#include "2048.h"

void ulozStatistiku(Statistiky statistika) {
    FILE* soubor;
    Statistiky statistiky[MAX_HRACU];
    int pocetHracu = 0;

    // Naètení aktuálních statistik ze souboru
    soubor = fopen("statistiky.txt", "r");

    if (soubor != NULL) {
        while (fscanf(soubor, "%s %d", statistiky[pocetHracu].jmeno, &statistiky[pocetHracu].skore) == 2 && pocetHracu < MAX_HRACU) {
            ++pocetHracu;
        }

        fclose(soubor);
    }
    else {
        printf("Chyba pri nacitani statistik ze souboru.\n");
        return;
    }

    // Pøidání aktuální statistiky do pole
    statistiky[pocetHracu] = statistika;
    ++pocetHracu;

    // Seøazení statistik podle skóre (bublinkové øazení)
    for (int i = 0; i < pocetHracu - 1; ++i) {
        for (int j = 0; j < pocetHracu - i - 1; ++j) {
            if (statistiky[j].skore < statistiky[j + 1].skore) {
                Statistiky temp = statistiky[j];
                statistiky[j] = statistiky[j + 1];
                statistiky[j + 1] = temp;
            }
        }
    }

    // Uložení aktualizovaných statistik zpìt do souboru
    soubor = fopen("statistiky.txt", "w");

    if (soubor != NULL) {
        for (int i = 0; i < pocetHracu && i < MAX_HRACU; ++i) {
            fprintf(soubor, "%s %d\n", statistiky[i].jmeno, statistiky[i].skore);
        }

        fclose(soubor);
    }
    else {
        printf("Chyba pri ukladani statistiky.\n");
    }
}




void ulozStavHry(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]) {
    FILE* soubor;
    soubor = fopen(jmeno, "w");

    if (soubor != NULL) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                fprintf(soubor, "%d ", tabulka[i][j]);
            }
            fprintf(soubor, "\n");
        }
        fclose(soubor);
    }
    else {
        printf("Chyba pri ukladani hry.\n");
    }
}

int navigation(void)
{
    int KB_code = 0;

    while (KB_code != KB_ESCAPE)
    {
        if (kbhit())
        {
            KB_code = getch();
            printf("\n");
            //printf("KB_code = %i \n", KB_code);

            switch (KB_code)
            {
            case KB_LEFT:
                return 1;
                break;

            case KB_RIGHT:
                return 2;
                break;

            case KB_UP:
                return 3;
                break;

            case KB_DOWN:
                return 4;
                break;

            }

        }
    }
}

// Funkce pro inicializaci tabulky nulami
void inicializujTabulku(int tabulka[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            tabulka[i][j] = 0;
        }
    }
}

// Funkce pro pøidání hodnoty 2 nebo 4 na náhodné místo do tabulky
void pridejNahodneCislo(int tabulka[4][4]) {
    // Najdi dostupná místa s nulami
    int dostupnaMista[16][2];
    int pocet = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tabulka[i][j] == 0) {
                dostupnaMista[pocet][0] = i;
                dostupnaMista[pocet][1] = j;
                pocet++;
            }
        }
    }

    // Zkontroluj, zda jsou dostupná místa
    if (pocet > 0) {
        // Vyber náhodné místo z dostupných
        int nahodnyIndex = rand() % pocet;
        int nahodnaHodnota = (rand() % 2 + 1) * 2;  // Buï 2 nebo 4
        tabulka[dostupnaMista[nahodnyIndex][0]][dostupnaMista[nahodnyIndex][1]] = nahodnaHodnota;
    }
}

void provedPohybVlevo(int tabulka[4][4], int* skore) {
    for (int radek = 0; radek < 4; ++radek) {
        int index = 0;  // Index pro sledování pozice èísla v øádku

        // Pøesuò èísla vlevo
        for (int sloupec = 0; sloupec < 4; ++sloupec) {
            if (tabulka[radek][sloupec] != 0) {
                // Hledej místo pro pøesunutí èísla
                int cilovySloupec = index;

                while (cilovySloupec > 0 && tabulka[radek][cilovySloupec - 1] == 0) {
                    --cilovySloupec;
                }

                // Pokud je èíslo stejné jako èíslo na cílovém místì, seèti je
                if (cilovySloupec > 0 && tabulka[radek][cilovySloupec - 1] == tabulka[radek][sloupec]) {
                    *skore = *skore + (2 * tabulka[radek][cilovySloupec - 1]);
                    tabulka[radek][cilovySloupec - 1] *= 2;
                    tabulka[radek][sloupec] = 0;
                }
                else {
                    // Pøesuò èíslo na cílové místo
                    tabulka[radek][cilovySloupec] = tabulka[radek][sloupec];
                    if (cilovySloupec != sloupec) {
                        tabulka[radek][sloupec] = 0;
                    }
                    ++index;
                }
            }
        }
    }
}

void provedPohybVpravo(int tabulka[4][4], int* skore) {
    for (int radek = 0; radek < 4; ++radek) {
        int index = 3;  // Index pro sledování pozice èísla v øádku

        // Pøesuò èísla vpravo
        for (int sloupec = 3; sloupec >= 0; --sloupec) {
            if (tabulka[radek][sloupec] != 0) {
                // Hledej místo pro pøesunutí èísla
                int cilovySloupec = index;

                while (cilovySloupec < 3 && tabulka[radek][cilovySloupec + 1] == 0) {
                    ++cilovySloupec;
                }

                // Pokud je èíslo stejné jako èíslo na cílovém místì, seèti je
                if (cilovySloupec < 3 && tabulka[radek][cilovySloupec + 1] == tabulka[radek][sloupec]) {
                    *skore = *skore + (2 * tabulka[radek][cilovySloupec + 1]);
                    tabulka[radek][cilovySloupec + 1] *= 2;
                    tabulka[radek][sloupec] = 0;
                }
                else {
                    // Pøesuò èíslo na cílové místo
                    tabulka[radek][cilovySloupec] = tabulka[radek][sloupec];
                    if (cilovySloupec != sloupec) {
                        tabulka[radek][sloupec] = 0;
                    }
                    --index;
                }
            }
        }
    }
}

// Funkce pro pohyb èísel nahoru v tabulce
void provedPohybNahoru(int tabulka[4][4], int* skore) {
    for (int sloupec = 0; sloupec < 4; ++sloupec) {
        int indexNuly = 0;

        for (int radek = 0; radek < 4; ++radek) {
            if (tabulka[radek][sloupec] == 0) {
                // Pøesun nuly na konec sloupce
                int temp = tabulka[indexNuly][sloupec];
                tabulka[indexNuly][sloupec] = tabulka[radek][sloupec];
                tabulka[radek][sloupec] = temp;
                ++indexNuly;
            }
        }
    }
    for (int sloupec = 0; sloupec < 4; ++sloupec) {
        int index = 0;  // Index pro sledování pozice èísla ve sloupci

        // Pøesuò èísla nahoru
        for (int radek = 0; radek < 4; ++radek) {
            if (tabulka[radek][sloupec] != 0) {
                // Hledej místo pro pøesunutí èísla
                int cilovyRadek = index;

                while (cilovyRadek > 0 && tabulka[cilovyRadek - 1][sloupec] == 0) {
                    --cilovyRadek;
                }

                // Pokud je èíslo stejné jako èíslo na cílovém místì, seèti je
                if (cilovyRadek > 0 && tabulka[cilovyRadek - 1][sloupec] == tabulka[radek][sloupec]) {
                    *skore = *skore + (2 * tabulka[cilovyRadek - 1][sloupec]);
                    tabulka[cilovyRadek - 1][sloupec] *= 2;
                    tabulka[radek][sloupec] = 0;
                }
                else {
                    // Pøesuò èíslo na cílové místo
                    tabulka[cilovyRadek][sloupec] = tabulka[radek][sloupec];
                    if (cilovyRadek != radek) {
                        tabulka[radek][sloupec] = 0;
                    }
                    ++index;
                }
            }
        }
    }
}

// Funkce pro pohyb èísel dolù v tabulce
void provedPohybDolu(int tabulka[4][4], int* skore) {
    for (int sloupec = 0; sloupec < 4; ++sloupec) {
        int index = 3;  // Index pro sledování pozice èísla ve sloupci

        // Pøesuò èísla dolù
        for (int radek = 3; radek >= 0; --radek) {
            if (tabulka[radek][sloupec] != 0) {
                // Hledej místo pro pøesunutí èísla
                int cilovyRadek = index;

                while (cilovyRadek < 3 && tabulka[cilovyRadek + 1][sloupec] == 0) {
                    ++cilovyRadek;
                }

                // Pokud je èíslo stejné jako èíslo na cílovém místì, seèti je
                if (cilovyRadek < 3 && tabulka[cilovyRadek + 1][sloupec] == tabulka[radek][sloupec]) {
                    *skore = *skore + (2 * tabulka[cilovyRadek + 1][sloupec]);
                    tabulka[cilovyRadek + 1][sloupec] *= 2;
                    tabulka[radek][sloupec] = 0;
                }
                else {
                    // Pøesuò èíslo na cílové místo
                    tabulka[cilovyRadek][sloupec] = tabulka[radek][sloupec];
                    if (cilovyRadek != radek) {
                        tabulka[radek][sloupec] = 0;
                    }
                    --index;
                }
            }
        }
    }
}

void vypis(int tabulka[4][4], Statistiky s) {
    printf("\njmeno:%s skore :%d\n", s.jmeno, s.skore);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%d ", tabulka[i][j]);
        }
        printf("\n");
    }
}



int provedPohyb(int tabulka[4][4], int smer, Statistiky* s) {
    // Implementace pohybu podle smìru (1 pro vlevo, 2 pro vpravo, 3 pro nahoru, 4 pro dolu)
    switch (smer) {
    case 1:
        provedPohybVlevo(tabulka, &s->skore);
        break;
    case 2:
        provedPohybVpravo(tabulka, &s->skore);
        break;
    case 3:
        provedPohybNahoru(tabulka, &s->skore);
        break;
    case 4:
        provedPohybDolu(tabulka, &s->skore);
        break;
    default:
        printf("Neplatny smer. Zkuste to znovu.\n");
    }

    // Pøidání nového náhodného èísla po každém pohybu
    pridejNahodneCislo(tabulka);

    // Uložení stavu hry
    ulozStavHry(tabulka, s->jmeno);

    // Kontrola ukonèení hry
    if (hraSkoncila(tabulka)) {
        printf("Hra skoncila. Dosahli jste cisla 2048 nebo nemate zadny platny pohyb.\n");
        return 1;
    }
}

bool hraSkoncila(int tabulka[4][4]) {
    // Kontrola, zda uživatel dosáhl èísla 2048
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tabulka[i][j] == 2048) {
                return true;
            }
        }
    }

    // Kontrola, zda jsou všechna políèka obsazena a nelze provést žádný další pohyb
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (tabulka[i][j] == 0) {
                return false;  // Existuje alespoò jedno prázdné pole, hra mùže pokraèovat
            }
            // Kontrola sosedních políèek pro možnost dalšího pohybu
            if ((i < 3 && tabulka[i][j] == tabulka[i + 1][j]) || (j < 3 && tabulka[i][j] == tabulka[i][j + 1])) {
                return false;  // Existuje alespoò jedno sousední políèko se stejným èíslem, hra mùže pokraèovat
            }
        }
    }

    return true;  // Žádné prázdné pole a žádný platný pohyb, hra skonèila
}

void hrajHru(int tabulka[4][4], Statistiky stats) {
    while (1) {
        vypis(tabulka, stats);
        if (provedPohyb(tabulka, navigation(), &stats) == 1) {
            return;
        }
    }
}


void novaHra(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]) {
    inicializujTabulku(tabulka);
    printf("Zadejte sve jmeno: ");
    scanf("%s", jmeno);
    pridejNahodneCislo(tabulka);
    pridejNahodneCislo(tabulka);
    ulozHru(tabulka, jmeno);
}

void nactiHru(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]) {
    printf("Zadejte sve jmeno: ");
    scanf("%s", jmeno);
    if (jmenoExistuje(jmeno)) {
        printf("Nacitam hru pro hrace %s...\n", jmeno);
        // Naètìte hru ze souboru
        nactiHruZeSouboru(tabulka, jmeno);
    }
    else {
        printf("Hrac s jmenem %s neexistuje.\n", jmeno);
    }
}


void ulozHru(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]) {
    FILE* soubor;
    soubor = fopen(jmeno, "w");

    if (soubor != NULL) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                fprintf(soubor, "%d ", tabulka[i][j]);
            }
            fprintf(soubor, "\n");
        }
        fclose(soubor);
    }
    else {
        printf("Chyba pri ukladani hry.\n");
    }
}

bool jmenoExistuje(char jmeno[MAX_JMENO_DELKA]) {
    FILE* soubor;
    soubor = fopen(jmeno, "r");

    if (soubor != NULL) {
        fclose(soubor);
        return true;
    }
    else {
        return false;
    }
}
void nactiHruZeSouboru(int tabulka[4][4], char jmeno[MAX_JMENO_DELKA]) {
    FILE* soubor;
    soubor = fopen(jmeno, "r");

    if (soubor != NULL) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                fscanf(soubor, "%d", &tabulka[i][j]);
            }
        }
        fclose(soubor);
        printf("Hra nactena ze souboru.\n");
    }
    else {
        printf("Chyba pri nacitani hry ze souboru.\n");
    }
}

void zobrazStatistiky() {
    Statistiky statistiky[MAX_HRACU];
    FILE* soubor;
    int pocetHracu = 0;

    // Naètení statistik ze souboru
    soubor = fopen("statistiky.txt", "r");

    if (soubor != NULL) {
        while (fscanf(soubor, "%s %d", statistiky[pocetHracu].jmeno, &statistiky[pocetHracu].skore) == 2 && pocetHracu < MAX_HRACU) {
            ++pocetHracu;
        }

        fclose(soubor);
    }
    else {
        printf("Chyba pri nacitani statistik ze souboru.\n");
        return;
    }

    // Seøazení statistik podle skóre (bublinkové øazení)
    for (int i = 0; i < pocetHracu - 1; ++i) {
        for (int j = 0; j < pocetHracu - i - 1; ++j) {
            if (statistiky[j].skore < statistiky[j + 1].skore) {
                Statistiky temp = statistiky[j];
                statistiky[j] = statistiky[j + 1];
                statistiky[j + 1] = temp;
            }
        }
    }

    // Vypisovani nejvyssich statistik
    printf("Nejvyssi statistiky:\n");
    for (int i = 0; i < pocetHracu && i < MAX_HRACU; ++i) {
        printf("%d. %s - %d\n", i + 1, statistiky[i].jmeno, statistiky[i].skore);
    }
}
