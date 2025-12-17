
#include "monitor.h"

double tempCalc(void) {
	FILE *file = fopen("/sys/class/thermal/thermal_zone1/temp", "r");
	if (!file) return (1);
	
	long long rawTemp;
	int isValid = fscanf(file, "%lld", &rawTemp);
	fclose(file);
	if (isValid != 1) exit(1);
	
	double temperature = (double)rawTemp / 1000.0;
	return (temperature);
}
