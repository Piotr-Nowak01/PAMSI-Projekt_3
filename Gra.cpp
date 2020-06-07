#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include "Gra.h"
#include "Statek.h"
#include "Pole.h"
using namespace std;
int Gra::trafienia_gracza=0;
int Gra::trafienia_przeciwnika=0;
Gra::Gra()
{
	srand(time(NULL));
	int wybor;
	while(1)
	{
		cout<<"Czy chcesz widziec statki przeciwnika?"<<endl<<"1 - tak"<<endl<<"2 - nie"<<endl;
		cin>>wybor;
		if(wybor==1)
		{
			czy_widoczne=true;
			break;
		}
		else if( wybor==2)
		{
			czy_widoczne=false;
			break;
		}
	}
	system("cls");
	Gra::ustaw_statki_gracza(pole_gracza,fragmenty_gracza);
	Gra::ustaw_statki_pc(pole_przeciwnika,fragmenty_przeciwnika);
	Gra::gra_petla(pole_przeciwnika,fragmenty_przeciwnika,pole_gracza,fragmenty_gracza);
	cout<<"Koniec gry!"<<endl;
}
void Gra::wyswietl_dane_statkow(Statek *fragmenty_przeciwnika, int ile_fragmentow)
{
	for(int i=0; i<ile_fragmentow;i++)
	{
		fragmenty_przeciwnika[i].wyswietl_dane();
	}
}
void Gra::gra_petla(Pole *pole_przeciwnika, Statek *fragmenty_przeciwnika, Pole *pole_gracza, Statek *fragmenty_gracza)
{
	while(true)
	{
		strzelanie_gracza(pole_przeciwnika,fragmenty_przeciwnika);
		cout<<" Ile razy trafil gracz: "<<trafienia_gracza<<endl;
		if(trafienia_gracza==ile_fragmentow)
		{
			system("cls");
			cout<<"Wygrales! Gratulacje!"<<endl;
			Sleep(5000);
			break;
		}
		cout<<"________________________"<<endl<<endl;
		strzelanie_komputera(pole_gracza,fragmenty_gracza);
		cout<<" Ile razy trafil komputer: "<<trafienia_przeciwnika<<endl;
		if(trafienia_przeciwnika==ile_fragmentow)
		{
			system("cls");
			cout<<"Przegrales! Sprobuj ponownie"<<endl;
			Sleep(5000);
			break;
		}
	}
}
void Gra::strzelanie_gracza(Pole *pole_przeciwnika, Statek *fragmenty_przeciwnika)
{
	cout<<" Pole przeciwnika: "<<endl;
	pole_przeciwnika->wyswietl_pole(czy_widoczne);
	cout<<"Podaj wspolrzedna x do ostrzalu [1-10]"<<endl;
	int tem_x=Gra::get_koordynaty((pole_przeciwnika->get_rozmiar_tablicy())-2);
	cout<<"Podaj wspolrzedna y do ostrzalu [1-10]"<<endl;
	int tem_y=Gra::get_koordynaty((pole_przeciwnika->get_rozmiar_tablicy())-2);
	system("cls");
	if(pole_przeciwnika->get_pole(tem_x, tem_y)=='8')
	{
		int ktory_fragment=co_trafiono(tem_x,tem_y,fragmenty_przeciwnika,ile_fragmentow);
		zwieksz_obrazenia(fragmenty_przeciwnika, fragmenty_przeciwnika[ktory_fragment].get_id());
		if (fragmenty_przeciwnika[ktory_fragment].get_obrazenia()==fragmenty_przeciwnika[ktory_fragment].get_dlugosc())
		{
			cout<<"Lodz zatopiona!"<<endl;
			wykluczenie_pozycji(pole_przeciwnika, fragmenty_przeciwnika, ktory_fragment, fragmenty_przeciwnika[ktory_fragment].get_id());
		}
		else
		{
			cout<<"Lodz trafiona, lecz nie zatopiona"<<endl;
		}
		pole_przeciwnika->ustaw_pole(tem_x, tem_y, 'X');
		trafienia_gracza++;
	}
	else if(pole_przeciwnika->get_pole(tem_x,tem_y)=='X' || pole_przeciwnika->get_pole(tem_x,tem_y)=='*')
	{
		cout<<"Zmarnowalismy strzal kapitanie!"<<endl;
	}
	else
	{
		cout<<"Pudlo!"<<endl;
		pole_przeciwnika->ustaw_pole(tem_x,tem_y,'*');
	}
}
void Gra::strzelanie_komputera(Pole *pole_gracza,Statek *fragmenty_gracza)
{
	int tem_x,tem_y;
	while(1)
	{
		tem_x=rand()%10+1;
		tem_y=rand()%10+1;
		if(pole_gracza->get_pole(tem_x,tem_y)=='.' || pole_gracza->get_pole(tem_x,tem_y)=='8')
		{
			break;
		}
	}
	if (pole_gracza->get_pole(tem_x,tem_y)=='8')
	{
		int ktory_fragment=co_trafiono(tem_x,tem_y,fragmenty_gracza,ile_fragmentow);
		zwieksz_obrazenia(fragmenty_gracza, fragmenty_gracza[ktory_fragment].get_id());
		if (fragmenty_gracza[ktory_fragment].get_obrazenia()==fragmenty_gracza[ktory_fragment].get_dlugosc())
		{
			cout<<"Komputer zatopil lodz!"<<endl;
			wykluczenie_pozycji(pole_gracza, fragmenty_gracza, ktory_fragment, fragmenty_gracza[ktory_fragment].get_id());
		}
		else
		{
			cout<<"Komputer trafil, lecz nie zatopil."<<endl;
		}
		pole_gracza->ustaw_pole(tem_x, tem_y, 'X');
		trafienia_przeciwnika++;
	}
	else
	{
		cout<<"Komputer pudluje!"<<endl;
		pole_gracza->ustaw_pole(tem_x,tem_y,'*');
	}
	cout<<" Widok komputera: "<<endl;
	pole_gracza->wyswietl_pole(true);
}
void Gra::wykluczenie_pozycji(Pole *pole_przeciwnika, Statek *fragnenty_przeciwnika, int ktory_fragment,int id)
{
	int start_x, start_y;
	int orientacja = fragmenty_przeciwnika[ktory_fragment].get_orientacja(); 
	for (int i=0; i<ile_fragmentow;i++)
	{
		if(fragmenty_przeciwnika[i].get_id()==id)
		{
			start_x=fragmenty_przeciwnika[i].get_x();
			start_y=fragmenty_przeciwnika[i].get_y();
			break;		
		}
	}
	if(orientacja)
	{
		for (int i=0; i<(2+fragmenty_przeciwnika[ktory_fragment].get_dlugosc());i++)
		{
			pole_przeciwnika->ustaw_pole(start_x-1,start_y-1+i,'*');
			pole_przeciwnika->ustaw_pole(start_x+1,start_y-1+i,'*');
			pole_przeciwnika->ustaw_pole(start_x,start_y-1,'*');
			pole_przeciwnika->ustaw_pole(start_x,start_y+(fragmenty_przeciwnika[ktory_fragment].get_dlugosc()),'*');
		}
	}
	else
	{
		for (int i=0; i<(2+fragmenty_przeciwnika[ktory_fragment].get_dlugosc());i++)
		{
			pole_przeciwnika->ustaw_pole(start_x-1+i,start_y-1,'*');
			pole_przeciwnika->ustaw_pole(start_x-1,start_y,'*');
			pole_przeciwnika->ustaw_pole(start_x+(fragmenty_przeciwnika[ktory_fragment].get_dlugosc()),start_y,'*');
			pole_przeciwnika->ustaw_pole(start_x-1+i,start_y+1,'*');
		}
	}
}
void Gra::zwieksz_obrazenia(Statek *fragmenty_przeciwnika, int id)
{
	for(int i=0; i<ile_fragmentow;i++)
	{
		if(fragmenty_przeciwnika[i].get_id()==id)
		{
			fragmenty_przeciwnika[i].zwieksz_obrazenia();
		}
	}
}
int Gra::co_trafiono(int x, int y, Statek *fragmenty_przeciwnika, int ile_fragmentow)
{
	int i=0;
	for(i=0;i<ile_fragmentow;i++)
	{
		if(fragmenty_przeciwnika[i].get_x()==x && fragmenty_przeciwnika[i].get_y()==y)
		{
			break;
		}
	}
	return i;
}
Gra::~Gra()
{
	delete [] fragmenty_przeciwnika;
	fragmenty_przeciwnika=NULL;
}
short int Gra::get_koordynaty(int max)
{
	int tem;
	do
	{
		cin>>tem;
		if(tem<1 ||tem>max)
		{
			cout<<"Blad! Wprowadz jeszcze raz"<<endl;
		}
		else
		{
			break;
		}
	}while(true);
	return tem;
}
bool Gra::pobierz_orientacje(int wielkosc)
{
	int wybor;
	while(true)
	{
		cout<<"Podaj plaszczyzne ustawienia "<<wielkosc<<"masztowca. ( 1 - pion, 0 - poziom)"<<endl;
		cin>>wybor;
		if(wybor==1)
		{
			return true;
		}
		else if(wybor==0)
		{
			return false;
		}
		else
		{
			cout<<"Nieprawidlowa liczba!"<<endl;
		}
	}
}
bool Gra::czy_pole_puste(Pole *pole_przeciwnika, int x, int y)
{
	if( (pole_przeciwnika->get_pole(x-1,y-1)=='.' || pole_przeciwnika->get_pole(x-1,y-1)=='*' ) &&	(pole_przeciwnika->get_pole(x,y-1)=='.' || pole_przeciwnika->get_pole(x,y-1)=='*' ) &&
		(pole_przeciwnika->get_pole(x+1,y-1)=='.' || pole_przeciwnika->get_pole(x+1,y-1)=='*' ) &&	(pole_przeciwnika->get_pole(x-1,y)=='.' || pole_przeciwnika->get_pole(x-1,y)=='*' ) &&	
		(pole_przeciwnika->get_pole(x,y)=='.' || pole_przeciwnika->get_pole(x,y)=='*' )         &&	(pole_przeciwnika->get_pole(x+1,y)=='.' || pole_przeciwnika->get_pole(x+1,y)=='*' ) &&
	    (pole_przeciwnika->get_pole(x-1,y+1)=='.' || pole_przeciwnika->get_pole(x-1,y+1)=='*' ) &&	(pole_przeciwnika->get_pole(x,y+1)=='.' || pole_przeciwnika->get_pole(x,y+1)=='*' ) &&
		(pole_przeciwnika->get_pole(x+1,y+1)=='.' || pole_przeciwnika->get_pole(x+1,y+1)=='*' ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Gra::ustaw_statki_pc(Pole *pole_przeciwnika, Statek *fragmenty_przeciwnika)
{
	int tem_x,tem_y;
	bool orientacja;
	int ilosc_statkow=0;
	int ile_ustawiono=0;
	int pozycja_statku=0;
	orientacja=rand()%2;
	if(orientacja)	//ustawienie 4masztowca
	{
		tem_x=rand()%10+1;
		tem_y=rand()%7+1;
		for(int i=0;i<4;i++,pozycja_statku++)
		{
			pole_przeciwnika->ustaw_pole(tem_x,tem_y+i,'8');
			fragmenty_przeciwnika[pozycja_statku].ustaw_parametry(1+ile_ustawiono,tem_x,tem_y+i,4,0,orientacja);
		}
	}
	else
	{
		tem_x=rand()%7+1;
		tem_y=rand()%10+1;
		for(int i=0;i<4;i++,pozycja_statku++)
		{
			pole_przeciwnika->ustaw_pole(tem_x+i,tem_y,'8');
			fragmenty_przeciwnika[pozycja_statku].ustaw_parametry(1+ile_ustawiono,tem_x+i,tem_y,4,0,orientacja);
		}
	}
	ile_ustawiono++;
	while(ilosc_statkow<2)
	{
		while(true)		// wykonuj a¿ nie ustawisz statku
		{
			while(true)	// losuj a¿ wspó³rzêdne nie bêd¹ wolne
			{
				tem_x=rand()%8+1;
				tem_y=rand()%8+1;
				if(czy_pole_puste(pole_przeciwnika,tem_x,tem_y))
				{
					break;
				}
			}
			if(czy_pole_puste(pole_przeciwnika,tem_x+2,tem_y))
			{
				for(int i=0;i<3;i++,pozycja_statku++)
				{
					pole_przeciwnika->ustaw_pole(tem_x+i,tem_y,'8');
					fragmenty_przeciwnika[pozycja_statku].ustaw_parametry(1+ile_ustawiono,tem_x+i,tem_y,3,0,0);
				}
				break;
			}
			else if (czy_pole_puste(pole_przeciwnika,tem_x,tem_y+2))
			{
				for(int i=0;i<3;i++,pozycja_statku++)
				{
					pole_przeciwnika->ustaw_pole(tem_x,tem_y+i,'8');
					fragmenty_przeciwnika[pozycja_statku].ustaw_parametry(1+ile_ustawiono,tem_x,tem_y+i,3,0,1);
				}
				break;
			}
		}
		ilosc_statkow++;
		ile_ustawiono++;
	}
	ilosc_statkow=0;
	while(ilosc_statkow<3)
	{
		while(true)		// wykonuj a¿ nie ustawisz statku
		{
			while(true)	// losuj a¿ wspó³rzêdne nie bêd¹ wolne
			{
				tem_x=rand()%9+1;
				tem_y=rand()%9+1;
				if(czy_pole_puste(pole_przeciwnika,tem_x,tem_y))
				{
					break;
				}
			}
			if(czy_pole_puste(pole_przeciwnika,tem_x+1,tem_y))
			{
				for(int i=0;i<2;i++,pozycja_statku++)
				{
					pole_przeciwnika->ustaw_pole(tem_x+i,tem_y,'8');
					fragmenty_przeciwnika[pozycja_statku].ustaw_parametry(1+ile_ustawiono,tem_x+i,tem_y,2,0,0);
				}
				break;
			}
			else if (czy_pole_puste(pole_przeciwnika,tem_x,tem_y+1))
			{
				for(int i=0;i<2;i++,pozycja_statku++)
				{
					pole_przeciwnika->ustaw_pole(tem_x,tem_y+i,'8');
					fragmenty_przeciwnika[pozycja_statku].ustaw_parametry(1+ile_ustawiono,tem_x,tem_y+i,2,0,1);
				}
				break;
			}
		}
		ilosc_statkow++;
		ile_ustawiono++;
	}
	ilosc_statkow=0;	
	while(ilosc_statkow<4)
	{
			while(true)	// losuj a¿ wspó³rzêdne nie bêd¹ wolne
			{
				tem_x=rand()%10+1;
				tem_y=rand()%10+1;
				if(czy_pole_puste(pole_przeciwnika,tem_x,tem_y))
				{
					pole_przeciwnika->ustaw_pole(tem_x,tem_y,'8');
					fragmenty_przeciwnika[pozycja_statku].ustaw_parametry(1+ile_ustawiono,tem_x,tem_y,1,0,0);
					if(pozycja_statku<19)
					{
						pozycja_statku++;
					}
					break;
				}
			}
		ilosc_statkow++;
		ile_ustawiono++;
	}	
}
void Gra::ustaw_statki_gracza(Pole *pole_gracza, Statek *fragmenty_gracza)
{
	int tem_x,tem_y;
	bool orientacja;
	int ilosc_statkow=0;
	int ile_zbudowano=0;
	int pozycja_statku=0;
	int rozmiar_obecnego_statku=4;
	orientacja=pobierz_orientacje(rozmiar_obecnego_statku);
	cout<<"Podaj wspolrzedna x do ustawienia statku"<<endl;
	tem_x=Gra::get_koordynaty(orientacja?10:7);
	cout<<"Podaj wspolrzedna y do ustawienia statku"<<endl;
	tem_y=Gra::get_koordynaty(orientacja?7:10);
	if (orientacja)
	{
		for(int i=0; i<rozmiar_obecnego_statku;i++,pozycja_statku++)
		{
			pole_gracza->ustaw_pole(tem_x,tem_y+i,'8');
			fragmenty_gracza[pozycja_statku].ustaw_parametry(1+ile_zbudowano,tem_x,tem_y+i,rozmiar_obecnego_statku,0,orientacja);
		}
	}
	else
	{
		for(int i=0; i<rozmiar_obecnego_statku;i++,pozycja_statku++)
		{
			pole_gracza->ustaw_pole(tem_x+i,tem_y,'8');
			fragmenty_gracza[pozycja_statku].ustaw_parametry(1+ile_zbudowano,tem_x+i,tem_y,rozmiar_obecnego_statku,0,orientacja);
		}
	}
	ile_zbudowano++;
	pole_gracza->wyswietl_pole(1);
	rozmiar_obecnego_statku=3;
	while(ilosc_statkow<2)
	{
		while(1)
		{
			while(1)
			{
				orientacja=pobierz_orientacje(rozmiar_obecnego_statku);
				cout<<"Podaj wspolrzedna x do ustawienia statku"<<endl;
				tem_x=Gra::get_koordynaty(orientacja?10:8);
				cout<<"Podaj wspolrzedna y do ustawienia statku"<<endl;
				tem_y=Gra::get_koordynaty(orientacja?8:10);
				if( czy_pole_puste(pole_gracza,tem_x,tem_y) &&  czy_pole_puste(pole_gracza,(orientacja?tem_x:(tem_x+2)),(orientacja?(tem_y+2):tem_y)))
				{
					break;
				}
			}
			if(!orientacja)
			{
				for(int i=0;i<rozmiar_obecnego_statku;i++,pozycja_statku++ )
				{
					pole_gracza->ustaw_pole(tem_x+i, tem_y, '8');
					fragmenty_gracza[pozycja_statku].ustaw_parametry(1+ile_zbudowano,tem_x+i,tem_y,rozmiar_obecnego_statku,0,0);
				}
				break;
			}
			else
			{
				for(int i=0;i<rozmiar_obecnego_statku;i++,pozycja_statku++ )
				{
					pole_gracza->ustaw_pole(tem_x, tem_y+i, '8');
					fragmenty_gracza[pozycja_statku].ustaw_parametry(1+ile_zbudowano,tem_x,tem_y+i,rozmiar_obecnego_statku,0,1);
				}
				break;
			}
		}
		ilosc_statkow++;
		ile_zbudowano++;
		pole_gracza->wyswietl_pole(1);
	}
	ilosc_statkow=0;
	rozmiar_obecnego_statku=2;
	while(ilosc_statkow<3)
	{
		while(1)
		{
			while(1)
			{
				orientacja=pobierz_orientacje(rozmiar_obecnego_statku);
				cout<<"Podaj wspolrzedna x do ustawienia statku"<<endl;
				tem_x=Gra::get_koordynaty(orientacja?10:9);
				cout<<"Podaj wspolrzedna y do ustawienia statku"<<endl;
				tem_y=Gra::get_koordynaty(orientacja?9:10);
				if( czy_pole_puste(pole_gracza,tem_x,tem_y) &&  czy_pole_puste(pole_gracza,(orientacja?tem_x:(tem_x+1)),(orientacja?(tem_y+1):tem_y)))
				{
					break;
				}
			}
			if(!orientacja)
			{
				for(int i=0;i<rozmiar_obecnego_statku;i++,pozycja_statku++ )
				{
					pole_gracza->ustaw_pole(tem_x+i, tem_y, '8');
					fragmenty_gracza[pozycja_statku].ustaw_parametry(1+ile_zbudowano,tem_x+i,tem_y,rozmiar_obecnego_statku,0,0);
				}
				break;
			}
			else
			{
				for(int i=0;i<rozmiar_obecnego_statku;i++,pozycja_statku++ )
				{
					pole_gracza->ustaw_pole(tem_x, tem_y+i, '8');
					fragmenty_gracza[pozycja_statku].ustaw_parametry(1+ile_zbudowano,tem_x,tem_y+i,rozmiar_obecnego_statku,0,1);
				}
				break;
			}
		}
		ilosc_statkow++;
		ile_zbudowano++;
		pole_gracza->wyswietl_pole(1);
	}
	ilosc_statkow=0;
	while(ilosc_statkow<4)
	{
		while(1)
		{
			orientacja=0;
			cout<<"Podaj wspolrzedna x do ustawienia statku"<<endl;
			tem_x=Gra::get_koordynaty(10);
			cout<<"Podaj wspolrzedna y do ustawienia statku"<<endl;
			tem_y=Gra::get_koordynaty(10);
			if(czy_pole_puste(pole_gracza,tem_x,tem_y) )
			{
				pole_gracza->ustaw_pole(tem_x,tem_y,'8');
				fragmenty_gracza[pozycja_statku].ustaw_parametry(1+ile_zbudowano,tem_x,tem_y,1,0,0);
				if(pozycja_statku<19)
				{
					pozycja_statku++;
				}
				break;
			}
		}
		ilosc_statkow++;
		ile_zbudowano++;
		pole_gracza->wyswietl_pole(1);
	}
	system("cls");
	cout<<" Koniec ustawiania statkow. Wcisnij dowolny klawisz. "<<endl<<endl;
	getch();
}
