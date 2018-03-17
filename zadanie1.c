/*PIOTR SZUBERSKI, ZADANIE NR 1, POZIOMKA, 28.XI.2016

    KONTAKT MAILOWY: p.szuberski@student.uw.edu.pl
    PROGRAM SYMULUJE GRE PRAWEGO GRACZA

    ABY GRAC W GRE NALEZY NARAZ PODAWAC WSPOLRZEDNE PLANSZY
    ZACZYNAJACE SIE OD DUZEJ, NASTEPNIE MALEJ LITERY,
    BEZ ZADNYCH INNYCH ZNAKOW
 
    ABY PRZERWAC GRE NALEZY WPISAC DWIE DOWOLNE CYFRY
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define DUZE_LITERY 65
#define MALE_LITERY 97
#define PIERWSZA 0
#define DRUGA 1
#define WYMIARY 2

#ifndef POLA
# define POLA 5
#endif

#ifndef WIERSZE
# define WIERSZE 26
#endif

#ifndef KOLUMNY
# define KOLUMNY 26
#endif

/* funkcja nr 1
nadaje całej planszy wartości zero
*/
void zerowanie_planszy(int PLANSZA[WIERSZE][KOLUMNY]) {
    int w, k;
    for (w = 0; w < WIERSZE; w++) {
        for (k = 0; k < KOLUMNY; k++) {
            PLANSZA[w][k] = 0;
        }
    }
}

/* funkcja nr 2
w - odpowiada za wiersze, k - za kolumny - petla idzie po
    wierszach, w pionie
ilosc_pol - oznacza zmienna okreslajaca, czy jest wystarczajaca
    wolnych pol do postawienia kreski
ruchy_lewy - oznacza ilosc kresek jakie jest w stanie postawic
    gracz lewy
*/
int lewy_liczba_ruchow(int PLANSZA[WIERSZE][KOLUMNY], int pola) {
    int w, k;
    int ilosc_pol, ruchy_lewy;

    ruchy_lewy = 0;
    for (k = 0; k < KOLUMNY; k++) {
        ilosc_pol = 0;
        for (w = 0; w < WIERSZE; w++) {
            if (PLANSZA[w][k] == 0)
                ilosc_pol++;
            else
                ilosc_pol = 0;

            if (ilosc_pol == pola) {
                ruchy_lewy++;
                ilosc_pol = 0;
            }
        }
    }
    return ruchy_lewy;
}

/* funkcja nr 3
w - wiersze, k - kolumny, ida po kolumnach, w poziomie
ilosc_pol - oznacza zmienna okreslajaca, czy jest wystarczajaca
    wolnych pol do postawienia kreski
ruchy_prawy - oznacza ilosc kresek jakie jest w stanie postawic
    gracz prawy
*/
int prawy_liczba_ruchow(int PLANSZA[WIERSZE][KOLUMNY], int pola) {
    int w, k;
    int ilosc_pol, ruchy_prawy = 0;

    for (w = 0; w < WIERSZE; w++) {
        ilosc_pol = 0;
        for (k = 0; k < KOLUMNY; k++) {
            if (PLANSZA[w][k] == 0)
                ilosc_pol++;
            else
                ilosc_pol = 0;

            if (ilosc_pol == pola) {
                ruchy_prawy++;
                ilosc_pol = 0;
            }
        }
    }
    return ruchy_prawy;
}


/* funkcja nr 4
ruch lewego gracza - wcisniecie najpierw litery duzej, pozniej malej
    jako wspolrzedne wywola ruch. Wcisniecie znaku o nizszej wartosci od
    liter konczy gre. Wciśnięcie enter - przekazuje ruch prawemu
    graczowi lub wciśnięty kolejny raz omija kolejkę (co byłoby 
    niepoprawnie wprowadzoną daną)

duza_litera - pierwsza wczytywana wspolrzedna z wejscia
lewa_litera - druga wczytywana wspolrzedna z wejscia
*/
int ruch_lewego(int PLANSZA[WIERSZE][KOLUMNY], int pola) {
    int mala_litera;
    int duza_litera;
    int i;

    duza_litera = getchar() - DUZE_LITERY;
    if ((char) (duza_litera + DUZE_LITERY) == '\n')
        return 1;
    mala_litera = getchar() - MALE_LITERY;
    getchar();
    if ((duza_litera < -1) || (mala_litera < -1))
        return 0;
    else {
        for (i = mala_litera; i < mala_litera + pola; i++) {
            PLANSZA[i][duza_litera] = 1;
        }
    }
    return 1;
}

/* funkcja nr 5
losuje, który z wybranych ruchów wybrać
*/
int losuj_calkowita(int n) {
    assert(n > 0);
    return (int) (rand() / (RAND_MAX + 1.0) * n);
}

/* funkcja nr 6
zeruje tablicę współrzędnych możliwych ruchów prawego gracza
*/
void zerowanie_ruchow(int WSPOLRZEDNE[WIERSZE * KOLUMNY][WYMIARY], int ruchy) {
    int i;

    for (i = 0; i < ruchy; i++) {
        WSPOLRZEDNE[i][PIERWSZA] = 0;
        WSPOLRZEDNE[i][DRUGA] = 0;
    }
}

/* funkcja nr 7
funkcja wypisująca ruchy prawego gracza na wyjście

mala_litera - pierwsza wspolrzedna do wyjscia
duza_litera - druga wspolrzedna do wyjscia
*/
void wypisz(int WSPOLRZEDNE[KOLUMNY * WIERSZE][WYMIARY], int wybrany_ruch) {
    int mala_litera, duza_litera;

    mala_litera = WSPOLRZEDNE[wybrany_ruch][PIERWSZA] + MALE_LITERY;
    duza_litera = WSPOLRZEDNE[wybrany_ruch][DRUGA] + DUZE_LITERY;
    printf("%c%c\n", mala_litera, duza_litera);
}

/* funkcja nr 8
1)sprawdza, czy ruch jest legalny - jeśli nie to k przesuwa się o 1 
    naprzód
2)jeśli jest legalny, to idzie dalej do momentu, w którym uzbierała
    sie odpowiednia ilość pól do postawienia kreski
3)robi symulację ruchu i sprawdza ocenę planszy po jego wykonaniu
4)kasuje ten ruch
5)sprawdza czy ten ruch byl lepszy od poprzednich
6)jeśli tak, to zeruje tablicę poprzednich ruchów i zapisuje
    współrzędne tego ruchu i cofa k o pola-2 pozycje do tyłu
7)jeśli taki jak poprzedni to dodaje tę współrzędną i cofa k o pola-2
    pozycje do tyłu
8)jeśli nie to tylko cofa k o pola-2 pozycje do tyłu
9)oddaje liczbę możliwych do wykonania ruchów
10)ocena_przed wynosi na poczatku minus wszystkie możliwe ruchy, aby 
    na pewnojej wartosc byla nizsza od mozliwych do wykonania ruchow

w - wiersze, k - kolumny, i - zmienna do wypelniania okreslonej
    przez pola liczby pol
ocena_przed - najlepsza dotychczasowa ocena planszy dla prawego gracza
ocena_teraz - ocena planszy w chwili obecnej
czy_legalny_ruch - zmienna wskazujaca czy da sie na danym ciagu pol
    postawic kreske
ruchy - liczba najlepszych ruchow w danej chwili
 */
int generowanie_ruchow(int PLANSZA[WIERSZE][KOLUMNY], int pola,
                       int WSPOLRZEDNE[WIERSZE * KOLUMNY][WYMIARY]) {
    int w, k, i;
    int czy_legalny_ruch, ocena_przed, ocena_teraz, ruchy;

    ocena_przed = -WIERSZE * KOLUMNY;
    ruchy = 0;

    for (w = 0; w < WIERSZE; w++) {
        czy_legalny_ruch = 0;
        k = 0;
        while (k < KOLUMNY) {
            if ((PLANSZA[w][k] != 0)) {
                czy_legalny_ruch = 0;
                k++;
            } else {
                czy_legalny_ruch++;
                if (czy_legalny_ruch == pola) {
                    czy_legalny_ruch = 0;
                    for (i = k - pola + 1; i <= k; i++) {
                        PLANSZA[w][i] = 1;
                    }
                    ocena_teraz = prawy_liczba_ruchow(PLANSZA, pola)
                                  - lewy_liczba_ruchow(PLANSZA, pola);
                    for (i = k - pola + 1; i <= k; i++) {
                        PLANSZA[w][i] = 0;
                    }
                    if (ocena_teraz > ocena_przed) {
                        ocena_przed = ocena_teraz;
                        zerowanie_ruchow(WSPOLRZEDNE, ruchy);
                        ruchy = 1;
                        WSPOLRZEDNE[0][PIERWSZA] = w;
                        WSPOLRZEDNE[0][DRUGA] = k - pola + 1;
                    } else if (ocena_teraz == ocena_przed) {
                        ruchy++;
                        WSPOLRZEDNE[ruchy - 1][PIERWSZA] = w;
                        WSPOLRZEDNE[ruchy - 1][DRUGA] = k - pola + 1;
                    }
                    k = k - pola + 2;
                } else {
                    k++;
                }
            }
        }
    }
    return ruchy;
}

/* funkcja nr 9
1) pobiera ruchy do wylosowania 
2) losuje, który ruch wybrać
3) stawia kreskę
4) wypisuje wybrany ruch na wyjście programu

wybrany_ruch - na tej zmiennej zapisany jest wylosowany ruch
mala_litera - pierwsza wspolrzedna
duza_litera - druga wspolrzedna
WSPOLRZEDNE[KOLUMNY*WIERSZE][WYMIARY] - tablica zapisujaca potencjalne ruchy,
    okreslone podczas generowania ruchow. Jej rozmiar wynosi ilosc
    wszystkich mozliwych ruchow do wykonania na planszy minus
    wymiar pola, ale dla niewielkich danych (26x26) uznalem to za
    czytelniejsze rozwiazanie
 */
void ruch_prawego(int PLANSZA[WIERSZE][KOLUMNY], int pola) {
    int i, wybrany_ruch, ruchy, mala_litera, duza_litera;
    int WSPOLRZEDNE[KOLUMNY * WIERSZE][WYMIARY];

    ruchy = generowanie_ruchow(PLANSZA, pola, WSPOLRZEDNE);
    wybrany_ruch = losuj_calkowita(ruchy);

    mala_litera = WSPOLRZEDNE[wybrany_ruch][PIERWSZA];
    duza_litera = WSPOLRZEDNE[wybrany_ruch][DRUGA];

    for (i = duza_litera; i < duza_litera + pola; i++) {
        PLANSZA[mala_litera][i] = 1;
    }

    wypisz(WSPOLRZEDNE, wybrany_ruch);
}

int main() {
    int pola;
    int GRAJ_DALEJ;
    int PLANSZA[WIERSZE][KOLUMNY];

#ifdef LOSOWE
    srand(LOSOWE);
#else
    srand(time(NULL));
#endif

    GRAJ_DALEJ = 1;
    pola = POLA;
    zerowanie_planszy(PLANSZA);

    while (GRAJ_DALEJ) {
        if (lewy_liczba_ruchow(PLANSZA, pola) != 0)
            GRAJ_DALEJ = ruch_lewego(PLANSZA, pola);
        else
            GRAJ_DALEJ = 0;

        if (GRAJ_DALEJ && (prawy_liczba_ruchow(PLANSZA, pola) != 0))
            ruch_prawego(PLANSZA, pola);
    }

    return 0;
}