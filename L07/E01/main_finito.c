#include <stdio.h>
#define MAX_L 50
#define FILE_NAME "mappa.txt"

typedef struct{
    int h, b, a, r, c;
}regione;

int leggi_file(int input_matrix[][MAX_L], int *nr, int *nc); // lettura file di input
void trovaRegioni(int matrix[MAX_L][MAX_L], int nr, int nc);

int main(void) {
    //Inizializzazione variabili
    int nr, nc, input_matrix[MAX_L][MAX_L], error;
    // Lettura del file di input e riempimento della matrice di input
    // Passo alla funzione anche l'indirizzo di memoria di nr e nc in modo da averle in seguito.
    error = leggi_file(input_matrix, &nr, &nc);
    // Gestione dell'errore nel caso in cui dovesse mancare il file 'mappe.txt'
    if (error)
        return error;
    // Controllo delle regioni che presentano rettangoli neri e print dell'output
    trovaRegioni(input_matrix,nr,nc);
    return 0;
}
//Funzioni

int leggi_file(int input_matrix[][MAX_L], int* nr, int* nc)
{
    int i, j;
    FILE *fp_in;
    // Apertura file
    fp_in = fopen(FILE_NAME, "r");
    // Controllo file
    if (fp_in == NULL){
        printf("Errore nell'apertura del file"); return 1;}
    // lettura del numero di righe e di colonne che, al contempo, restituisco al main by pointer
    fscanf(fp_in, "%d %d", nr, nc);
    if (nr > 0 && nc > 0)
    {
        printf("Matrice in input:\n\n"); // Acquisizione e print della matrice in input
        for (i = 0; i < *nr; i++)
        {
            for (j = 0; j < *nc; j++)
            {
                fscanf(fp_in, "%d ", &input_matrix[i][j]);
                printf("%d ", input_matrix[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        printf("Errore con le dimensioni indicate nel file.\n");
        return 1;
    }
    fclose(fp_in); // chiusura file
    return 0;
}

void trovaRegioni(int matrix[MAX_L][MAX_L], int nr, int nc){
    regione temp; // variabile temporanea utile per l'allocazione temporanea di informazioni
    regione vettRegioni[3];
    int nero, first, k;
    // inizializzazione del vettore contenente il risultato:
    for (int cont = 0; cont < 3; cont++)
    {
        vettRegioni[cont].h = 0; vettRegioni[cont].b = 0; vettRegioni[cont].a = 0;
    }
    //Corpo funzione
    printf("\n");
    for(int i=0; i<nr; i++) // ciclo righe
    {
        first = 1;
        for (int j = 0; j < nc; j++) // ciclo colonne
        {
            nero = matrix[i][j];
            if (nero && first) // se incontro per la prima volta uno spazio nero
            {
                temp.r = i;
                temp.c = j;
                temp.h = 1;
                temp.b = 1;
                first = 0;
            }
            else if(nero && !first) // se non è la prima volta, allora, incremento solo la base
                temp.b++;
            // VERIFICA DELLE RIGHE SOTTOSTANTI NEL CASO NECESSARIO:
            if (j == nc-1  && nero || (!nero && !first)) // Se arrivo alla fine della riga oppure ho finito non è più uno spazio nero
            {
                // significa che devo ora controllare le righe sottostanti
                for (k = i+1; k < nr; k++) // controllo dalla riga successiva in poi
                {
                    nero = matrix[k][temp.c];
                    if (nero)
                        temp.h++;
                    if (!nero || k == nr-1) // se ho finito le righe a disposizione o se la regione non è più nera
                    {
                        temp.a = temp.h * temp.b;
                        if (temp.b > vettRegioni[0].b)
                        {
                            vettRegioni[0].b = temp.b;
                            vettRegioni[0].h = temp.h;
                            vettRegioni[0].a = temp.a;
                            vettRegioni[0].r = temp.r;
                            vettRegioni[0].c = temp.c;
                        }
                        if (temp.h > vettRegioni[1].h)
                        {
                            vettRegioni[1].b = temp.b;
                            vettRegioni[1].h = temp.h;
                            vettRegioni[1].a = temp.a;
                            vettRegioni[1].r = temp.r;
                            vettRegioni[1].c = temp.c;
                        }
                        if (temp.a > vettRegioni[2].a)
                        {
                            vettRegioni[2].b = temp.b;
                            vettRegioni[2].h = temp.h;
                            vettRegioni[2].a = temp.a;
                            vettRegioni[2].r = temp.r;
                            vettRegioni[2].c = temp.c;
                        }
                        break; // termino l'esecuzione del ciclo sulle righe
                    }
                }
                first = 1;
            }
        }
    }
    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[0].r,vettRegioni[0].c,vettRegioni[0].b,vettRegioni[0].h,vettRegioni[0].a);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[1].r,vettRegioni[1].c,vettRegioni[1].b,vettRegioni[1].h,vettRegioni[1].a);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", vettRegioni[2].r,vettRegioni[2].c,vettRegioni[2].b,vettRegioni[2].h,vettRegioni[2].a);
}
