# e-birdhouse
TI RF Birdhouse
contact: dmitriigalantsev AT gmail.com

[Example visualization](https://datastudio.google.com/reporting/4fe43fef-7b5d-4011-a5dd-2243992ace87)

[Additional docs](https://github.com/dmitrii-galantsev/e-birdhouse/tree/master/docs/README.md)

folder structure
```
.
├── README.md               - this readme file
├── docs                    - documentation
├── rpi_src                 - raspberry pi
│   └── serial_read             - serial reader
├── server_src              - remote data server
│   └── ring_server             - POST receiver and DB manager
└── ti_src                  - ti board files
    ├── bird_motion_detector
    ├── i2c_temp_humidity
    ├── rf_easy_rx              - receiver
    └── rf_easy_tx              - sender


```

Battery tests:
```
2020/03/07
    Somewhat sunny day today. Battery been charging from solar at my window all
    day without the board connected.
    Just connected now at 7:00 PM. Logging temp+hum every 10 min.
    Was pulling 2mA in idle with programmer connected. Just disconnected
    programmer 30 min into experiment. Hopefully it pulls less now.

    Results:
    day  0: 00 hr 30 min - no problem, took off programmer jumpers off the eval
            board.
    day  0: 01 hr 30 min - no problem
    day  3: 11 hr 30 min - no problem, no drops in data, still going strong!

2020/03/15
    day  7: 21 hr 10 min - no problem, log count accurate. Finish testing.
            System logged for almost 8 days without errors. All during rainy
            weather. 
```

Connectivity diagram:

![][connectivity_diagram]

[connectivity_diagram]: ./docs/connectivity_diagram.png?raw=true "Connectivity diagram"
