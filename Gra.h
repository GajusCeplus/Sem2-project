#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <conio.h>
using namespace std;
class Bot;
class Gra
{
public:
	char linia[7] = { '*','*','*','x','*','*','*' };
	char symbole[7] = { 'z','x','c','v','b','n','m' };
	char widzialne[7] = { '*','*','*','x','*','*','*' };
	int punktygracz = 1;
	int punktybot = 1;
	int tura = 1;
	int trudnosc = 1;
	Gra();
	virtual ~Gra();
	void gra(char[], char[]);
	void umieszczenie(char[], char[], char[]);
	void ukrycie(char[]);
	void zamiana(char[], char[]);
	void podejrzenie(char[]);
	void wyzwanie();
	int All_in();
	bool Gameover();
	friend void Tellstones(Gra&, Bot&);
	friend int Trudnosc(Gra&, Bot&);
	void menuStart();
	void StartGame(Gra&, Bot&);
	void instrukcja();
	/*pierwsze 5 tur*/
	void akcjelista();
	/*po 5 turach*/
	void akcjelista1();
};

class Bot :public Gra
{
public:
	int poziom = 1;
	Bot();
	Bot(int poziom);
	virtual ~Bot() {};
	void bot(Gra&);
	void bot1(Gra&);
	void botukrycie(char[]);
	void botumieszczenie(char[], char[], char[]);
	void botzamiana(char[], char[]);
	void botwyzwanie(Gra&);
	int botAll_in(Gra&);
};