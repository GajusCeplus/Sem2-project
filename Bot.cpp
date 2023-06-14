#include "Gra.h"

Bot::Bot() {};
Bot::Bot(int a):poziom(a) {}
//pierwsze 5 tur
void Bot::bot(Gra& obiekt) {
	int akcja;
	srand(time(NULL));
	akcja = (rand() % 3 + 1);
	switch (akcja)
	{
	case 1: /*umieszczenie*/
		botumieszczenie(obiekt.linia, obiekt.symbole, obiekt.widzialne);
		break;
	case 2: /*zamiana*/
		botzamiana(obiekt.linia, obiekt.widzialne);
		break;
	case 3: /*ukrycie*/
		botukrycie(obiekt.widzialne);
		break;
	}

}
/*po 5 turach*/
void Bot::bot1(Gra& obiekt) {
	int akcja;
	srand(time(NULL));
	akcja = (rand() % 4 + 1);
	switch (akcja)
	{
	case 1: /*zamiana*/
		botzamiana(obiekt.linia, obiekt.widzialne);
		break;
	case 2: /*ukrycie*/
		botukrycie(obiekt.widzialne);
		break;
	case 3: /*wyzwanie*/
		botwyzwanie(obiekt);
		break;
	case 4: /*Przechwalka*/
		botAll_in(obiekt);
		break;
	}
}
//akcje bota
void Bot::botukrycie(char tab3[]) {
	int a = (rand() % 7);
	tab3[a] = '#';
	cout << "Ukrylem znak pod numerem " << a << endl;
	Sleep(2000);
}
void Bot::botumieszczenie(char tab1[], char tab2[], char tab3[]) {
	char symbol{};
	int strona{}, a{};
	a = (rand() % 7);
	symbol = tab2[a];
	strona = (rand() % 2);
	if (strona == 0)
	{
		/*ta funkcja jest problematyczna, istnieje mozliwosc ze sie wysypie*/
		for (int j = 0; j < 7; j++)
		{
			if ((tab1[j] != '*') && (j != 0) && (j !=6))
			{
				if (j - 1 <= 0)
					goto jakimcudemtegouzylem; //dobry jezu 
				tab1[j - 1] = symbol;
				tab3[j - 1] = symbol;
				cout << "Umiescilem symbol: " << symbol << " z lewej strony\n";
				Sleep(2000);
				break;
			}
			//else if (tab1[j + 1]); nie pamietam po co mi to bylo

		}
	}
	else if (strona == 1)
	{
		jakimcudemtegouzylem: //a nasz panie
		for (int j = 0; j < 7; j++)
		{
			if (tab1[6 - j] != '*')
			{
				if (6 - j > 6)
				{
					break;
				}
				else if (6 - j == 6)
				{
					tab1[6 - j] = symbol;
					tab3[6 - j] = symbol;
				}
				tab1[6 - j + 1] = symbol;
				tab3[6 - j + 1] = symbol;
				cout << "Umiescilem symbol: " << symbol << " z prawej strony\n";
				Sleep(2000);
				break;
			}
		}
	}
}
void Bot::botzamiana(char tab1[], char tab3[]) {
	int a{}, b{}, c{}, d{};
	a = (rand() % 7);
	b = (rand() % 7);
	if ((a == b) && (a != 0) && (a != 6))
		b++;
	else if ((a == b) && (a == 6))
		b--;
	else if ((a == b) && (a == 0))
		b++;
	/*zamiana na niewidzialnej*/
	c = tab1[a];
	tab1[a] = tab1[b];
	tab1[b] = c;
	/*zamiana na widzialnej tablicy*/
	d = tab3[a];
	tab3[a] = tab3[b];
	tab3[b] = d;
	cout << "zamieni³em miejsca " << c << " i " << d << endl;
}
void Bot::botwyzwanie(Gra& obiekt) {
	int numer{};
	char odpowiedz{};
	srand(time(NULL));
	numer = rand() % 7;
	cout << endl << "Jaki symbol w linii jest pod numerem " << numer << "?(podaj znak): ";
	cin >> odpowiedz;
	if (odpowiedz == obiekt.linia[numer])
	{
		cout << "Dobrze! Zdobywasz punkt\n\a";
		obiekt.punktygracz++;
		Sleep(2000);
	}
	else
	{
		cout << "Zle! Twoj przeciwnik zdobywa punkt\n";
		obiekt.punktybot++;
		Sleep(2000);
	}
}
int Bot::botAll_in(Gra& obiekt) {
	int opcja{4}, opcjaalt{};
	char symbol{};
	srand(time(NULL));
	cout << "Twoj przeciwnik uwaza ze zna kolejnosc znakow. Co teraz robisz?\n";
	cout << "1 - Wierzysz mu (oddajesz mu punkt)\n 2 - Nie wierzysz mu (musi podac we wlasciwej kolejnosci znaki w linii)\n"
		<< "3 - Nie interesuje cie to, bo tez je znasz(kradniesz All in)\n (Wpisz numer od 1 do 3):";
	while (opcja > 3 || opcja < 1)
	{
		cin >> opcja;
	}
	switch (opcja)
	{
	case 1:
		cout << "Przeciwnik zdobywa punkt\n";
		Sleep(2000);
		return obiekt.punktybot++;
		break;
	case 2:
		cout << "Przeciwnik podaje znaki";
		for (int i = 0; i < 3; i++)
		{
			Sleep(300);
			cout << ".";
		}
		cout << "\a";
		if ((rand() % 4) >= obiekt.trudnosc)
		{
			cout << endl << "Twoj przeciwnik sie pomylil!\a\n";
			Sleep(2000);
			return obiekt.punktygracz = 3;
		}
		else
		{
			cout << endl << "Twoj przeciwnik faktycznie znal ulozenie linii!\a\n";
			Sleep(2000);
			return obiekt.punktybot = 3;
		}
		break;
	case 3:
		cout << "Nie interesuje cie to, bo tez znasz wszystkie symbole w linii\n";
		if ((rand() % 4) >= obiekt.trudnosc)
		{
			cout << "Przeciwnik ci wierzy\n";
			cout << "Zdobywasz punkt!\n";
			Sleep(2000);
			return obiekt.punktygracz++;
		}
		else
		{
			cout << "Przeciwnik ci nie wierzy, musisz wymienic wszystkie znaki od lewej do prawej:\n";
			for (int i = 0; i < 7; i++)
			{
				cout << "Symbol nr " << i << " w linii to: ";
				cin >> symbol;
				if (symbol == obiekt.linia[i])
				{
					cout << "dobrze!\n";
					if ((i == 6) && (symbol == obiekt.linia[i]))
					{
						cout << "Udalo ci sie!";
						Sleep(2000);
						return obiekt.punktygracz = 3;
					}
				}
				else if (symbol != obiekt.linia[i])
				{
					cout << "Zle! Przegrywasz.\n";
					Sleep(2000);
					return obiekt.punktybot = 3;
				}
			}
			break;
		}
	default:
		return 0;
		break;
	}
}