#include "Gra.h"
using namespace std;
Gra::Gra() {}
Gra::~Gra() {}
//punkty
bool Gra::Gameover()
{
	if (punktygracz == 3)
		return 1;
	else if (punktybot == 3)
		return 1;
	else
		return 0;
}
//wypisanie planszy
void Gra::gra(char tab1[], char tab2[]) {
	cout << "Linia:\n\n";
	for (int i = 0; i < 7; i++)
	{
		cout << " " << tab1[i];
	}
	cout << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << " " << i;
	}
	cout << endl << endl;
	cout << "Dostepne symbole:\n\n";
	for (int i = 0; i < 7; i++)
	{
		cout << " " << tab2[i];
	}
	cout << endl;
	for (int i = 0; i < 7; i++)
	{
		cout << " " << i;
	}
}
//akcje
void Gra::umieszczenie(char tab1[], char tab2[], char tab3[])
{/*jesli zamienie gwiazdke z litera, umieszczenie moze nie dzialac poprawnie*/
/*ukryte gwiazdki zostana usuniete na rzecz umieszczonych w ich miejscu znakow*/
	char symbol{};
	bool strona{};
	cout << "Ktory symbol umiescic?(wpisz litere!):";
	cin >> symbol; /*jesli zly symbol to funkcja nic nie zrobi*/
	for (int i = 0; i < 7; i++)
	{
		if (symbol == tab2[i])
		{
			cout << "z ktorej strony?\n lewo - 0 \n prawo - 1 \n Strona:";
			cin >> strona; /*tu moze sie wysypac*/
			if (strona == 0)
			{
				for (int j = 0; j < 7; j++)
				{
					if (tab1[j] != '*')
					{/*gracz moze wyjechac poza tablice*/
						tab1[j - 1] = symbol;
						tab3[j - 1] = symbol;
						break;
					}
				}
			}
			else if (strona == 1)
			{
				for (int j = 0; j < 7; j++)
				{
					if (tab1[6 - j] != '*')
					{
						tab1[6 - j + 1] = symbol;
						tab3[6 - j + 1] = symbol;
						break;
					}
				}
			}
		}
	}
}
void Gra::ukrycie(char tab3[])
{
	int numer{7};
	while (numer > 6 || numer < 0)
	{
		cout << "ktory pole ukryc?(podaj numer od 0 do 7):";
		cin >> numer;
	}
	tab3[numer] = '#';

}
void Gra::zamiana(char tab1[], char tab3[]) {
	int i{ 7 }, j{ 7 };
	char a{}, b{};
	cout << "ktore miejsca zamienic?\nmiejsce 1:";
	while (i > 6 || i<0)
	{
		cin >> i;
		if (i > 6 || i < 0)
		{
			cout << "wpisz numer od 0 do 6:";
		}
	}
	cout << "miejsce2: ";
	while ((j > 6 || j < 0) || j == i)
	{
		cin >> j;
		if (j > 6 || j < 0 || j==i)
		{
			cout << "wpisz numer od 0 do 6, inny od poprzedniego:";
		}
	}
	/*zamiana na niewidzialnej*/
	a = tab1[i];
	tab1[i] = tab1[j];
	tab1[j] = a;
	/*zamiana na widzialnej tablicy*/
	b = tab3[i];
	tab3[i] = tab3[j];
	tab3[j] = b;
}
void Gra::podejrzenie(char tab1[])
{
	system("cls");
	cout << "Patrz szybko!\n\n";
	cout << "Linia: \n";
	for (int i = 0; i < 7; i++)
	{
		cout << " " << tab1[i];
	}
	cout << endl;
	Sleep(3000);
	system("cls");
 /*podejrzenie symboli z linii przez 3 sekundy*/
}
void Gra::wyzwanie()
{
	int rezultat{}, numer{7};
	srand(time(NULL));
	cout << "Znak pod ktorym numerem chcesz aby odgadnal twoj przeciwnik?: ";
	while (numer > 6 || numer < 0)
	{
		cin >> numer;
		if (numer > 6 || numer < 0)
		{
			cout << "Podaj numer od 0 do 6:";
		}
	}
	rezultat = (rand() % 4) <trudnosc;
	if (rezultat > 2)
	{
		cout << "Twoj przeciwnik prawidlowo odgadnal symbol, wiec zyskuje punkt!";
		punktybot++;
		Sleep(2000);
		
	}
	else
	{
		cout << "Twoj przeciwnik sie pomylil, dostajesz punkt!\a";
		punktygracz++;
		Sleep(2000);
	}
}
int Gra::All_in()
{
	int opcja{}, opcjaalt{}, x{};
	char symbol{};
	srand(time(NULL));
	x = rand() % 4;
	if (x > trudnosc)
		opcja = 0;
	else if (x < trudnosc)
		opcja = 1;
	else
		opcja = 2;
	switch (opcja)
	{
	case 0:
		cout << "Przeciwnik wierzy ci, ze znasz kolejnosc symboli w linii!\n Dostajesz punkt!\n\a";
		Sleep(2000);
		return punktygracz++;
		break;
	case 1:
		cout << "Przeciwnik ci nie wierzy, musisz wymienic wszystkie znaki od lewej do prawej:\n";
		for (int i = 0; i < 7; i++)
		{
			cout << "Symbol nr " << i << " w linii to: ";
			cin >> symbol;
			if (symbol == linia[i])
			{
				cout << "dobrze!\n";
				if ((i == 6) && (symbol == linia[i]))
				{
					cout << "Udalo ci sie!";
					Sleep(2000);
					return punktygracz = 3;
				}
			}
			else if (symbol != linia[i])
			{
				cout << "Zle! Przegrywasz.\n";
				Sleep(2000);
				return punktybot = 3;
			}
		}
		break;
	case 2:
		cout << "Twoj przeciwnik uwaza ze tez zna kolejnosc znakow. Co teraz robisz?\n";
		cout << "1 - Wierzysz mu (oddajesz mu punkt)\n 2 - Nie wierzysz mu (musi podac we wlasciwej kolejnosci znaki w linii)\n Wybierz numer:  ";
		cin >> opcjaalt;
		switch (opcjaalt)
		{
		case 1:
			cout << "Oddajesz punkt przeciwnikowi\n";
			Sleep(2000);
			return punktybot++;
			break;
		default: //w wypadku gdy dla "opcjaalt" zostanie wprowadzone cos innego niz 1 to uznaje ze chodzilo o 2
			cout << "Przeciwnik sprawdza";
			for (int i = 0; i < 3; i++)
			{
				Sleep(300);
				cout << ".";
			}
			if ((rand() % 4) >= trudnosc)
			{
				cout << "\nTwoj przeciwnik sie pomylil!\a\n";
				Sleep(2000);
				return punktygracz = 3;
			}
			else
			{
				cout << "\nTwoj przeciwnik faktycznie znal ulozenie linii!\a\n";
				Sleep(2000);
				return punktybot = 3;
			}
			break;
		}
	default:
		return 0;
		break;
	}
}
void Tellstones(Gra& obiekt, Bot& przeciwnik)
{
	while (true)
	{
		int menu{};

		obiekt.menuStart();
		cin >> menu;
		switch (menu)
		{
		case 1:
			Trudnosc(obiekt, przeciwnik);
			obiekt.StartGame(obiekt, przeciwnik);
			break;
		case 2:
			obiekt.instrukcja();
			_getch();
			break;
		case 3:
			system("cls");
			cout << "Do zobaczenia :)" << endl;
			exit(0);
			break;
		}
	}
}
//wyswietlenie menu startowego
void Gra::menuStart() {
	system("cls");
	cout << "         Tellstones         " << endl;
	cout << "!Wszystkie akcje konczysz klikajac ENTER!" << endl;
	cout << "     1 - Rozpocznij gre     " << endl;
	cout << "     2 - Instrukcja         " << endl;
	cout << "     3 - Wyjdz z gry        " << endl;
	cout << "  Wybierz numer:            " << endl;
}
//ustalenie poziomu trudnosci
int Trudnosc(Gra& obiekt, Bot& przeciwnik)
{
	int a = 11;
	while (a != 3 || a != 2 || a != 1)
	{
		cout << "wybierz poziom trudnosci\n"
			<< "latwy -- 1\n"
			<< "sredni -- 2\n"
			<< "trudny -- 3\n"
			<< "Podaj liczbe:";
		cin >> a;
		if (a == 1)
		{
			obiekt.trudnosc = a;
			break;
		}
		else if (a == 2)
		{
			obiekt.trudnosc = a;
			break;
		}
		else if (a == 3)
		{
			obiekt.trudnosc = a;
			break;
		}
		else
		{
			cout << "wybierz wartosc od 1 do 3!\n";
		}
	}
	return przeciwnik.poziom = obiekt.trudnosc;
}
//wlasciwa gra
void Gra::StartGame(Gra& obiekt, Bot& przeciwnik)
{
	int nrakcji{};
	/*pierwsze 5 tur*/
	while (((obiekt.punktygracz != 3) || (obiekt.punktybot != 3)) && (obiekt.tura <= 5))
	{
		system("cls");
		obiekt.gra(obiekt.widzialne, obiekt.symbole);
		cout << endl;
		akcjelista();
		cout << "Tura nr: " << obiekt.tura << endl;
		cout << "Twoje punkty: " << obiekt.punktygracz << endl;
		cout << "Punkty przeciwnika: " << obiekt.punktybot << endl;
		cout << endl << "Wybierz numer akcji: ";
		cin >> nrakcji;
		switch (nrakcji)
		{
		case 1:
			obiekt.umieszczenie(obiekt.linia, obiekt.symbole, obiekt.widzialne);
			break;
		case 2:
			obiekt.zamiana(obiekt.linia, obiekt.widzialne);
			break;
		case 3:
			obiekt.ukrycie(obiekt.widzialne);
			break;
		case 4:
			obiekt.podejrzenie(obiekt.linia);
			break;
		default:
			break;
		}
		cout << endl;
		przeciwnik.bot(obiekt);
		cout << "Nacisnij przycisk aby kontynuowac";
		_getch();
		obiekt.tura++;
	}
	/*po 5 turach mozna zdobywac punkty*/
	while (((obiekt.punktygracz != 3) || (obiekt.punktybot != 3)) && (obiekt.tura > 5))
	{
		if (obiekt.Gameover() == 1)
			break;
		system("cls");
		obiekt.gra(obiekt.widzialne, obiekt.symbole);
		cout << endl;
		akcjelista1();
		cout << "Tura nr: " << tura << endl;
		cout << "Twoje punkty: " << obiekt.punktygracz << endl;
		cout << "Punkty przeciwnika: " << obiekt.punktybot << endl;
		cout << endl << "Wybierz numer akcji: ";
		cin >> nrakcji;
		switch (nrakcji)
		{
		case 1:
			obiekt.zamiana(obiekt.linia, obiekt.widzialne);
			przeciwnik.bot1(obiekt);
			break;
		case 2:
			obiekt.ukrycie(obiekt.widzialne);
			przeciwnik.bot1(obiekt);
			break;
		case 3:
			obiekt.podejrzenie(obiekt.linia);
			przeciwnik.bot1(obiekt);
			break;
		case 4:
			obiekt.wyzwanie();
			break;
		case 5:
			obiekt.All_in();
			break;
		default:
			break;
		}
		cout << "Nacisnij przycisk aby kontynuowac";
		_getch();
		obiekt.tura++;
	}
	/*zakonczenie gry*/
	if (obiekt.punktygracz == 3)
	{
		system("cls");
		cout << "Gratulacje wygrales w Tellstones!\a" << endl;
		cout << "Kliknij dowolny przycisk aby kontynuowac" << endl;
		_getch();
	}
	else if (obiekt.punktybot == 3)
	{
		system("cls");
		cout << "Przegrales, powodzenia nastepnym razem!\a" << endl;
		cout << "Kliknij dowolny przycisk aby kontynuowac" << endl;
		_getch();
	}
	else
	{
		system("cls");
		cout << "jak..." << endl;
		Sleep(200);
		cout << "znaczy sie, Hurra!\n" << "Odkryles sekretne zakonczenie!\n";
		exit(0);
	}
}
void Gra::instrukcja() {
	system("cls");
	cout << "            Witaj w Tellstones - King's Gambit!        " << endl << endl;
	cout << "Jest to gra pamieciowa, w ktorej zwycieza osoba posiadajaca 3 punkty.\n Ty oraz przeciwnik zaczynacie z 1 punktem.\n Zdobywasz punkt poprzez prawidlowe odgadniecie symboli.\n "
		<< " Jesli odpowiesz zle, twoj przeciwnik zyskuje punkt.\n W grze jest 7 roznych symboli zawsze widocznych dla ciebie\n Symbole mozna ustawiac na linii, gra rozpoczyna sie juz z jednym sybolem w grze\n "
		<< " Do dyspozycji masz 4 ruchy:\n\n 1: umieszczenie\n mozesz umiescic symbol z lewej lub prawej strony linii\n\n 2: ukrycie\n mozesz zakryc dowolne pole\n\n 3: zamiana\n zamieniasz miejscami dwa pola planszy\n\n"
		<< " 4: podejrzenie\n mozesz zobaczyc wszystkie symbole w linii przez 3 sekundy\n" << endl;
	cout << "(ukryte gwiazdki zostana usuniete na rzecz umieszczonych w ich miejscu znakow)\n";
	cout << "Po 5 turach gracze zyskuja 2 dodatkowe akcje:\n\n 1 - Wyzwanie\n Twoj przeciwnik musi odgadnac symbol we wskazanym miejscu\n\n 2 - All in (przechwalanie sie)\n"
		<< "Mowisz przeciwnikowi ze znasz ulozenie wszystkich symboli w linii, twoj przeciwnik moze wtedy:\n Uwierzyc ci, dostajesz wtedy punkt\n Nie uwierzyc ci, wtedy musisz sprawdzic cala linie. Jesli prawidlowo odczytasz wszystkie symbole, wygrywasz!\n Jednak jesli sie pomylisz choc raz to przegrywasz.\n";
	cout << "Moze tez powiedziec, ze tez zna ulozenie calej linii. Wtedy kradnie ci All in pozostawiajac ci poprzednie dwie opcje\n";
	cout << "\nNa poczatku gry zobaczysz dwie linie:\n\n";
	Gra::gra(linia, symbole);
	cout << "\n\nGorna linia przedstawia plansze do gry, numery pod nia pokazuja numer elementu w linii\n" <<
		"Dolna linia przedstawia symbole dostepne w grze, numery pod nia pokazuja numer elementu w linii\n\n";
	cout << "Pod tymi liniami zobaczysz liste dostepnych zmieniajacych sie wraz z uplywem czasu, liczbe punktow obu graczy oraz numer tury" << endl;
	cout <<endl<< "Mozna grac na 3 poziomach trudnosci, im nizszy poziom tym wieksze szanse na to, ze twoj przeciwnik bedzie gral pasywnie\n\n";
	cout << "Pamietaj, ze przejezyczenie moze byc bardzo niebezpieczne. Na cale szczescie w tej grze bedzie cie to kosztowac co najwyzej stracony ruch, a nie 25 lat zycia\n\n";
	cout << "\n\n Kliknij dowolny przycisk aby kontynuowac";

}
/*pierwsze 5 tur*/
void Gra::akcjelista()
{
	cout << "\nMozliwe akcje:\n " << "1 - umieszczenie\n 2 - zamiana\n 3 - ukrycie\n 4 - podejrzenie\n";
}
/*po 5 turach*/
void Gra::akcjelista1()
{
	cout << "\nMozliwe akcje:\n " << "1 - zamiana\n 2 - ukrycie\n 3 - podejrzenie\n 4 - wyzwanie\n 5 - All in\n";
}