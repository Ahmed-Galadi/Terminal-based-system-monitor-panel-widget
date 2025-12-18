#ifndef MONITOR_H
#define MONITOR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/statvfs.h>
#include <stddef.h>
#include <unistd.h>

#define INPUT_SIZE 10
#define PROGRESS_BAR_LEN 5

double tempCalc(void);
double cpuCalc(void);
double *ramCalc(void);
double *storageCalc(void);

#endif
