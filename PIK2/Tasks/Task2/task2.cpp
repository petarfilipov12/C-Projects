// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){

	char words_list[] = { ' ', ',', '.', ';', ':', '/', '\n', '\t' };

	char sentences_list[] = { '.', '?', '!', ':' };

	FILE *f;
	FILE *w;
	FILE *sen;
	FILE *con_in;
	FILE *con_out;
	FILE *p_in;
	FILE *p_out;

	p_out = fopen("path_out.txt", "w");

	p_in = fopen("path_in.txt", "r");

	con_out = fopen("consts_output.txt", "w");

	con_in = fopen("consts_input.txt", "r");

	sen = fopen("sentences.txt", "w");

	w = fopen("words.txt", "w");

	f = fopen("text.txt", "r");

	int c;
	int i, j = 0, k = 0;

	char *str;
	str = (char *)malloc(sizeof(char));

	while ((c = fgetc(f)) != EOF) {
		for (i = 0; (c != words_list[i]) && (i < 8); i++);
		if (i < 8){
			fprintf(w, "\n");
			j++;
		}
		else
			fprintf(w, "%c", c);

		for (i = 0; (c != sentences_list[i]) && (i < 5); i++);
		if (i < 5){
			fprintf(sen, "\n");
			k++;
		}
		else
			fprintf(sen, "%c", c);
	}

	printf("words = %d || sentences = %d\n", j, k);


	for (i = 0; c = fgetc(con_in);){
		if (c != '\n' && c != EOF) {
			str = (char *)realloc(str, (i + 1) * sizeof(char));
			str[i] = c;
			i++;
		}
		else {
			str[i] = '\0';
			for (j = 0; j < strlen(str) && str[j] != '.'; j++);
			if (j < strlen(str))
				fprintf(con_out, "%s - float\n", str);
			else
				fprintf(con_out, "%s - int\n", str);
			i = 0;
		}
		if (c == EOF)
			break;

	}
	//--------------------------------------------------------------DISK-------------------------------------------------------------

	int temp1 = 0;
	int temp2 = 0;
	int dot_location = 0;

	char disk = '@';

	char *path;
	path = (char *)malloc(sizeof(char));

	char *name;
	name = (char *)malloc(sizeof(char));

	char *ext;
	ext = (char *)malloc(sizeof(char));


	for (i = 0; (c = fgetc(p_in)) != EOF; i++) {
		str = (char *)realloc(str, ((i + 1) * sizeof(char)+1));
		str[i] = c;
	}

	str[i] = '\0';

	for (i = 0; i < strlen(str); i++) {
		if (disk == '@' && str[i] == ':') {
			disk = str[i - 1];
			i++;
		}
		if (disk != '@') {
			while (i < strlen(str)) {
				if (str[i] == 92) {
					if (temp1 == 0)
						temp1 = i;
					if (temp1 != 0)
						temp2 = i;
				}
				if (str[i] == '.') {
					dot_location = i;
					break;
				}
				i++;
			}
		}
	}

	path = (char *)realloc(path, (temp2 - temp1) * sizeof(char)+1);
	path[(temp2 - temp1) + 1] = '\0';
	for (j = 0; temp1 <= temp2; temp1++, j++)
		path[j] = str[temp1];

	temp2++;
	name = (char *)realloc(name, (dot_location - temp2) * sizeof(char));
	name[dot_location - temp2] = '\0';
	for (j = 0; temp2 < dot_location; temp2++, j++)
		name[j] = str[temp2];

	ext = (char *)realloc(ext, (strlen(str) - dot_location) * sizeof(char));
	ext[strlen(str) - dot_location] = '\0';
	for (j = 0; dot_location < strlen(str); dot_location++, j++)
		ext[j] = str[dot_location];

	fprintf(p_out, "file: %s \ndisk: %c: \npath: %s \nname: %s \next: %s", str, disk, path, name, ext);

	fclose(f);
	fclose(w);
	fclose(sen);
	fclose(con_in);
	fclose(con_out);
	fclose(p_in);
	fclose(p_out);

	free(str);
	//free(path);
	//free(name);
	//free(ext);

	return 0;
}
