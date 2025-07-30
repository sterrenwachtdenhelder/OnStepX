## Informatie over de kijker
| Parameter    | Waarde |
| ------------ | ------ |
| RA Reductie  | 720    |
| DEC Reductie | 480    |


## Informatie over de stapmotoren
| Parameter             | Waarde |
| --------------------- | ------ |
| Stappen per revolutie | 200    |
| Maximale RPM          | 120    |


## Informatie over de OnStepX Controller
| Parameter       | Waarde          |
| --------------- | --------------- |
| Printplaat      | MaxPCB4         |
| Stapmotordrivers| TMC2209 (legacy)|


## Instellingen van de kijker die in `Config.h` moeten worden geplaatst.
De waarde van deze instellingen zijn berekent met het excel bestand te vinden op de OnStep groups.io pagina, of in deze repository met alle waardes al ingevuld.


| Parameter                 | Value       |
| ------------------------- | ----------- |
| PINMAP                    | MaxPCB4     |
| STATUS\_LED               | ON          |
| AXIS1\_DRIVER\_MODEL      | TMC2209S    |
| AXIS1\_STEPS\_PER\_DEGREE | 25600       |
| AXIS1\_DRIVER\_MICROSTEPS | 64          |
| AXIS1\_DRIVER\_IHOLD      | 400         |
| AXIS1\_DRIVER\_IRUN       | 800         |
| AXIS1\_DRIVER\_IGOTO      | 1000        |
| AXIS2\_DRIVER\_MODEL      | TMC2209S    |
| AXIS2\_STEPS\_PER\_DEGREE | 17066.66667 |
| AXIS2\_DRIVER\_MICROSTEPS | 64          |
| AXIS2\_DRIVER\_IHOLD      | 400         |
| AXIS2\_DRIVER\_IRUN       | 800         |
| AXIS2\_DRIVER\_IGOTO      | 1000        |
| MOUNT\_TYPE               | FORK        |
| TIME\_LOCATION\_SOURCE    | TEENSY      |
| STATUS\_MOUNT\_LED        | ON          |
| STATUS\_BUZZER            | ON          |
| STATUS\_BUZZER\_DEFAULT   | ON          |
| STATUS\_BUZZER\_MEMORY    | ON          |
| GUIDE\_TIME\_LIMIT        | 60          |
| SLEW\_RATE\_BASE\_DESIRED | 0.5         |
| SLEW\_RATE\_MEMORY        | ON          |
| SLEW\_ACCELERATION\_DIST  | 1.0         |
| SLEW\_RAPID\_STOP\_DIST   | 0.5         |
| AXIS4\_DRIVER\_MODEL      | TMC2209S    |
| AXIS4\_DRIVER\_MICROSTEPS | 64          |
