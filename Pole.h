#ifndef Pole_h
#define Pole_h
class Pole
{
	private:
		char **tablica;
		const int rozmiar_tablicy=12;
	public:
		Pole();
		virtual ~Pole();
	
		void inicializuj(char **tablica, const int rozmiar_tablicy);
		void wyswietl_pole( bool widzialnosc);
		char get_pole(int x, int y)
		{
			return tablica[y][x];
		}
		void ustaw_pole(int x, int y, char pole)
		{
			tablica[y][x]=pole;
		}
		const int get_rozmiar_tablicy()
		{
			return rozmiar_tablicy;
		}
};
#endif
