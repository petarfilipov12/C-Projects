// tema4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct WORDS{
	char **words;
	int *counter;
	int rows = 0;
};

struct WORDS rechnik_func(FILE *f) {

	struct WORDS rechnik;

	char words_list[] = { ' ', ',', '.', ';', ':', '/', '\n', '\t', '?', '!' };
	char c;
	int i, j, rows_counter = 0;
	int consecutive = 0;

	
	rechnik.counter = (int *)malloc(sizeof(int));

	char *str;
	str = (char *)malloc(sizeof(char));

	for (i = 0; (c = fgetc(f)) != EOF; ) {
		str = (char *)realloc(str, (i + 1) * sizeof(char));
		for (j = 0; (c != words_list[j]) && (j < 10); j++);
		if (j < 10 ){
			//str[i] = '\n';
			consecutive++;
		}
		if (consecutive < 2){
			str[i] = '\n';

		}

		if(j > 9){
			str[i] = c;
			consecutive = 0;
		}
		if (consecutive < 2)
			i++;
	}
	str[i] = '\0';

	char *str_temp;
	str_temp = (char *)malloc(sizeof(char));

	rechnik.words = (char **)malloc(sizeof(char *));
	rechnik.words[0] = (char *)malloc(sizeof(char));
	rechnik.words[0][0] = '@';
	
	for (i = 0, j = 0; i < (strlen(str) + 1); i++){
		if (str[i] == '\n' || str[i] == '\0'){
			str_temp[j] = '\0';
			if (rechnik.words[0][0] == '@'){
				rechnik.words[0] = (char *)malloc(strlen(str_temp) * sizeof(char));
				strcpy(rechnik.words[0], str_temp);
				rechnik.counter[0] = 1;
				j = 0;
			}
			else{
				for (rows_counter = 0; strcmp(rechnik.words[rows_counter], str_temp) != 0 && rows_counter < rechnik.rows; rows_counter++);
				if (rows_counter < rechnik.rows)
					rechnik.counter[rows_counter]++;
				else{
					rechnik.rows++;
					
					rechnik.words = (char **)realloc(rechnik.words, (rechnik.rows + 1) * sizeof(char *));
					rechnik.words[rechnik.rows] = (char *)malloc(strlen(str_temp) * sizeof(char));
					strcpy(rechnik.words[rechnik.rows], str_temp);
					rechnik.words[rechnik.rows][strlen(rechnik.words[rechnik.rows]) + 1] = '\0';
					
					rechnik.counter = (int *)realloc(rechnik.counter, (rechnik.rows + 1) * sizeof(int));
					rechnik.counter[rechnik.rows] = 1;
				}

				j = 0;
			}
		}
		else{
			str_temp = (char *)realloc(str_temp, (j + 1) * sizeof(char));
			str_temp[j] = str[i];
			j++;
		}
	}




	return rechnik;

	free(str);
	free(str_temp);
}







void search_word(struct WORDS rechnik){

	char duma[100];

	int i;

	printf("\nTursena duma:");
	scanf("%s", duma);

	for (i = 0; strcmp(rechnik.words[i], duma) != 0 && i < rechnik.rows; i++);
	if (i < rechnik.rows)
		printf("\n%s || %d", rechnik.words[i], rechnik.counter[i]);
	else
		printf("\n%s ne prisustva v rechnika",duma);
}




struct WORDS sortirane(struct WORDS rechnik){

	char str_temp[50];

	int temp = 0;
	
	int i, j;

	printf("\n1: Sortirane po azbuchen red");
	printf("\n2: Sortirane po chestota");
	printf("\nInput: ");
	scanf("%d", &temp);

	while (temp < 1 && temp > 2){
		printf("\nVuvedeta valindna stoinost: ");
		scanf("%d", &temp);
	}

	if (temp == 1){
		for (i = 0; i <= rechnik.rows; i++){
			for (j = 0; j <= rechnik.rows; j++){
				if (strcmp(rechnik.words[i], rechnik.words[j]) < 0){
					temp = rechnik.counter[i];
					rechnik.counter[i] = rechnik.counter[j];
					rechnik.counter[j] = temp;

					strcpy(str_temp, rechnik.words[i]);
					strcpy(rechnik.words[i], rechnik.words[j]);
					strcpy(rechnik.words[j], str_temp);
				}
			}
		}
	}

	if (temp == 2){
		for (i = 0; i <= rechnik.rows; i++){
			for (j = 0; j <= rechnik.rows; j++){
				if (rechnik.counter[i] >= rechnik.counter[j]){
					temp = rechnik.counter[i];
					rechnik.counter[i] = rechnik.counter[j];
					rechnik.counter[j] = temp;

					strcpy(str_temp, rechnik.words[i]);
					strcpy(rechnik.words[i], rechnik.words[j]);
					strcpy(rechnik.words[j], str_temp);
				}
			}
		}
	}

	return rechnik;

}



void zapis(struct WORDS rechnik, char file_name_original[]){

	FILE *f;
	
	char file_name_rechnik[100];

	printf("\nIme na faila za zapis: ");
	scanf("%s", file_name_rechnik);


	int i;
	int temp = 0;


	while (temp < 1 || temp > 2){
		printf("\n1: vsichko v edin file");
		printf("\n2: Broq na sreshtaniqta v otdelen fail");
		printf("\nInput: ");
		scanf("%d", &temp);
	}

	if (temp == 1){
		f = fopen(strcat(file_name_rechnik, ".txt"), "w");
		fputs(file_name_original, f);

		for (i = 0; i <= rechnik.rows; i++)
			fprintf(f, "\n%s|%d", rechnik.words[i], rechnik.counter[i]);
	}
	if (temp == 2){
		FILE *count;

		char file_name_rechnik_temp[100];
		strcpy(file_name_rechnik_temp, file_name_rechnik);

		f = fopen(strcat(file_name_rechnik_temp, ".txt"), "w");
		fputs(file_name_original, f);

		for (i = 0; i <= rechnik.rows; i++)
			fprintf(f, "\n%d-%s", i, rechnik.words[i]);

		strcat(file_name_rechnik, ".cnt");
		count = fopen(file_name_rechnik, "w");
		fputs(file_name_original, count);
		for (i = 0; i <= rechnik.rows; i++)
			fprintf(count, "\n%d-%d", i, rechnik.counter[i]);
		fclose(count);
	}

	fclose(f);
	
}



struct WORDS zarejdane(){
	
	struct WORDS rechnik;
	
	FILE *f;

	char file_name[100];

	printf("\nput do rechnika: ");
	scanf("%s", file_name);

	f = fopen(file_name, "r");

	char c;
	int j = 0, count = 0;

	rechnik.counter = (int *)malloc(sizeof(int));

	rechnik.words = (char **)malloc(sizeof(char *));
	rechnik.words[0] = (char *)malloc(sizeof(char));

	do{
		c = fgetc(f);
		if (c == '|'){
			rechnik.counter = (int *)realloc(rechnik.counter, (count + 1) * sizeof(int));
			fscanf(f, "%d", &rechnik.counter[count]);
		}
		else if (c == '\n' || c == EOF){
			rechnik.words[count] = (char *)realloc(rechnik.words[count], (j + 1) * sizeof(char));
			rechnik.words[count][j] = '\0';
			if (c != EOF){
				count++;
				j = 0;
				rechnik.rows++;

				rechnik.words = (char **)realloc(rechnik.words, (count + 1) * sizeof(char *));
				rechnik.words[count] = (char *)malloc(sizeof(char));
			}
		}
		else{
			if (j > 0)
				rechnik.words[count] = (char *)realloc(rechnik.words[count], (j + 1) * sizeof(char));
			rechnik.words[count][j] = c;
			j++;
		}
	} while (c != EOF);

	return rechnik;

}



void kodirane(){
	char words_list[] = { ' ', ',', '.', ';', ':', '/', '\n', '\t', '?', '!' };

	char file_to_encode[100];
	char name_rechnik[100];
	char new_file_name[100];

	printf("\nIme na faila, koito shte bude kodiran: ");
	//scanf("%s", file_to_encode);
	strcpy(file_to_encode, "text1.txt");

	printf("\nIme na noviq file: ");
	//scanf("%s", new_file_name);
	strcpy(new_file_name, "gosho.txt");

	printf("\nRechnik: ");
	//scanf("%s", name_rechnik);
	strcpy(name_rechnik, "ivan.txt");


	FILE *fte, *r, *nf;

	fte = fopen(file_to_encode, "r");
	r = fopen(name_rechnik, "r");
	nf = fopen(new_file_name, "w");

	char **rechnik;
	rechnik = (char **)malloc(sizeof(char*));

	char c;
	int i = 0, j = 0;

	int temp = 0;
	int rechnik_rows;

	do{
		c = fgetc(r);
		if (temp == 1){
			if (c == '\n' || c == EOF){
				rechnik[i] = (char *)realloc(rechnik[i], (j + 1) * sizeof(char));
				rechnik[i][j] = '\0';
				temp = 0;
				j = 0;
				i++;
			}
			else{
				if (j > 0)
					rechnik[i] = (char *)realloc(rechnik[i], (j + 1) * sizeof(char));
				rechnik[i][j] = c;
				j++;
			}

		}
		if (c == '-'){
			temp = 1;
			rechnik = (char **)realloc(rechnik, (i + 1) * sizeof(char*));
			rechnik[i] = (char *)malloc(sizeof(char));
		}
	} while (c != EOF);

	for (j = 1; j < i; j++)
		printf("\n%s", rechnik[j]);

	fclose(r);

	rechnik_rows = i - 1;


	char str_temp[100];

	temp = 0;

	fputs(name_rechnik, nf);
	fputc('\n', nf);

	
	while ((c = fgetc(fte)) != EOF){
		for (j = 0; (c != words_list[j]) && (j < 10); j++);
		if (j >= 10){
			str_temp[temp] = c;
			temp++;
		}
		else{
			str_temp[temp] = '\0';
			for (j = 0; strcmp(rechnik[j], str_temp) != 0 && j < rechnik_rows; j++);

			fprintf(nf, "%d", j);
			fprintf(nf, "%c", c);

			temp = 0;
		}
	}

	fclose(nf);
	fclose(fte);

}




void dekodirane(){
	char words_list[] = { ' ', ',', '.', ';', ':', '/', '\n', '\t', '?', '!' };

	char file_to_decode[100];
	char new_file[100];

	/*
	printf("\nFile za dekodirane");
	scanf("%s", file_to_decode);
	printf("\nNov file");
	scanf("%s", new_file);
	*/

	strcpy(file_to_decode, "gosho.txt");
	strcpy(new_file, "margo.txt");

	FILE *ftd, *nf, *r;

	nf = fopen(new_file, "w");
	ftd = fopen(file_to_decode, "r");

	char *name_rechnik;
	name_rechnik = (char *)malloc(sizeof(char));


	char c;
	int i = 0, j = 0;

	int temp = 0;
	int rechnik_rows;

	for (i = 0; (c = fgetc(ftd)) != '\n'; i++){
		name_rechnik = (char *)realloc(name_rechnik, (i + 1) * sizeof(char));
		name_rechnik[i] = c;
	}
	name_rechnik[i] = '\0';

	r = fopen(name_rechnik, "r");

	char **rechnik;
	rechnik = (char **)malloc(sizeof(char*));

	
	i = 0;
	do{
		c = fgetc(r);
		if (temp == 1){
			if (c == '\n' || c == EOF){
				rechnik[i] = (char *)realloc(rechnik[i], (j + 1) * sizeof(char));
				rechnik[i][j] = '\0';
				temp = 0;
				j = 0;
				i++;
			}
			else{
				if (j > 0)
					rechnik[i] = (char *)realloc(rechnik[i], (j + 1) * sizeof(char));
				rechnik[i][j] = c;
				j++;
			}

		}
		if (c == '-'){
			temp = 1;
			rechnik = (char **)realloc(rechnik, (i + 1) * sizeof(char*));
			rechnik[i] = (char *)malloc(sizeof(char));
		}
	} while (c != EOF);

	rechnik_rows = i - 1;



	while ((c = fgetc(ftd)) != EOF){
		for (j = 0; (c != words_list[j]) && (j < 10); j++);
		if (j < 10)
			fprintf(nf, "%c", c);
		else{
			fseek(ftd, -1, SEEK_CUR);
			fscanf(ftd, "%d", &i);
			fprintf(nf, "%s", rechnik[i]);
		}
		
	}





	fclose(nf);
	fclose(ftd);

}



int main() {

	struct WORDS rechnik;

	FILE *f;


	char file_name[100];
	char c;

	int temp;
	int i;

	printf("1: Input from console\n2: Input from File\nChoose: ");
	do {
		scanf("%d", &temp);
		if (temp < 1 || temp > 2)
			printf("\nChoose valid number: ");
	} while (temp < 1 || temp > 2);

	if (temp == 1) {
		printf("\nPath to File: ");
		scanf("%s", file_name);
	}

	if (temp == 2) {
		char file_to_file[100];

		printf("\nFile containing file name: ");
		scanf("%s", file_to_file);

		FILE *name;
		name = fopen(file_to_file, "r");
		for (i = 0; (c = fgetc(name)) != EOF; i++)
			file_name[i] = c;
		file_name[i] = '\0';

		fclose(name);
	}

	f = fopen(file_name, "r");

	printf("\n%s", file_name);

	while (temp != 99) {
		printf("\n\n1: Suzdavane na rechnik na izpolzvanite dumi");
		printf("\n\n2: Printirane na rechnik");
		printf("\n\n3: Tursene na duma v rechnika");
		printf("\n\n4: Sortirane");
		printf("\n\n5: Zapis");
		printf("\n\n6: Zarejdane na rechnik ot file");
		printf("\n\n7: kodirane");
		printf("\n\n8: dekodirane");

		printf("\n\n\n\n\n99: Izhod");
		printf("\nInput: ");
		scanf("%d", &temp);

		if (temp == 1)
			rechnik = rechnik_func(f);
		if (temp == 2){
			for (i = 0; i <= rechnik.rows; i++)
				printf("\n%s || %d", rechnik.words[i], rechnik.counter[i]);
		}
		if (temp == 3)
			search_word(rechnik);
		if (temp == 4)
			rechnik = sortirane(rechnik);
		if (temp == 5)
			zapis(rechnik, file_name);
		if (temp == 6)
			rechnik = zarejdane();
		if (temp == 7)
			kodirane();
		if (temp == 8)
			dekodirane();
	}

	fclose(f);

	return 0;
}
