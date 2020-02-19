# Hardware used

```
- TI boards:              CC1352R Wireless MCU
- Luminosity sensor:      SparkFun TSL2561 (might need to be ported to another sensor)
- Humidity+temp sensor:   SparkFun Si7021
- Raspberry Pi:           TBA
```

# Database

PostgreSQL 10

More info [here][database]

# Visualization

[Google Data Studio](https://datastudio.google.com/navigation/reporting)

More info [here][visualization]

# Potential additions

```
- Current sensor:         Zio Qwiic Current Sensor
- Motion sensor:          SparkFun OpenPIR
- Solar controller:       SparkFun Sunny Buddy
- Solar panel:            TBA
- Battery for solar:      TBA
```

Connectivity diagram:

![][connectivity_diagram]

TI:

![][ti]

RPi:

![][rpi]

Luminosity:

![][si7021]

Humidity+temp:

![][tl2561]

[ti]: ./ti.jpg?raw=true "Sensor collector + rf transciever"
[rpi]: ./rpi.jpeg?raw=true "Data uploader"
[si7021]: ./si7021.jpeg?raw=true "Luminosity sensor"
[tl2561]: ./tl2561.jpeg?raw=true "Temperature + humidity sensor"

[connectivity_diagram]: ./connectivity_diagram.png?raw=true "Connectivity diagram"

[database]: ./DATABASE.md
[visualization]: ./VISUALIZATION.md
