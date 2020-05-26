#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include "Pole.h"
using namespace std;

Pole::Pole()
{
	tablica=new char * [rozmiar_tablicy];
	for(int i=0; i< rozmiar_tablicy; i++)
	{
		tablica[i]=new char [rozmiar_tablicy];
	}
	inicializuj( tablica, rozmiar_tablicy);
}
Pole::~Pole()
{
	for (int i=0; i< rozmiar_tablicy; i++)
	{
		delete [] tablica[i];
	}
	delete [] tablica;
	tablica = NULL;
}
void Pole::inicializuj(char **tablica, const int rozmiar_tablicy)
{
	for(int i=0; i<rozmiar_tablicy; i++)
	{
		for (int j=0; j<rozmiar_tablicy; j++)
		{
			tablica[i][j]='.';
		}
	}
}
void Pole::wyswietl_pole(bool widzialnosc)
{
	cout<<"_  ";
    for(int i=1;i<rozmiar_tablicy-1;i++)
	{
		cout<<i<<"  ";
	}
	cout<<endl;
	for (int i=1; i<rozmiar_tablicy-1; i++)
	{
		cout<<i;
		for(int j=1; j<rozmiar_tablicy-1;j++)
		{
			if (widzialnosc)
			{
				cout<<(((i>9)&&(j<2))?" ":"  ")<<tablica[i][j];
			}
			else
			{
				cout<<(((i>9)&&(j<2))?" ":"  ")<<((tablica[i][j]=='8')?'.':tablica[i][j]);
			}
		}
		cout<<endl;
	}
    cout<<"___________________________"<<endl;
}
