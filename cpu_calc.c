
#include "monitor.h"

static long long *readInput() {
	FILE *file = fopen("/proc/stat", "r");
	if (!file) return (NULL);
	
	long long *input = (long long *)malloc(sizeof(long long) * INPUT_SIZE);
	if (!input) return (NULL);
	
	int isValid = fscanf(file, "%*s %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", 
			&input[0], &input[1],&input[2],&input[3],
				&input[4],&input[5],&input[6],&input[7],
					  &input[8],&input[9]);
	
	fclose(file);
	if (isValid != INPUT_SIZE) return (free(input), NULL);
	
	return (input);
}

static long long sumCPU(long long *input) {
	long long accumulator = 0;
	for (size_t i = 0; i < INPUT_SIZE - 2; i++)
		accumulator += input[i];
	free(input);
	return (accumulator);
}

double cpuCalc(void) {
	long long *input = readInput();
	if (!input) exit(1);
	long long idle1 = input[3] + input[4];
	long long total1 = sumCPU(input);

	sleep(1);

	input = readInput();
	if (!input) exit(1);
	long long idle2 = input[3] + input[4];
	long long total2 = sumCPU(input);

	long long totalDelta = total2 - total1;
	long long idleDelta = idle2 - idle1;
	
	double usage = (double)(totalDelta - idleDelta) / totalDelta * 100.0;

	return (usage);
}
