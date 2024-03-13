/* Si scriva un programma che calcoli l’area di un cerchio o di un quadrato in base alla scelta dell’utente.
L’utente può specificare se calcolare l’area del quadrato (Q) tramite la lunghezza della diagonale (D) o del lato (L), mentre l’area del cerchio (C)
specificando se tramite il diametro (D) oppure il raggio (R).
Esempio: Se l’utente inserisce Q D10, il programma dovrà stampare a schermo
Area Quadrato = 50.0
In particolare:
a) Si definisca una costante P tramite #define, e gli si assegni il valore 3.14, (nota: con la
define non si mette né l’= né il ;)
b) Si acquisiscano i caratteri da tastiera.
c) Si calcoli il valore dell’area in base alla scelta dell’utente.
d) Si stampi il risultato a video.
Nota: Quadrato: Area = L*L = D*D/2, Cerchio: Area = pi*R*R = pi*D*D/4) */

#include <stdio.h>
#define P 3.14 //dichiaro la variabile globale P

int main(void)
{
    // DICHIARAZIONE VARIABILI
    char Q_or_C; //carattere di scelta se quadrato o cerchio
    char dimensione; //scelta tra lunghezza/diagonale oppure tra diametro e raggio
    float lunghezza; //lunghezza della dimensione
    float area;
    Q_or_C = 'a';
    dimensione = 'a';
    lunghezza = 1.0;
    area = 1.0;
    printf("%s", "Benvenuto!\nScegli se vuoi lavorare su un quadrato (Q) o su un cerchio (C):\n");
    scanf("%c", &Q_or_C); //ottengo il carattere Q o C e lo assegno a Q or C

    if (Q_or_C == 'Q')
    {

        printf("Scegli se vuoi ottenere l'area del quadrato tramite diagonale (D) o tramite lato (L):\n");
        scanf(" %c", &dimensione);
        printf("Inserisci la dimensione della lunghezza che hai scelto:\n");
        scanf("%f", &lunghezza);
        if (dimensione == 'D')
        {
            area = lunghezza*lunghezza/2;
        }
        else if (dimensione == 'L')
        {
            area = lunghezza*lunghezza;
        }
        else
            return 1;
    }
    else if (Q_or_C == 'C')
    {
        printf("Scegli se vuoi ottenere l'area del quadrato tramite diametro (D) o tramite raggio (R):\n");
        scanf(" %c", &dimensione);
        printf("Inserisci la dimensione della lunghezza che hai scelto:\n");
        scanf("%f", &lunghezza);
        if (dimensione == 'D')
        {
            lunghezza /= 2;
            area = P*lunghezza*lunghezza;
        }
        else if (dimensione == 'R')
        {
            area = P*lunghezza*lunghezza;
        }
        else
            return 1;
    }
    else
        return 1;
    printf("L'area vale: %.2f", area);
    return 0;

}