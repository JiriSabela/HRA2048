#include "2048.h"


int main() {
    int tabulka[4][4], volba;
    Statistiky s;
    s.skore = 0;
    // Inicializace generátoru náhodných čísel
    srand(time(NULL));

    do {
        printf("1. Nova hra\n");
        printf("2. Pokracovat ve hre\n");
        printf("3. Zobrazit statistiky\n");
        printf("4. Konec\n");
        printf("Vyberte moznost: ");
        scanf("%d", &volba);

        switch (volba) {
        case 1:
            novaHra(tabulka, s.jmeno);
            hrajHru(tabulka, s);
            ulozStatistiku(s);
            break;
        case 2:
            nactiHru(tabulka, s.jmeno);
            hrajHru(tabulka, s);
            ulozStatistiku(s);
            break;
        case 3:
            zobrazStatistiky();
            break;
        case 4:
            printf("Konec programu.\n");
            return 0;
            break;
        default:
            printf("Neplatna volba. Zkuste to znovu.\n");
        }
    } while (volba != 4);
}
