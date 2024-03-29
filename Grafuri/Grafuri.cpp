#include "stdafx.h"
#include<string.h>
#include<stdio.h>

int matrice[100][100],nrMax=0,vizitat[10], nrComponente=1,marc[10],elem,count1,nrConexe,var=-1,numara=0,marc1[1000];
char nod1, nod2, i[10], vectElem[10];

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Citire, adaugare,afisare~~~~~~~~~~~~~~~~~~~~~~~~
void InitilizareVectElem()
{
	int i, j,count=0;
	for (i = 0; i <= nrMax; i++)
		if (var == -1)
			vectElem[i] ='*';
		else
			vectElem[var] = '*';

	for (i = 0; i <= nrMax; i++)
		for (j = 0; j <= nrMax; j++)
			if (matrice[i][j] != 0)
				vectElem[i] = i + 65;

	printf("\n");

	for (i = 0; i <= nrMax; i++)
		printf("%c ", vectElem[i]);

	printf("\n");

	while (count != 2*nrMax+3)
	{
		printf("-");
		count++;
	}

	printf("\n");
}


void afisareMatrice()
{
	int i, j;
	InitilizareVectElem();

	for (i = 0; i <= nrMax; i++)
	{
		for (j = 0; j <= nrMax; j++)
			printf("%d ", matrice[i][j]);
		printf("|%c \n",vectElem[i]);
	}

}


void adaugareArc()
{
	int linie, coloana;
	linie = nod1 - 65;
	coloana = nod2 - 65;

	matrice[linie][coloana] = 1;
	matrice[coloana][linie] = 1;

	if (nrMax < linie)
		nrMax = linie;
	if (nrMax < coloana)
		nrMax = coloana;
}


void citire()
{
	FILE* fisier;
	fisier = fopen("fisier.txt","r");

	if (fisier)
	{
		while (fgets(i, 10, fisier) != NULL)
		{
			printf("%c %c \n", i[0], i[1]);
			nod1 = i[0];
			nod2 = i[1];

			adaugareArc();
		}
		fclose(fisier);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Componente conexe, parcurgeri in adancime si in latime~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int verifica(int linie)
{
	int j;
	for (j = 0; j <= nrMax; j++)
		if (matrice[linie][j] == 1 && vizitat[j] != 0)
			return 1;
	return 0;
}

int nrComponenteConexe(int i)
{
	int j,nr=0;
	while (nr != nrMax)
	{
		for (j = 0; j <= nrMax; j++)
		{
			if (matrice[i][j] == 1)
			{
				vizitat[i] = 1;
				i = j;
			}
		}

		nr++;
	}

	for (j = 0; j <= nrMax; j++)
	{
		if (vizitat[j] == 0 && verifica(j) == 0)
		{
			nrComponente++;
			nrComponenteConexe(j);
		}
		else
			vizitat[j] = 1;
	}


	return nrComponente;
}


int verifica1(int linie)
{
	int j;
	for (j = 0; j <= nrMax; j++)
		if (matrice[linie][j] == 1 && marc[j] != 0)
			return 1;
	return 0;
}

void parcurgere_adancime(int k)
{
	int j;
	marc[k] = 1;
	printf("Trece prin nodul %c \n", k+65);

	for (int x = 1; x <= nrMax; x++)
		if (matrice[k][x] == 1) 
			if (marc[x] == 0)  
				parcurgere_adancime(x);

//~~~~~~~~~~~~~~~~~~~~~de aici ii pt neconex~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	for (j = 0; j <= nrMax; j++)
	{
		if (marc[j] == 0)
		{
			if (verifica1(j) == 0)
				printf("\nAlta componenta conexa: \n");
			parcurgere_adancime(j);
		}

	}
}

//merge si cea de pe campus, dar trebuie adaugate niste cond
/*
void CautaInAdancime(int i)
{

	int j;

	marc[i] = 1;
	printf("%c ", i + 65);
	for (j = 0; j <= nrMax; j++)
		if (matrice[i][j] == 1)
		{
			if (marc[j] == 0)
				CautaInAdancime(j);

		}
}

void TraversareInAdancime()
{
	int i;

	for (i = 0; i <=nrMax; i++)
		marc[i] = 0;

	for (i = 0; i <=nrMax; i++)
		if (marc[i] == 0)
		{
			CautaInAdancime(i);
			nrConexe++;
		}
}
*/




/*

void CautaPrinCuprindere( int x)
{

	//CoadaNoduri Q;
	int Q[20];
	int  y;

//	ADAUGA(Q, x);
	Q[numara] = x;
	numara++;
	while (numara!= 0)
	{
		//x = SCOATE(Q);
		x = Q[numara];
		Q[numara] = 0;
		marc1[x] = 1;
		numara--;
		for (y=0;y<=nrMax;y++)
			if (marc1[y] == 0 && matrice[x][y]==1) 
			{
				marc1[y] = 1; 
				Q[numara] = x;
				numara++;
				//ADAUGA(Q, y);
			}
	}
}

void TraversarePrinCuprindere()
{
	int x;

	for (x = 0; x <= nrMax; x++)
		marc1[x] =0; 

	for (x=0;x<=nrMax;x++)
		if (marc1[x] == 0) 
			CautaPrinCuprindere( x);
}
*/

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Grad, suprimare~~~~~~~~~~~~~~~~~~~~~~~~~~~

void grad()
{
  
	int m = 0,j;
	while (m != nrMax+1)
	{
		int gr = 0;
		for (j = 0; j <= nrMax; j++)
		{
			if (matrice[m][j] == 1)
				gr++;
		}
		printf("Nodul %c are gradul %d\n", m + 65, gr);
		m++;
	}


}

void suprimare(char nod)
{
	int l;
    var = nod - 65;
	for (l = 0; l <= nrMax; l++)
	{
		matrice[var][l] = 0;
		matrice[l][var] = 0;
	}
	printf("\nMatricea arata asa dupa suprimare:");
	afisareMatrice();

}

int main()
{

	citire();
	afisareMatrice();
	printf("\nNumarul de componente conexe este: %d \n\n",nrComponenteConexe(0));
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARCURGEREA IN ADANCIME~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	parcurgere_adancime(0);
	//TraversareInAdancime();
	printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~GRADUL FIECARUI NOD~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	grad();
	suprimare('A');
	//TraversarePrinCuprindere();
	getchar();
    return 0;
}

