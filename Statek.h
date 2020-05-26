#ifndef Statek_h
#define Statek_h
class Statek
{
	private:
		int id;
		int x;
		int y;
		int dlugosc;
		int obrazenia;
		int orientacja;
	public:
		Statek();
		void ustaw_parametry( int id, int x, int y, int dlugosc,int obrazenia, int orientacja);
		void wyswietl_dane();
		virtual ~Statek();
		
		int get_id()
		{
			return id;
		}
		void ustaw_id(int id)
		{
			this->id=id;
		}
		
		int get_x()
		{
			return x;
		}
		void ustaw_x(int x)
		{
			this->x=x;
		}
		
		int get_y()
		{
			return y;
		}
		void ustaw_y(int y)
		{
			this->y=y;
		}
		
		int get_dlugosc()
		{
			return dlugosc;
		}
		void ustaw_dlugosc(int dlugosc)
		{
			this->dlugosc=dlugosc;
		}
		
		int get_obrazenia()
		{
			return obrazenia;
		}
		void ustaw_obrazenia(int obrazenia)
		{
			this->obrazenia=obrazenia;
		}
		void zwieksz_obrazenia()
		{
			obrazenia++;
		}
		
		int get_orientacja()
		{
			return orientacja;
		}
		void ustaw_orientacja(int orientacja)
		{
			this->orientacja=orientacja;
		}
};
#endif
