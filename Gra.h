#ifndef Gra_h
#define Gra_h
#include "Pole.h"
#include "Statek.h"
class Gra
{
	private:
		static const int ile_statkow=10;
		static const int ile_fragmentow=20;
		Pole *pole_przeciwnika = new Pole();
		Pole *pole_gracza= new Pole();
		Statek *fragmenty_przeciwnika = new Statek [ile_fragmentow];
		Statek *fragmenty_gracza=new Statek [ile_fragmentow];
		bool czy_widoczne;
		static int trafienia_gracza;
		static int trafienia_przeciwnika;
	public:
		Gra();
		virtual ~Gra();
		void gra_petla ( Pole *pole_przeciwnika, Statek *fragmenty_przeciwnika, Pole *pole_gracza, Statek *fragmenty_gracza);
		void strzelanie_gracza (Pole *pole_przeciwnika, Statek *fragmenty_przeciwnika);
		void strzelanie_komputera (Pole *pole_gracza, Statek *fragmenty_gracza);
		void ustaw_statki_pc (Pole *pole_przeciwnika, Statek *fragmenty_przeciwnika);
		void ustaw_statki_gracza (Pole *pole_gracza, Statek *fragmenty_gracza);
		void wyswietl_dane_statkow (Statek *fragmenty_przeciwnika, int ile_fragmentow);
		short int get_koordynaty( int max);
		bool czy_pole_puste(Pole *pole_przeciwnika, int x, int y);
		int co_trafiono (int x, int y, Statek *fragmenty_przeciwnika, int ile_fragmentow);
		void zwieksz_obrazenia(Statek *fragmenty_przeciwnika, int id);
		void wykluczenie_pozycji (Pole *pole_przeciwnika, Statek *fragmenty_przeciwnika, int ktory_fragment, int id);
		bool pobierz_orientacje (int wielkosc);
		
		void ustaw_widocznosc(int czy_widoczne)
		{
			this->czy_widoczne=czy_widoczne;
		}
		bool get_widocznosc()
		{
			return czy_widoczne;
		}
		void zwieksz_strzaly();
		short int ile_strzalow();
};
#endif
