#include <stdio.h>
#define MAX_L 20
int leggi_matrice(FILE *fp_in, int matrix[MAX_L][MAX_L], int nr, int nc);
void leggi_giornata(int matrix[MAX_L][MAX_L], int nr, int k);

int main(void)
{
    int matrix[MAX_L][MAX_L], nr, nc, k = 1, errore = 0;
    char nome_file[MAX_L];
    // LETTURA FILE
    FILE *fp_in;
    printf("Inserire il nome del file di input:"); scanf("%s", nome_file);
    fp_in = fopen(nome_file, "r");
    if (fp_in == NULL)
    {
        printf("\nErrore nell'apertura del file."); return 1;
    }
    else
    {
        fscanf(fp_in, "%d %d ", &nr, &nc);
        printf("\nLa matrice contenente la classifica e' la seguente:\n\n");
        errore = leggi_matrice(fp_in, matrix, nr, nc);
        fclose(fp_in);
        if (errore == 0)
        {
            printf("\nIl campionato consta di %d squadre e %d giornate", nr, nc);
            while (k <= nc)
            {
                leggi_giornata(matrix, nr, k);
                k++;
            }
        }
    }
    return errore;
}

int leggi_matrice(FILE *fp_in, int matrix[MAX_L][MAX_L], int nr, int nc)
{
    int i, j, errore = 0;
    int punteggio_accettabile = 0;
    for (i = 0; i < nr; i++)
    {
        for(j = 0; j < nc; j++)
        {
            if (fscanf(fp_in, "%d ", &matrix[i][j]) == 1) // la matrice verrà restituita al main (essendo passata by reference)
            {
                punteggio_accettabile = (matrix[i][j] == 0 || matrix[i][j] == 1 || matrix[i][j] == 3); // il punteggio può essere 0,1 o 3 per essere accettabile
                if (punteggio_accettabile) // se il punteggio è accettabile
                    printf("%d ", matrix[i][j]); // stampo l'elemento della matrice corrispondente
                else // se non lo è, termino l'esecuzione del programma e genero errore
                {
                    printf("\nErrore, ho letto un punteggio errato (%d) della squadra %d alla giornata %d", matrix[i][j], i+1, j + 1);
                    errore = 2; return errore;
                }
            }
            else // se manca un punteggio in una riga
            {
                printf("\nErrore, formato della matrice errato nella riga del file n. %d.", i+1);
                errore = 3; return errore;
            }
        }
        printf("\n");
    }
    return errore;
}

void leggi_giornata(int matrix[MAX_L][MAX_L], int nr, int k)
{
    int i, j, somma = 0, somma_max = -1, riga = 0;
    for (i = 0; i < nr; i++) // per ogni giornata
    {
        for(j = 0; j < k; j++) // per ogni squadra
        {
            somma += matrix[i][j];
        }
        if (somma > somma_max)
        {
            somma_max = somma; riga = i+1; // imposto la somma max = somma e la riga corrispondente alla squadra capolista come i+1 (evito che sia 0)
        }
        somma = 0;
    }
    printf("\nLa capolista alla giornata %d e' la squadra numero %d con una somma punti pari a %d.", k, riga, somma_max);
}