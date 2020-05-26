#include "Statek.h"
#include <iostream>
using namespace std;
Statek::Statek()
{
	ustaw_parametry(0,0,0,0,0,0);
}
Statek::~Statek()
{	
}
void Statek::wyswietl_dane()
{
	cout<<"Id statku: "<<id<<endl;
	cout<<"Wspolrzedna x:  "<<x<<endl;
	cout<<"Wspolrzedna y: "<<y<<endl;
	cout<<"Dlugosc: "<<dlugosc<<endl;
	cout<<"Obrazenia: "<<obrazenia<<endl;
	cout<<"Orientacja: "<<orientacja<<endl;
}
void Statek::ustaw_parametry(int id, int x, int y, int dlugosc, int obrazenia, int orientacja)
{
	this->id=id;
	this->x=x;
	this->y=y;
	this->dlugosc=dlugosc;
	this->obrazenia=obrazenia;
	this->orientacja=orientacja;
}
