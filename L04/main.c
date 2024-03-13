#include <stdio.h>
#define len_max 20

int leggi_matrice_e_trova_sottomatrici();
void trova_sottomatrici(int matrix[len_max][len_max], int dim, int nc, int nr);
int main(void)
{
    int codice_errore;
    codice_errore = leggi_matrice_e_trova_sottomatrici();
    return codice_errore;
}


int leggi_matrice_e_trova_sottomatrici() {
    FILE *f_in;
    char file_name[len_max];
    int nr = 0, nc = 0, dim = 1, i, j, matrix[len_max][len_max], finito = 0;
    printf("Inserisci il nome del file da aprire:");
    scanf("%s", file_name);
    f_in = fopen(file_name, "r");
    if (f_in == NULL) {
        printf("Errore nell'apertura del file");
        return 1;
    }
    // leggo il numero di righe e di colonne
    fscanf(f_in, "%d %d ", &nr, &nc);
    //definisco la matrice con le dimensioni lette
    if (nc <= len_max && nr <= len_max) {
        printf("\n");
        for (i = 0; i < nr; i++) {
            for (j = 0; j < nc; j++) {
                fscanf(f_in, "%d", &matrix[i][j]);
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    } else if (nc > len_max) {
        printf("\nErrore, la matrice da te inserita ha %d righe e %d colonne e supera la dimensione massima consentita di colonne (%d)",
               nr, nc, len_max);
        return 2;
    } else if (nr > len_max) {
        printf("\nErrore, la matrice da te inserita ha %d righe e %d colonne e supera la dimensione massima consentita di righe (%d)",
               nr, nc, len_max);
        return 3;
    }
    while (!finito)
    {
        printf("\nInserisci la dimensione di ogni sottomatrice quadrata:");
        if (scanf("%d", &dim) == 1 && dim <= nc && dim <= nr && dim != 1)
            trova_sottomatrici(matrix, dim, nc, nr);
        else
        {
            printf("\nProgramma terminato per via delle dimensioni delle sottomatrici errate.");
            finito = 1;
        }
    }
    fclose(f_in);
    return 0;
}

void trova_sottomatrici(int matrix[len_max][len_max], int dim, int nc, int nr)
{
    int i, j, h, k, cont_1 = 0, cont_2 = 0, somma = 1, somma_max = -10000, riga_max_somma = 0, col_max_somma = 0;
    for(i = 0; i + dim <= nr; i++) // fin quando i + dim < numero di righe (questo ciclo sposta di una riga verso il basso sotto-matrice)
    {
        for(j = 0; j + dim <= nc; j++) // fin quando j + dim < numero di colonne, (questo ciclo sposta di una colonna a destra la sottomatrice)
        {
            for(k = i; cont_1 < dim; k++) // imposto k = i (cioè corrisponde alla riga i-esima) e un contatore per le righe che faccia far dim iterazioni
            {
                for(h = j; cont_2 < dim; h++) // imposto h = j (cioè corrisponde alla col i-esima) e un contatore per le colonne che faccia far dim iterazioni
                {
                    printf("%d ", matrix[k][h]); //stampo l'intero presente in posizione (k,h)
                    cont_2++; //incremento il contatore delle colonne
                    somma += matrix[k][h]; // sommo l'intero corrispondente alla somma totale della sotto-matrice
                }
                printf("\n"); // stampo a capo quando finisco la colonna
                cont_1++; cont_2 = 0; // incremento il contatore delle righe e imposto il contatore delle colonne a 0 in modo che rifaccia dim iterazioni
            }
            if (somma >= somma_max) // se la somma totale della sotto-matrice > somma_max
            {
                riga_max_somma = i; // allora la riga max di inizio sarà la i-esima
                col_max_somma = j; // la colonna max di inizio sarà la j-esima
                somma_max = somma;
            }
            printf("\n"); //stampo un a capo per separare la prossima sottomatrice
            somma = 0; // resetto la somma
            cont_1 = 0; // resetto il contatore delle righe
        }
    }
    printf("\nLa somma massima delle seguente sotto-matrice vale %d:\n", somma_max);
    cont_1 = 0; cont_2 = 0;
    for (i = riga_max_somma; cont_1 < dim; i++)
    {
        for(j=col_max_somma; cont_2 < dim; j++)
        {
            printf("%d ", matrix[i][j]); cont_2++;
        }
        printf("\n");
        cont_2 = 0;
        cont_1 ++;
    }
}