#!/bin/bash

CPU_PERSENTAGE=$(./CPU_CALC)
RAW_CPU_TEMP=$(< /sys/class/thermal/thermal_zone1/temp)
CPU_TEMPERTURE=$(echo "scale=1; $RAW_CPU_TEMP / 1000" | bc)
RAMTOTAL=$(awk '/MemTotal/ { printf "%.1f", $2 / 1024 / 1024 }' /proc/meminfo)
RAMAVAILABLE=$(awk '/MemAvailable/ { printf "%.1f", $2 / 1024 / 1024 }' /proc/meminfo)

