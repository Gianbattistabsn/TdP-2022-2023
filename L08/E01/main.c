#include <stdio.h>
#define MAX_L 50
#define file_name "mappa.txt"

// La prima parte della consegna era già stata implementata nel LAB07 in modo da evitare di far restituire alla funzione leggi_file una struct.

typedef struct{
  int b,h,area, r,c;
}Regioni;

// FUNZIONI
int leggiMatrice(int input_matrix[][MAX_L], int MAX_R, int *nr, int *nc); // lettura file di input
int riconosciRegione(int input_matrix[MAX_L][MAX_L], int nr, int nc, int r, int c, int* b, int* h);
void find_rettangoli(int input_matrix[MAX_L][MAX_L], int nr, int nc);
void stampa_max(Regioni vett_max[3]);


int main(void)
{
    int nr, nc, error;
    int input_matrix[MAX_L][MAX_L];
    // LETTURA FILE DI INPUT, CONTROLLO ERRORI E PRINT DELL'INPUT
    error = leggiMatrice(input_matrix, MAX_L, &nr, &nc);
    if (error) // Gestione dell'errore nel caso in cui dovesse mancare il file 'mappe.txt'
        return error;
    // TROVA TUTTE LE REGIONI PRESENTI NEL FILE E STAMPA QUELLE CHE SODDISFANO I CRITERI
    find_rettangoli(input_matrix, nr, nc);
    return 0;
}


int leggiMatrice(int input_matrix[][MAX_L], int MAX_R, int* nr, int* nc)
{
    int i, j;
    FILE *fp_in;
    // APERTURA FILE E GESTIONE ERRORE
    fp_in = fopen(file_name, "r");
    if (fp_in == NULL){
        printf("Errore nell'apertura del file"); return 1;}
    // RIEMPIMENTO E PRINT DELLA MATRICE DI INPUT
    fscanf(fp_in, "%d %d", nr, nc);
    if (*nr > 0 && *nc > 0 && *nr < MAX_R)
    {
        printf("Matrice in input:\n\n");
        for (i = 0; i < *nr; i++) {
            for (j = 0; j < *nc; j++) {
                fscanf(fp_in, "%d ", &input_matrix[i][j]);
                printf("%d ", input_matrix[i][j]);
            }
            printf("\n");
        }
    }
    else // se ci fossero problemi con le dimensioni del file:
    {
        printf("Errore con le dimensioni indicate nel file.\n"); return 1;
    }
    fclose(fp_in); // chiusura file
    return 0;
}


void find_rettangoli(int input_matrix[MAX_L][MAX_L], int nr, int nc)
{
    int i, j, b, h, a, max_b = 0, max_h = 0, max_a = 0;
    Regioni vett_regioni[3], tmp;

    for (i = 0; i < nr; i++) // CICLO SULLE RIGHE
    {
        for (j = 0; j < nc; j++) // CICLO SULLE COLONNE
            if (riconosciRegione(input_matrix, nr, nc, i, j, &b, &h)) //Se ho trovato una regione con estremo superiore:
            {
                a = b*h;
                tmp.b = b;
                tmp.h = h;
                tmp.area = a;
                tmp.r = i;
                tmp.c = j;
                if (b > max_b)
                {
                    max_b = b;
                    vett_regioni[0] = tmp;
                }
                if (h > max_h)
                {
                    max_h = h;
                    vett_regioni[1] = tmp;
                }
                if (a > max_a)
                {
                    max_a = a;
                    vett_regioni[2] = tmp;
                }
                printf("\nHo trovato una regione con estremo superiore in <%d,%d>, base = %d, altezza = %d, area = %d", i,j, b,h,a);
                if (j + b + 1< nc)
                    j = j+b; // passo direttamente a considerare le caselle successive.
            }
    }
    printf("\n");
    // PRINT DEL MASSIMO DELLE REGIONI:
    stampa_max(vett_regioni);
}

int riconosciRegione(int input_matrix[MAX_L][MAX_L], int nr, int nc, int r, int c, int* b, int* h)
{
    int i, j, rettangolo, trovato = 0, flag_forzata, flag_necessaria;
    *b = 0;
    *h = 1;
    // rettangolo è utile per verificare la necessità di entrare nel ciclo, se le caselle r e c acquisite dall'input
    // dell'utente sono delle caselle nere, allora, entro nel ciclo.
    rettangolo = input_matrix[r][c]; // SE LA CASELLA CHE CONSIDERO è 1
    flag_forzata = (c == 0 && r == 0) || c == 0; // se la casella che considero si trova su un bordo che potrebbe sforare
    flag_necessaria = (rettangolo && (input_matrix[r][c-1] != 1 && input_matrix[r-1][c] != 1)); //flag necessaria per entrare a fare il controllo
    if (flag_forzata || flag_necessaria) // se almeno una delle due condizioni è verificata, allora entro a fare il controllo
    {
        // CONTROLLO SULLE COLONNE C-ESIME
        for (j = c; j < nc && rettangolo; j++)
        {
            rettangolo = input_matrix[r][j];
            if (rettangolo)
            {
                *b = *b + 1;
                trovato = 1;
            }
        }
        // CONTROLLO SULLE RIGHE SOTTOSTANTI
        for (i = r+1; i < nr; i++)
        {
            rettangolo = input_matrix[i][c]; // considero la riga successiva ma la colonna precedente.
            if (rettangolo)
                (*h)++;
            else
                return trovato;   // posso già segnalare di aver trovato la regione visto che ho letto tutto il rettangolo.
        }
    }
    return trovato; // in tutti gli altri casi, non avrò trovato la regione.
}

void stampa_max(Regioni vett_regioni[3])
{
    printf("\nMAX BASE: coord. estremo <%d,%d>, altezza = %d, base = %d, area = %d", vett_regioni[0].r, vett_regioni[0].c, vett_regioni[0].h, vett_regioni[0].b, vett_regioni[0].area);
    printf("\nMAX ALTEZZA: coord. estremo <%d,%d>, altezza = %d, base = %d, area = %d", vett_regioni[1].r, vett_regioni[1].c, vett_regioni[1].h, vett_regioni[1].b, vett_regioni[1].area);
    printf("\nMAX AREA: coord. estremo <%d,%d>, altezza = %d, base = %d, area = %d", vett_regioni[2].r, vett_regioni[2].c, vett_regioni[2].h, vett_regioni[2].b, vett_regioni[2].area);
}