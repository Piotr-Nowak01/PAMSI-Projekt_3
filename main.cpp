#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "Gra.h"
using namespace std;
class Menu
{
	public:
	Menu()
	{
		wyswietlMenu();	
	}
	void wyswietlMenu();
	void zasady();
};
int main(){
	Menu menu;
}
void Menu::wyswietlMenu()
{
	int wybor=0;
	while(wybor!=3)
	{
		system("cls");
		cout<<" Gra w statki z komputerem"<<endl;
		cout<<" Menu: "<<endl;
		cout<<"\t 1. Zagraj"<<endl<<"\t 2. Zasady gry"<<endl<<"\t 3. Wyjdz z gry."<<endl;
		cin>>wybor;
		switch(wybor)
		{
			case 1:
			{
				system("cls");
				Gra gra;
				break;
			}
			case 2:
			{
				system("cls");
				zasady();
				break;			}
			case 3:
			{
				system ("cls");
				cout<<"\t Wybrano wyjscie z gry. Milego dnia."<<endl;
				break;
			}
			default:
			{
				system("cls");
				cout<<"\t Zla liczba. Sprobuj ponownie.";
				Sleep(3000);
				system("cls");
				break;
			}
			break;
		}
	}
}
void Menu::zasady()
{
	cout<<"Zasady: "<<endl;
	cout<<"\t Twoim zadaniem jest zatopienie statkow przeciwnika."<<endl;
	cout<<"\t Rozstawic musisz 1 statek 4masztowy, 2 statki 3masztowe, 3 statki 2masztowe i 4 statki 1masztowe"<<endl;
	cout<<"\t Statki nie moga sie stykac."<<endl;
	cout<<"\t Strzelasz na zmiane z komputerem. Nie masz dodatkowego strzalu po trafieniu."<<endl;
	cout<<"\t Wygrywa ten, kto pierwszy zestrzeli wszystkie statki przeciwnika"<<endl;
}
