#!/bin/bash

stm32flash -b 115200 -w RootControl.bin -v -g 0x0 /dev/ttyUSB0

