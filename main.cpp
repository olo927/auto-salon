#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <stdio.h>
#include <algorithm> 
#include <sstream>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;
/////////////////////////////////////
bool plikOtwarty = false;
static string nazwa_pliku_otwartego = "";
void zamkniecie();
/////////////////////////////////////
class Interface
{
	protected:
		string pierwszy_ekran;
		string drugi_ekran;
		string trzeci_ekran;
		string czwarty_ekran;
		string zacheta;
	public:
		Interface();
		void main_menu();
		void second_menu();
		void list_menu();
		void one_menu(int i);
		void back_to_second_menu();
		void zapisNaZadanie();
		
};

//////////////////////////////////////////
class Auto
{
	public:
		
		Auto();
		Auto(string words[]);
		void usun();
		void popraw_dane();	
		string GetElement(int i);
	protected:
		string marka;
		string model;
		string kraj_pochodzenia;
		int rok_produkcji;
		string nowy;
		int przebieg;
		int cena;
};
string Auto::GetElement(int i)
{
	stringstream ss;
	string  out;
	switch(i){
		case 1:
			return marka;
			break;
		case 2:
			return model;
			break;
		case 3:
			return kraj_pochodzenia;
			break;
		case 4:
			ss<<rok_produkcji;
			return ss.str();
			break;
		case 5:
			return nowy;
			break;
		case 6:
			ss<<przebieg;
			return ss.str();
			break;
		case 7:
			ss<<cena;
			return ss.str();
			break;
	}	
} 
Auto::Auto(string tab[])
{
	marka = tab[0];
	model = tab[1];  
	kraj_pochodzenia = tab[2];
	rok_produkcji = atoi(tab[3].c_str());
	nowy = tab[4];
	przebieg = atoi(tab[5].c_str());
	cena = atoi(tab[6].c_str());
}
Auto::Auto()
{
	system("cls");
	cout<<"Podaj Marke auta: ";
	cin>>marka;
	cout<<"Podaj model auta: ";
	cin>>model;
	cout<<"Podaj kraj pochodzenia auta: ";
	cin>>kraj_pochodzenia;
	cout<<"Podaj rok produkcji: ";
	cin>>rok_produkcji;
	cout<<"Nowy? ";
	cin>>nowy;
	do
	{
		cout<<"Podaj przebieg: ";
		cin>>przebieg;
	}while(przebieg<0);
	do
	{
		cout<<"Podaj cene: ";
		cin>>cena;
	}while(cena<0);
}

vector<Auto> vector_egzemplarzy;
/////////////////////////////////////////////
class OdczytZapisPliku
{
	public:
		void stworz_nowa();
		void pobierz();
		void zapisz();
};

void OdczytZapisPliku::stworz_nowa()
{
	system("cls");
	string nazwa_pliku;
	cout<<"Podaj nazwe pliku: ";
	cin>>nazwa_pliku;
	nazwa_pliku += ".txt";
	ofstream plik(nazwa_pliku.c_str());	//tworzenie pliku
	plikOtwarty = true;
	nazwa_pliku_otwartego = nazwa_pliku;
	Interface inter;
	inter.second_menu();
}

void OdczytZapisPliku::zapisz()
{	

	if(plikOtwarty)
	{
		char odpowiedz;
		do
		{
			cout<<"[T/N]Czy zapisac zmiany w pliku " << nazwa_pliku_otwartego << endl;
			cin>>odpowiedz;
		}while(odpowiedz!='n'&&odpowiedz!='N'&&odpowiedz!='t'&&odpowiedz!='T');
		if(odpowiedz == 'n'|| odpowiedz == 'N')
		{
			stworz_nowa();
			zapisz(); //wywo³ywanie jeszcze raz metody z nowym plikiem do zapisu .txt
		}
		else
		{
			ofstream plik(nazwa_pliku_otwartego.c_str());
			if(plik)
			{
				cout<<"Zapisuje";
				//wpisanie wszystkich elementow wektora do pliku
				for(int i = 0; i!=vector_egzemplarzy.size();i++)
				{
				plik<<vector_egzemplarzy.at(i).GetElement(1)<<"|"<<vector_egzemplarzy.at(i).GetElement(2)<<"|"
				<<vector_egzemplarzy.at(i).GetElement(3)<<"|"<<vector_egzemplarzy.at(i).GetElement(4)<<"|"
				<<vector_egzemplarzy.at(i).GetElement(5)<<"|"<<vector_egzemplarzy.at(i).GetElement(6)<<"|"<<vector_egzemplarzy.at(i).GetElement(7)<<endl;
				}	
			}			
		}
	}
	else
	{
		stworz_nowa();
		zapisz();
	}
}

void OdczytZapisPliku::pobierz()
{//przygotowanie do odczytu
	system("cls");
	cout<<"Podaj nazwe pliku do odczytu ";
	string nazwa_pliku;
	cin>>nazwa_pliku;
	nazwa_pliku+=".txt";
	nazwa_pliku_otwartego = nazwa_pliku;
	plikOtwarty = true;
	ifstream plik(nazwa_pliku.c_str());
	if(plik)
	{	
		vector_egzemplarzy.clear(); //czyszczenie wektora przed zaladowaniem nowych danych
		string linia;
		int licznik_slow = 0;
		while (getline(plik,linia))//dopoki jest mo¿liwloœæ pobierania linijki
		{	
			string words[7];
			licznik_slow = 0;
			for(int i = 0; i < linia.length(); i++)
			{
				if(linia[i]!='|')
				{
					words[licznik_slow] += linia[i];
				}
				else
				{
					licznik_slow++;
				}
			}
			Auto pojazd(words);
			vector_egzemplarzy.push_back(pojazd);
		}
		Interface inter;
		inter.second_menu();
	}
	else
	{
		char odpowiedz;
		do
		{
			cout<<"Blad, Czy chcesz stworzyc nowy plik? [T/N]";
			cin>>odpowiedz;
		}while(odpowiedz!='n'&&odpowiedz!='N'&&odpowiedz!='t'&&odpowiedz!='T');
		if(odpowiedz=='t'||odpowiedz=='T')
		{
			stworz_nowa();
		}
		else
		{
			Interface inter;
			inter.main_menu();
		}
	}
}
//////////////////////////////////////////////
class OdczytZapisVectora
{
	public:
		void stworz_nowa();
		void pobierz_spis();
		void wyswietl_pojedynczo(int i);
		void zapisz();
		void wyszukaj();
		void sortuj();
	private:
		int mini_menu();
		void rozpisz_auto(int i);
		void naglowek();
		void warunek_wyszukania_int(int i, int j,int wartosc);
		void warunek_wyszukania_stringa(int i, int odp,string wartosc);
		string wartosc_elementu(int j,int kryterium);
		void zamiana(int j);
};

void OdczytZapisVectora::rozpisz_auto(int i)
{
	cout<<i+1<<":"<<'\t'<<vector_egzemplarzy.at(i).GetElement(1)<<'\t'<<vector_egzemplarzy.at(i).GetElement(2)<<'\t'<<vector_egzemplarzy.at(i).GetElement(3)<<'\t'
					<<vector_egzemplarzy.at(i).GetElement(4)<<'\t'<<vector_egzemplarzy.at(i).GetElement(5)<<'\t'<<vector_egzemplarzy.at(i).GetElement(6)<<'\t'<<vector_egzemplarzy.at(i).GetElement(7)<<endl;
}
void OdczytZapisVectora::naglowek()
{
	system("cls");
	cout<<"nr"<<'\t'<<"marka"<<'\t'<<"model"<<'\t'<<"kraj"<<'\t'<<"rok"<<'\t'<<"nowy"<<'\t'<<"przeb."<<'\t'<<"cena"<<endl;
}
int OdczytZapisVectora::mini_menu()
{
	system("cls");
	cout<<"wyszukaj po:"<<endl;
	cout<<"1-marka"<<endl;
	cout<<"2-model"<<endl;
	cout<<"3-kraj_pochodzenia"<<endl;
	cout<<"4-rok_produkcji"<<endl;
	cout<<"5-nowy"<<endl;
	cout<<"6-przebieg"<<endl;
	cout<<"7-cena"<<endl;
	int kryterium;
	do{
		cout<< "podaj kryterium ";
		cin>>kryterium;	
	}while(kryterium<0 || kryterium>7);
	system("cls");
	return kryterium;
}
void OdczytZapisVectora::warunek_wyszukania_int(int i, int kryterium,int wartosc)
{
	if(atoi(wartosc_elementu(i,kryterium).c_str())==wartosc)
	{
		rozpisz_auto(i);
	}
}
void OdczytZapisVectora::warunek_wyszukania_stringa(int i, int kryterium,string wartosc)
{
	if(wartosc_elementu(i,kryterium)==wartosc)
	{
		rozpisz_auto(i);
	}
}
string OdczytZapisVectora::wartosc_elementu(int j, int kryterium) //zwraca wartoœæ kryterium j-tego auta
{
	return vector_egzemplarzy.at(j).GetElement(kryterium);
}
void OdczytZapisVectora::zamiana(int j) 
{
	Auto temp = vector_egzemplarzy.at(j);
	vector_egzemplarzy.at(j)=vector_egzemplarzy.at(j+1);
	vector_egzemplarzy.at(j+1)=temp;
}

void OdczytZapisVectora::zapisz()
{
	Auto a;	
	vector_egzemplarzy.push_back(a);
	Interface Inter;
	Inter.zapisNaZadanie();
}

void OdczytZapisVectora::pobierz_spis()
{
	naglowek();	
	for(int i = 0; i!=vector_egzemplarzy.size(); i++)
			{
				rozpisz_auto(i);
			}	
	Interface inter;
	inter.list_menu();	
}

void OdczytZapisVectora::wyswietl_pojedynczo(int i)
{
	system("cls");
	if(vector_egzemplarzy.size()==0)
					{
						cout<<"usunieto caly spis"<<endl;
						Interface inter;
						inter.main_menu();
						return;
					}
	if(i>vector_egzemplarzy.size()-1)
	{
		wyswietl_pojedynczo(--i);
		return;
	}

	naglowek();
	rozpisz_auto(i);
	Interface inter;
	inter.one_menu(i);
}
void OdczytZapisVectora::wyszukaj()
{
	int kryterium = mini_menu();
	if(kryterium==6||kryterium==7||kryterium==4)
	{
		int wartosc;
		cout<<"podaj wyszukiwana wartosc ";
		cin>>wartosc;
		naglowek();
		for(int i = 0; i<vector_egzemplarzy.size();i++)
		{
			warunek_wyszukania_int(i, kryterium, wartosc);
		}
	}
	if(kryterium>=1&&kryterium<=3||kryterium==5)
	{
		string wartosc;
		cout<<"podaj wyszukiwana wartosc ";
		cin>>wartosc;
		naglowek();
		for(int i = 0; i<vector_egzemplarzy.size();i++)
		{
			warunek_wyszukania_stringa( i,kryterium,wartosc);
		}
	}
	Interface inter;
	inter.back_to_second_menu();	
}

void OdczytZapisVectora::sortuj()
{
	int kryterium = mini_menu();
	if(kryterium==6||kryterium==7||kryterium==4)
		{
			for(int i = 0; i<vector_egzemplarzy.size()-1;i++)
			{
				for(int j = 0; j<vector_egzemplarzy.size()-1;j++)
				{
					int wartosc = 0, wartosc2 = 0;					
					wartosc = atoi(wartosc_elementu(j, kryterium).c_str());
					wartosc2 = atoi(wartosc_elementu(j+1,kryterium).c_str());
					if(wartosc>wartosc2)
					{
						zamiana(j);
					}
				}
			}
			pobierz_spis();
		}
	if(kryterium>=1&&kryterium<=3||kryterium==5)
		{
			for(int i = 0; i<vector_egzemplarzy.size()-1;i++)
			{
				for(int j = 0; j<vector_egzemplarzy.size()-1;j++)
				{
					string wartosc = "a", wartosc2 = "a";
					wartosc = wartosc_elementu(j, kryterium);
					wartosc2 = wartosc_elementu(j+1, kryterium);
					if(wartosc>wartosc2)
					{
						zamiana(j);
					}
				}
			}
			pobierz_spis();
			Interface Inter;
			Inter.zapisNaZadanie();
		}
		
}
//////////////////////////////////////////////////	

Interface::Interface()
{
	pierwszy_ekran = "1.Otworz baze z pliku\n2.Stworz nowa baze\n3.Zakoncz\n";
	drugi_ekran = "1.Dodaj auto\n2.pokaz liste\n3.pokaz pojedynczo\n4.zakoncz\n";
	trzeci_ekran = "1.Sortuj\n2.Wyszukaj\n3.Wroc\n4.zakoncz\n";
	czwarty_ekran = "W.pokaz wyzej\nS.pokaz nizej\nX.usun element\nZ.zakoncz\n";
	zacheta = "Podaj wybor: ";
}

void Interface::main_menu()
{
	system("cls");
	cout<<pierwszy_ekran;
	int odp;
	do{
		cout<<zacheta;
		cin>>odp;
	}while(odp<1 || odp>3);
	OdczytZapisPliku OZP;
	switch(odp)
	{
		case 1:
			OZP.pobierz();
			break;
		case 2: 
			OZP.stworz_nowa();
			break;
		case 3:
			zamkniecie();
			break;
			
	}
}

void Interface::second_menu()
{
	system("cls");
	cout<<drugi_ekran;
	int odp;
	do{
		cout<<zacheta;
		cin>>odp;
	}while(odp<1 || odp>4);
	OdczytZapisVectora OZV;
	switch(odp)
	{
		case 1:
			OZV.zapisz();
			second_menu();
			break;
		case 2:
			OZV.pobierz_spis();
			break;
		case 3:
			OZV.wyswietl_pojedynczo(0);
			break;
		case 4:
			zamkniecie();
	}
}

void Interface::back_to_second_menu()
{
	cout<<"Wpisz cokolwiek aby wrocic "<<endl;
	getchar();
	getchar();
	second_menu();
}

void Interface::list_menu()
{
	cout<<trzeci_ekran;
	int odp;
	do{
		cout<<zacheta;
		cin>>odp;
	}while(odp<1 || odp>4);
	OdczytZapisVectora OZV;
	switch(odp)
	{
		case 1:
			OZV.sortuj();
			break;
		case 2: 
			OZV.wyszukaj();
			break;
		case 3:
			second_menu();
			break;	
		case 4:
			zamkniecie();
	}
}

void Interface::one_menu(int i)
{
	cout<<czwarty_ekran;
	char klawisz;
	cin>>klawisz;
	OdczytZapisVectora OZV;
	switch(klawisz)
	{
			case 'w':
			case 'W':
				if(i>0)
				{
					OZV.wyswietl_pojedynczo(--i);
				}
				OZV.wyswietl_pojedynczo(i);
				break;
			case 's':
			case 'S':
				if(i<vector_egzemplarzy.size()-1)
				{
					OZV.wyswietl_pojedynczo(++i);
				}
				OZV.wyswietl_pojedynczo(i);
				break;
			case 'x':
			case 'X':					
					vector_egzemplarzy.erase(vector_egzemplarzy.begin()+i);//usuwanie elementu vektora na i-tym miesjcu
					cout<<"Usunieto ";
					zapisNaZadanie();
					OZV.wyswietl_pojedynczo(i);
				break;
			case 'z':
			case 'Z':
				zamkniecie();
			    break;
			default:
				one_menu(i);
	}
}
void Interface::zapisNaZadanie()
{
	system("cls");
	char odp;
	cout<<"\nCzy chcesz zapisac zmiany?[t/n]"<<endl;
	do
	{
		cin>>odp;
	}while(odp!='n'&&odp!='N'&&odp!='t'&&odp!='T');
	if(odp=='n'||odp=='N')
	{
		return;
	}else{
		OdczytZapisPliku OZP;
		OZP.zapisz();
	}
	
}				
//////////////////////////////////////////////////
void zamkniecie()
{
	char odpowiedz;
	do
	{
		cout<<"czy chcesz zapisac zmiany? [T/N]"<<endl;
		cin>>odpowiedz;
		
	}while(odpowiedz!='n'&&odpowiedz!='N'&&odpowiedz!='t'&&odpowiedz!='T');
	if(odpowiedz=='t'||odpowiedz=='T')
	{
		OdczytZapisPliku OZP;
		OZP.zapisz();
	}
	exit(0);
}
///////////////////////////////////////////////

int main(int argc, char** argv) {
	Interface inter;
	inter.main_menu();
}

