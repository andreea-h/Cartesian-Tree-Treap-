#include<stdio.h>
#include<stdlib.h>
#include "sequence.h"

int main()
{
	Sequence secventa = init();
	secventa->size=-1; //primul element din secventa are size initial -1
	secventa = insert(secventa, 2,0);
	afisare(secventa);
	printf("\n");
	secventa = insert(secventa, 4,1);
	afisare(secventa);
	printf("\n");
	secventa = insert(secventa, 6,2);
	afisare(secventa);
	printf("\n");
	secventa = insert(secventa, 7,3);
	afisare(secventa);
	printf("\n");
	secventa = insert(secventa, 10,4);
	afisare(secventa);
	printf("\n");
	secventa = insert(secventa, 12,5);
	afisare(secventa); 
	printf("\n");
	secventa = insert(secventa, 13,0);
	afisare(secventa); 
	printf("\n");
	secventa = insert(secventa, 22, 7);
	afisare(secventa); 
	printf("\n");
	secventa = insert(secventa, 23, 3);
	afisare(secventa);
	printf("\n");
	secventa = insert(secventa, 14,0);
	afisare(secventa); 
	printf("\n");
	secventa = insert(secventa, 33,5);
	afisare(secventa); 
	printf("\n");
	secventa = insert(secventa, 40,3);
	afisare(secventa); 
	printf("\n");

	//testarea functiei 'size'
	printf("------------------------------------------------\n");
	printf("Dimensiunea secventei este %d\n", size(secventa));
	printf("------------------------------------------------\n");

	//testare functia 'lookup'
	int i;
	for(i=0;i<secventa->size;i++){
		int l = lookup(secventa, i);
		printf("Elementul de pe pozitia %d este %d \n", i,l);
	}

  	//testarea functiei 'set'
  	printf("------------------------------------------------\n");
  	printf("Inlocuieste elementul de pe pozitia %d cu %d :\n", 0, 100);
  	secventa = set(secventa, 100,0);
  	afisare(secventa);
  	printf("\n");
  	printf("Inlocuieste elementul de pe pozitia %d cu %d :\n", 4, 200);
  	secventa = set(secventa, 200,4);
  	afisare(secventa);
  	printf("\n");
  	printf("------------------------------------------------\n");
  	printf("Inlocuieste elementul de pe pozitia %d cu %d :\n", 6, 300);
  	secventa = set(secventa, 300,6);
  	afisare(secventa);
  	printf("\n");
  	printf("------------------------------------------------\n");

  	//testarea functiei 'delete'
  	printf("Se elimina elementul de pe pozitia %d: \n",2);;
  	secventa=Delete(secventa, 2);
  	afisare(secventa);
  	printf("\n");
  	printf("Se elimina elementul de pe pozitia %d: \n",3);;
  	secventa=Delete(secventa, 3);
  	afisare(secventa);
  	printf("\n");
  	printf("Se elimina elementul de pe pozitia %d: \n",4);;
  	secventa=Delete(secventa, 4);
  	afisare(secventa);
  	printf("\n");
  	printf("Dimensiunea secventei este %d\n", size(secventa));
  	printf("------------------------------------------------\n");

  	///secventa2 este folosita pentru testarea functiilor 'concat' si split
	Sequence secventa2 = init();
	secventa2->size=-1;
	secventa2 = insert(secventa2, 87,0);
	secventa2 = insert(secventa2, 67,1);
	secventa2 = insert(secventa2, 34,2);
	secventa2 = insert(secventa2, 276,0);
	secventa2 = insert(secventa2, 43,4);
	secventa2 = insert(secventa2, 62,5);
	secventa2 = insert(secventa2, 89,3);
	printf("Prima secventa: ");
	afisare(secventa);
	printf("\n");
	printf("A doua secventa: ");
	afisare(secventa2);
	printf("\n");
	printf("Rezultatul concatenarii celor 2 secvente: ");
  	Sequence rezl=concat(secventa, secventa2);
  	afisare(rezl);
  	printf("\n");
    printf("------------------------------------------------\n");
  	printf("Aplicand operatia 'split' asupra primei secvente pentru index %d :\n", 4);
  	Sequence* separator = split(secventa, 4);
  	printf(" Subsecventa 1: ");
  	afisare(separator[0]);
  	printf("\n");
  	printf(" Subsecventa 2: ");
  	afisare(separator[1]);
  	printf("\n");
  	

  	
	


	return 0;
}