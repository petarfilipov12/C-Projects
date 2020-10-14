#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

struct student{
	char FirstName[20];
	char MiddleName[20];
	char LastName[20];

	long int FacNumber;

	char faculty[5];

	char specialty[20];

	int group;

	int course;

};

struct node{
	struct student std;
	struct node *next;
};




struct node *dobavqne(struct node *head){

	struct node *crnt;
	crnt = (struct node *)malloc(sizeof(struct node));


	printf("\nIme: ");
	scanf("%s", crnt->std.FirstName);

	printf("\nPrezime: ");
	scanf("%s", crnt->std.MiddleName);

	printf("\nFamiliq: ");
	scanf("%s", crnt->std.LastName);

	printf("\nFaculteten nomer: ");
	scanf("%d", &crnt->std.FacNumber);

	printf("\nFakultet: ");
	scanf("%s", crnt->std.faculty);

	printf("\nSpecialnost: ");
	scanf("%s", crnt->std.specialty);

	printf("\nGrupa: ");
	scanf("%d", &crnt->std.group);

	printf("\nKurs: ");
	scanf("%d", &crnt->std.course);

	if (head == NULL)
		crnt->next = NULL;
	else
		crnt->next = head;

	head = crnt;




	return head;


}




void tursene_po_familiq(struct node *head){
	char str[20];

	printf("\nFamiliq na turseniq student: ");
	scanf("%s", str);


	struct node *p = NULL;
	p = (struct node *)malloc(sizeof(struct node));

	for (p = head; p != NULL; p = p->next){
		if (strcmp(p->std.LastName, str) == 0){
			printf("\nIme: %s %s %s", p->std.FirstName, p->std.MiddleName, p->std.LastName);

			printf("\nFaculteten nomer: %d", p->std.FacNumber);

			printf("\nFakultet: %s", p->std.faculty);

			printf("\nSpecialnost: %s", p->std.specialty);

			printf("\nGrupa: %d", p->std.group);

			printf("\nKurs: %d", p->std.course);
		}
	}


}




struct node *iztrivane_po_facnomer(struct node *head){

	struct node *prev = NULL, *crnt = NULL;

	long int temp;
	printf("\nFakulteten nomer na studenta za iztrivane: ");
	scanf("%d", &temp);

	crnt = head;
	if (crnt->std.FacNumber == temp)
		return crnt->next;
	else{
		for (prev = crnt, crnt = crnt->next; crnt->std.FacNumber != temp; prev = crnt, crnt = crnt->next);
		prev->next = crnt->next;
		return head;
	}

}




void izvejdane_po_grupa(struct node *head){

	struct student *temp;
	temp = (struct student *)malloc(sizeof(struct student));

	int GROUP, i, j;
	printf("\nGrupa: ");
	scanf("%d", &GROUP);

	struct node *p = NULL;
	p = (struct node *)malloc(sizeof(struct node));

	for (p = head, i = 0; p != NULL; p = p->next){
		if (p->std.group == GROUP){
			temp = (struct student *)realloc(temp, (i + 1) * sizeof(struct student));
			temp[i] = p->std;
			
			i++;
		}
	}

	int l = i;

	struct student temp2;

	for (i = 0; i < l; i++){
		for (j = 0; j < l; j++){
			if (strcmp(temp[i].FirstName, temp[j].FirstName) < 0){
				temp2 = temp[i];
				temp[i] = temp[j];
				temp[j] = temp2;
			}
		}
	}


	for (i = 0; i < l; i++){
		printf("\nIme: %s %s %s", temp[i].FirstName, temp[i].MiddleName, temp[i].LastName);

		printf("\nFaculteten nomer: %d", temp[i].FacNumber);

		printf("\nFakultet: %s", temp[i].faculty);

		printf("\nSpecialnost: %s", temp[i].specialty);

		printf("\nGrupa: %d", temp[i].group);

		printf("\nKurs: %d", temp[i].course);
	}

}




int main()
{
	struct node *head = NULL;
	head = (struct node *)malloc(sizeof(struct node));
	head = NULL;

	int temp = 0;

	while (1){
		printf("\n1: Dobavqne na student.");
		printf("\n2: Tursene na student po familno ime.");
		printf("\n3: Iztrivane na student po fakulteten nomer");
		printf("\n4: Izvejdane na spisuk na studentite ot zadadena grupa, podredeni po azbuchen red");
		printf("\n8: Izhod.");

		printf("\nIntput:");
		scanf("%d", &temp);

		if (temp == 1)
			head = dobavqne(head);
		if (temp == 2)
			tursene_po_familiq(head);
		if (temp == 3)
			head = iztrivane_po_facnomer(head);
		if (temp == 4)
			izvejdane_po_grupa(head);



		if (temp == 8)
			break;
	}





	struct node *p = NULL;
	p = (struct node *)malloc(sizeof(struct node));

	for (p = head; p != NULL; p = p->next){
		printf("\nIme: %s %s %s", p->std.FirstName, p->std.MiddleName, p->std.LastName);

		printf("\nFaculteten nomer: %d", p->std.FacNumber);

		printf("\nFakultet: %s", p->std.faculty);

		printf("\nSpecialnost: %s", p->std.specialty);

		printf("\nGrupa: %d", p->std.group);

		printf("\nKurs: %d", p->std.course);

		printf("\n-----------------------------------------");
	}
	printf("\n");

	return 0;
}

