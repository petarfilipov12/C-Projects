// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {

	FILE *f;

	f = fopen("numbers.txt", "r");

	int *arr;
	arr = (int *)malloc(sizeof(int));

	int num, sum = 0, l = 0, j, i, k;
	int interval_left, interval_right;
	
	while (fscanf(f, "%d", &num) != EOF){
		arr = (int*)realloc(arr, (l + 1) * sizeof(int));
		arr[l] = num;
		l++;
	}
	arr[l] = '\0';

	
	for (i = 0; i < l; i++)
		printf("arr[%d] = %d\n", i, arr[i]);


	for (i = 0; i < l; i++){
		for (j = i, num = arr[i]; j < l; j++){
			if (arr[j] > num){
				num = arr[j];
				k = j;
			}
		}
		arr[k] = arr[i];
		arr[i] = num;

	}
	printf("----------------------\n");
	for (i = 0; i < l; i++){
		printf("arr[%d] = %d\n", i, arr[i]);
		sum = sum + arr[i];
	}
	printf("avr = %d\n", sum / l);

	printf("max = %d, min = %d\n", arr[0], arr[l - 1]);

	printf("interval_left = ");
	scanf("%d", &interval_left);
	printf("interval_right = ");
	scanf("%d", &interval_right);

	for (i = 0; i < l; i++){
		if (arr[i] > interval_left && arr[i] < interval_right)
			printf("arr[%d] = %d\n", i, arr[i]);
	}





	return 0;
}