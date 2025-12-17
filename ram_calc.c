#include "monitor.h"

double *ramCalc(void) {
	FILE *file = fopen("/proc/meminfo", "r");
	if (!file) exit(1);

	double availableRAM = 0.0;
	double totalRAM = 0.0;
	double usedRAM = 0.0;
	double RAMpercent = 0.0;

	char line[1024];
	while (fgets(line, sizeof(line), file) != NULL) {
		if (!strncmp(line ,"MemTotal:", strlen("MemTotal:")))
			sscanf(line,"%*s %lf", &totalRAM);
		if (!strncmp(line ,"MemAvailable:", strlen("MemAvailable:")))
			sscanf(line,"%*s %lf", &availableRAM);
		if (totalRAM && availableRAM) break;
	}
	
	fclose(file);

	availableRAM /= (1024 * 1024);
	totalRAM /= (1024 * 1024);
	usedRAM = totalRAM - availableRAM;
	RAMpercent = usedRAM / totalRAM * 100.0;

	double *output = (double *)malloc(sizeof(double) * 3);
	output[0] = usedRAM;
	output[1] = totalRAM;
	output[2] = RAMpercent;
	return (output);
}
