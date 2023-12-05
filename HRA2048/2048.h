#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <conio.h>

#define KB_UP 72 
#define KB_DOWN 80 
#define KB_LEFT 75 
#define KB_RIGHT 77 
#define KB_ESCAPE 27 
#define MAX_HRACU 10
#define MAX_JMENO_DELKA 20

typedef struct {
    char jmeno[MAX_JMENO_DELKA];
    int skore;
} Statistiky;

void novaHra(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]);
void nactiHru(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]);
void ulozHru(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]);
void zobrazStatistiky();
bool jmenoExistuje(char jmeno[MAX_JMENO_DELKA]);
void nactiHruZeSouboru(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]);
int provedPohyb(int tabulka[4][4], int smer, Statistiky* s);
bool hraSkoncila(int tabulka[4][4]);
void ulozStatistiku(Statistiky statistika);
void ulozStavHry(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]);
int navigation(void);
void inicializujTabulku(int tabulka[4][4]);
void pridejNahodneCislo(int tabulka[4][4]);
void provedPohybVlevo(int tabulka[4][4], int* skore);
void provedPohybVpravo(int tabulka[4][4], int* skore);
void provedPohybNahoru(int tabulka[4][4], int* skore);
void provedPohybDolu(int tabulka[4][4], int* skore);
void vypis(int tabulka[4][4], Statistiky s);
int provedPohyb(int tabulka[4][4], int smer, Statistiky* s);
bool hraSkoncila(int tabulka[4][4]);
void hrajHru(int tabulka[4][4], Statistiky stats);