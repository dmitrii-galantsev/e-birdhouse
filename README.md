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
│   └── serial_read             - serial reader WIP
├── server_src              - remote data server
│   └── ring_server             - POST receiver and DB manager
└── ti_src                  - ti board files
    ├── bird_motion_detector
    ├── i2c_temp_humidity
    ├── rf_easy_rx              - reciever
    └── rf_easy_tx              - sender


```
