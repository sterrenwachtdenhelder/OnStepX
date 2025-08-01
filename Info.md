## Informatie over de telescoop
| Parameter          | Waarde |
| ------------------ | ------ |
| Spiegeldiameter    | 400mm  |
| Openingsverhouding | 5.6    |
| Brandpuntafstand   | 2240mm |
| Monteringtype      | Fork   |
| RA Reductie        | 720    |
| DEC Reductie       | 480    |



## Informatie over de stapmotoren
| Parameter             | Waarde |
| --------------------- | ------ |
| Stappen per revolutie | 200    |
| Maximale RPM          | 120    |


## Informatie over de OnStepX Controller
| Parameter       | Waarde  |
| --------------- | ------- |
| Printplaat      | MaxPCB4 |
| Stapmotordrivers| TMC2209 |


## Instellingen die in `Config.h` moeten worden geplaatst.
De waarde van deze instellingen zijn berekent met het excel bestand te vinden op de OnStep groups.io pagina, of in deze repository met alle waardes al ingevuld.


| Parameter                 | Waarde      | Notities |
| ------------------------- | ----------- | -------- |
| PINMAP                    | MaxPCB4     |
| STATUS\_LED               | ON          |
| AXIS1\_DRIVER\_MODEL      | TMC2209S    | Legacy mode |
| AXIS1\_STEPS\_PER\_DEGREE | 25600       |
| AXIS1\_DRIVER\_MICROSTEPS | 64          |
| AXIS1\_DRIVER\_IHOLD      | 400         |
| AXIS1\_DRIVER\_IRUN       | 800         |
| AXIS1\_DRIVER\_IGOTO      | 1000        |
| AXIS2\_DRIVER\_MODEL      | TMC2209S    | Legacy mode |
| AXIS2\_STEPS\_PER\_DEGREE | 17066.66667 |
| AXIS2\_DRIVER\_MICROSTEPS | 64          |
| AXIS2\_DRIVER\_IHOLD      | 400         |
| AXIS2\_DRIVER\_IRUN       | 800         |
| AXIS2\_DRIVER\_IGOTO      | 1000        |
| MOUNT\_TYPE               | FORK        |
| AXIS1\_HOME\_DEFAULT      | 180         | Verborgen instelling |
| AXIS2\_HOME\_DEFAULT      | 20          | Verborgen instelling |
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
| AXIS4\_DRIVER\_MODEL      | TMC2209S    | Legacy mode |
| AXIS4\_DRIVER\_MICROSTEPS | 64          |
