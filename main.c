#include "monitor.h"

char *make_bar(double persentage) {
	char *buffer = (char *)malloc(PROGRESS_BAR_LEN * 8);
	int full = (int)(persentage / 100.0 * PROGRESS_BAR_LEN);
	
	for (int i = 0; i < PROGRESS_BAR_LEN; i++) {
		if (i < full)
			strcat(buffer, "●");
		else
			strcat(buffer, "○");
	}
	return (buffer);
}

int main() {
	double CPU_usage = cpuCalc();
	double CPU_temperature = tempCalc();
	double *RAM_usage = ramCalc();
	double *DISK_usage = storageCalc();
	
	char *CPU_color =
		CPU_usage <= 20 ? "#00BFFF" :
		CPU_usage <= 40 ? "#00FF00" :
		CPU_usage <= 60 ? "#FFFF00" :
		CPU_usage <= 80 ? "#FFA500" :
		"#FF4500";

	char *CPU_temp_color = 
		CPU_temperature <= 30 ? "#00BFFF" :
		CPU_temperature <= 40 ? "#00FF00" :
		CPU_temperature <= 60 ? "#FFFF00" :
		CPU_temperature <= 70 ? "#FFA500" :
		"#FF4500";

	char *RAM_usage_color = 
		RAM_usage[2] <= 20 ? "#00BFFF" :
		RAM_usage[2] <= 40 ? "#00FF00" :
		RAM_usage[2] <= 60 ? "#FFFF00" :
		RAM_usage[2] <= 80 ? "#FFA500" :
		"#FF4500";

	char *DISK_usage_color =
		DISK_usage[2] <= 20 ? "#00BFFF" :
		DISK_usage[2] <= 40 ? "#00FF00" : 
		DISK_usage[2] <= 60 ? "#FFFF00" :
		DISK_usage[2] <= 80 ? "#FFA500" :
		"#FF4500";

	char *CPU_bar = make_bar(CPU_usage);
	char *RAM_bar = make_bar(RAM_usage[2]);
	char *DISK_bar = make_bar(DISK_usage[2]);

	printf(
	"<txt><span foreground=\"%s\">CPU ⚛ %s %.1f%%</span> | "
	"<span foreground=\"%s\">Temp 🌡: %.1f°C</span> | "
	"<span foreground=\"%s\">RAM 🗂 %.1f/%.1fGB %s (%.1f%%)</span> | "
	"<span foreground=\"%s\">DISK ⛃ %s %.1f/%.1fGB (%.1f%%)</span></txt>",
		CPU_color, CPU_bar, CPU_usage,
		CPU_temp_color, CPU_temperature,
		RAM_usage_color, RAM_usage[0], RAM_usage[1], RAM_bar, RAM_usage[2],
		DISK_usage_color, DISK_bar, DISK_usage[0], DISK_usage[1], DISK_usage[2]
	);

	free(RAM_usage);
	free(DISK_usage);
	free(CPU_bar);
	free(RAM_bar);
	free(DISK_bar);
	return (0);
}
