// Broadcom AS37-H39B-B BISS-C encoders

#include "As37h39bb.h"

#ifdef HAS_AS37_H39B_B

// initialize BiSS-C encoder
As37h39bb::As37h39bb(int16_t maPin, int16_t sloPin, int16_t axis) {
  if (axis < 1 || axis > 9) return;

  this->axis = axis;

  this->maPin = maPin;
  this->sloPin = sloPin;
}

// get encoder count relative to origin
IRAM_ATTR bool As37h39bb::getCount(uint32_t &count) {

  bool foundAck = false;
  bool foundStart = false;
  bool foundCds = false;

  uint8_t  encErr = 0;
  uint8_t  encWrn = 0;
  uint8_t  as37Crc = 0;

  uint32_t encTurns = 0;

  // prepare for a reading
  count = 0;

  // bit delay in nanoseconds
  int rate = lround(500000.0/BISSC_CLOCK_RATE_KHZ);

  #ifdef ESP32
    portMUX_TYPE bisscMutex = portMUX_INITIALIZER_UNLOCKED;
    taskENTER_CRITICAL(&bisscMutex);
  #else
    noInterrupts();
  #endif

  // sync phase
  for (int i = 0; i < 20; i++) {
    digitalWriteF(maPin, LOW_MA);
    if (digitalReadF(sloPin) == LOW_SLO) foundAck = true;
    delayNanoseconds(rate);
    digitalWriteF(maPin, HIGH_MA);
    delayNanoseconds(rate);
    if (foundAck) break;
  }

  // if we have an Ack
  if (foundAck) {
    for (int i = 0; i < 20; i++) {
      digitalWriteF(maPin, LOW_MA);
      if (digitalReadF(sloPin) == HIGH_SLO) foundStart = true;
      delayNanoseconds(rate);
      digitalWriteF(maPin, HIGH_MA);
      delayNanoseconds(rate);
      if (foundStart) break;
    }

    // if we have an Start
    if (foundStart) {
      digitalWriteF(maPin, LOW_MA);
      if (digitalReadF(sloPin) == LOW_SLO) foundCds = true;
      delayNanoseconds(rate);
      digitalWriteF(maPin, HIGH_MA);
      delayNanoseconds(rate);

      // if we have an Cds, read the data
      if (foundCds) {

        // the first 16 bits are the multi-turn count
        for (int i = 0; i < 16; i++) {
          digitalWriteF(maPin, LOW_MA);
          if (digitalReadF(sloPin) == HIGH_SLO) bitSet(encTurns, 15 - i);
          delayNanoseconds(rate);
          digitalWriteF(maPin, HIGH_MA);
          delayNanoseconds(rate);
        }
        
        // the next 23 bits are the encoder absolute count
        for (int i = 0; i < 23; i++) {
          digitalWriteF(maPin, LOW_MA);
          if (digitalReadF(sloPin) == HIGH_SLO) bitSet(count, 22 - i);
          delayNanoseconds(rate);
          digitalWriteF(maPin, HIGH_MA);
          delayNanoseconds(rate);
        }

        // the Err bit
        digitalWriteF(maPin, LOW_MA);
        if (digitalReadF(sloPin) == HIGH_SLO) encErr = 1;
        delayNanoseconds(rate);
        digitalWriteF(maPin, HIGH_MA);
        delayNanoseconds(rate);

        // the Wrn bit
        digitalWriteF(maPin, LOW_MA);
        if (digitalReadF(sloPin) == HIGH_SLO) encWrn = 1;
        delayNanoseconds(rate);
        digitalWriteF(maPin, HIGH_MA);
        delayNanoseconds(rate);

        // the last 6 bits are the CRC
        for (int i = 0; i < 6; i++) {
          digitalWriteF(maPin, LOW_MA);
          if (digitalReadF(sloPin) == HIGH_SLO) bitSet(as37Crc, 5 - i);
          delayNanoseconds(rate);
          digitalWriteF(maPin, HIGH_MA);
          delayNanoseconds(rate);
        }
      }
    }
  }

  // send a CDM (invert)
  digitalWriteF(maPin, LOW_MA);
  delayNanoseconds(rate*4);
  digitalWriteF(maPin, HIGH_MA);

  #ifdef ESP32
    taskEXIT_CRITICAL(&bisscMutex);
  #else
    interrupts();
  #endif

  // trap errors
  int16_t errors = 0;

  uint64_t encData = (uint64_t)count | ((uint64_t)encTurns << 23);
  encData = (encData << 1) | encErr;
  encData = (encData << 1) | encWrn;

  if (!encWrn)     { DF("WRN: Encoder AS37_H39B_B"); D(axis); DLF(", Warn bit set"); warn++; }

  if (!foundAck)   { DF("WRN: Encoder AS37_H39B_B"); D(axis); DLF(", Ack bit invalid"); errors++; } else
  if (!foundStart) { DF("WRN: Encoder AS37_H39B_B"); D(axis); DLF(", Start bit invalid"); errors++; } else
  if (!foundCds)   { DF("WRN: Encoder AS37_H39B_B"); D(axis); DLF(", Cds bit invalid"); errors++; } else
  if (encErr)      { DF("WRN: Encoder AS37_H39B_B"); D(axis); DLF(", Error bit set"); errors++; } else
  if (crc6(encData) != as37Crc) {
    DF("WRN: Encoder AS37_H39B_B"); D(axis); DF(", Crc invalid (overall "); D(((float)(++bad)/good)*100.0F); D("%"); DLF(")");
    errors++;
  } else good++;

  if (errors > 0) {
    error++;
    return false;
  }

  #if BISSC_SINGLE_TURN == ON
    // extend negative to 32 bits
    if (bitRead(count, 23)) { count |= 0b11111111100000000000000000000000; }
  #else
    // combine absolute and 9 low order bits of multi-turn count for a 32 bit count
    count = count | ((encTurns & 0b0111111111) << 23);
  #endif

  count += origin;

  #if BISSC_SINGLE_TURN == ON
    if ((int32_t)count >= 8388608) count -= 8388608;
    if ((int32_t)count < 0) count += 8388608;
  #endif

  count -= 4194304;

  return true;
}

// Designed according protocol description found in as38-H39e-b-an100.pdf and
// Renishaw application note E201D02_02

// BiSS-C 6-bit CRC of 41 bit data (16 multi-turn + 23 position + 2 err/wrn)
uint8_t As37h39bb::crc6(uint64_t data) {
  uint8_t crc;
  uint64_t idx;
  idx = ((data >> 36) & 0b011111);
  crc = ((data >> 30) & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = ((data >> 24) & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = ((data >> 18) & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = ((data >> 12) & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = ((data >> 6) & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = (data & 0b111111);
  idx = crc ^ CRC6[idx];
  crc = CRC6[idx];
  return (~crc & 0b111111);
}

#endif
