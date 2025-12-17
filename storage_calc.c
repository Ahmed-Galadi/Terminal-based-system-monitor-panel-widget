
#include "monitor.h"

double *storageCalc(void) {
	struct statvfs fs;
	statvfs("/", &fs);

	unsigned long total = fs.f_blocks * fs.f_frsize;
	unsigned long free  = fs.f_bfree * fs.f_frsize;
	unsigned long used  = total - free;
	double usagePercent = (double)used / total * 100.0;
	
	double totalGB = total / 1024.0 / 1024.0 / 1024.0;
	double usedGB = used/ 1024.0 / 1024.0 / 1024.0;
	
	double *output = (double *)malloc(sizeof(double) * 3);
	output[0] = usedGB;
	output[1] = totalGB;
	output[2] = usagePercent;
	return (output);
}
