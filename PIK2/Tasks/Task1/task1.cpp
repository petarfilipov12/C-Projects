#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE *f;

	char file_name[100];

	int c;

	int count = 0;

	char ch;

	int list[256];
	int i = 0;

	for (i = 0; i < 256; i++) {
		list[i] = 0;
	}

	printf("Input FILE: ");
	scanf("%s", file_name);

	f = fopen(file_name, "r");

	while ((c = fgetc(f)) != EOF) {
		list[c]++;
		count++;
	}

	for (i = 0; i < 256; i++) {
		if (list[i] != 0)
			printf("%c | %d | %x | %d \n", i, i, i, list[i]);
	}
	/* ---------------------------2----------------------------- */
	printf("Input ch2: ");
	scanf("%c", &ch);
	scanf("%c", &ch);

	printf("%f \n", float(list[ch]) / float(count));

	/* -----------------------3------------------------------- */

	FILE *fp1;

	fp1 = fopen("output.txt", "w");

	char ch_in_file;

	printf("ch in file: ");
	scanf("%c", &ch_in_file);
	scanf("%c", &ch_in_file);

	printf("ch: ");
	scanf("%c", &ch);
	scanf("%c", &ch);

	printf("%c | %c", ch_in_file, ch);

	fclose(f);
	f = fopen(file_name, "r");

	while ((c = fgetc(f)) != EOF) {
		if (c == ch_in_file){
			fputc(ch, fp1);
		}
		else{
			fputc(c, fp1);
		}
	}

	/*-------------------------------4----------------------------------------*/

	FILE *f_int;
	FILE *f_interval;
	FILE *f_zero;
	int num;

	int min, max;

	int interval_min;
	int interval_max;

	int colum;

	float avr = 0;

	count = 0;

	f_int = fopen("numbers.txt", "r");
	f_interval = fopen("interval.txt", "w");
	f_zero = fopen("zeros.txt", "w");

	printf("\nGorna Granica: ");
	scanf("%d", &interval_max);
	printf("\n Dolna Granica: ");
	scanf("%d", &interval_min);

	if (interval_min > interval_max){
		int temp;
		temp = interval_min;
		interval_min = interval_max;
		interval_max = temp;
	}

	printf("Kolko koloni na red: ");
	scanf("%d", &colum);

	max = min = fscanf(f_int, "%d", &num);

	i = 0;
	while (fscanf(f_int, "%d", &num) != EOF){
		if (num < min)
			min = num;
		if (num > max)
			max = num;
		if (num >= interval_min && num <= interval_max){
			if (i >= colum ){
				fprintf(f_interval, "\n", num);
				i = 0;
			}
			fprintf(f_interval, "%d		", num);
		}
		avr = avr + num;

		if (num < 0)
			fprintf(f_zero, "%d\n", 0);
		else
			fprintf(f_zero, "%d\n", num);

		count++;
		i++;
	}

	printf("\nmin = %d || max = %d", min, max);

	avr = avr / count;
	printf("\n %f", avr);

	fclose(f_int);
	fclose(f_interval);
	fclose(f_zero);
	fclose(f);
	fclose(fp1);
	system("PAUSE");
	return 0;


}