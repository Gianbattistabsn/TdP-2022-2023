#include <stdio.h>
#define max_l 100

void riempi_vettore(FILE *fp_in, int nc, int v_1[max_l], int v_2[max_l], int v_3[max_l]);
void selection_sort(int vett[max_l], int nc);
void insertion_sort(int vett[max_l], int nc);
void shell_sort(int vett[max_l], int nc);
void stampa_riga_ordinata(int v[max_l], int n);


int main(int argc, char *argv[])
{
    // DICHIARAZIONE VARIABILI
        int nr = 0, nc = 0;
        int copia_selection[max_l], copia_insertion[max_l], copia_shell[max_l];
        FILE *fp_in = NULL;
    // GESTIONE ERRORI INPUT
        if (argc != 2)
        {
            printf("Errore, numero di argomenti non valido, inserire il nome del file.");
            return 1;
        }
        fp_in = fopen(argv[1], "r");
        if (fp_in == NULL)
        {
            printf("Errore, file inserito non valido.");
            return 1;
        }
    // BODY
    // scansiono il numero di righe del file (quanti vettori dovrò ordinare con ogni metodo)
    fscanf(fp_in, "%d", &nr);

    // ITERAZIONI DI OGNI RIGA (vettore) CON OGNUNO DEI TRE METODI
    for (int i = 0; i < nr; i++)
    {
        // Acquisizione del numero di elementi di ciascuna riga
        fscanf(fp_in, "%d", &nc);
        // RIEMPIO I TRE VETTORI CON GLI STESSI ELEMENTI CHE VERRANNO ORDINATI DAI VARI ALGORITMI
            riempi_vettore(fp_in, nc, copia_selection, copia_insertion, copia_shell);
            // STAMPO IL VETTORE DI PARTENZA
            printf("\n\n----VETTORE DI PARTENZA (RIGA n.%d, %d ELEMENTI)----", i+1,nc);
            stampa_riga_ordinata(copia_selection, nc);
            //SELECTION SORT
            printf("\n\nSELECTION SORT:");
            selection_sort(copia_selection, nc);
            //INSERTION SORT
            printf("\n\nINSERTION SORT:");
            insertion_sort(copia_insertion, nc);
            //SHELL SORT
            printf("\n\nSHELL SORT:");
            shell_sort(copia_shell,nc);
    }
}


void riempi_vettore(FILE *fp_in, int nc, int v_1[max_l], int v_2[max_l], int v_3[max_l])
{
    int j, val;
    for (j = 0; j < nc && fscanf(fp_in, "%d ", &val) == 1; j++)
    {
        v_1[j] = val;
        v_2[j] = val;
        v_3[j] = val;
    }
}


void selection_sort(int vettore[max_l], int nc)
{
    // variabili utili per l'esercizio
    int n_scambi, n_iter_ext = 0, n_iter_int = 0, n_tot = 0, n_scambi_tot = 0;
    // Variabili utili per l'algoritmo
    int i, min, j, pos, scambi;

    for (i = 0; i < nc-1; i++)
    {
        min = vettore[i];
        scambi = 0; // parto dicendo di non aver trovato un elemento minimo (FALSO)
        n_scambi = 0;
        for (j = i+1; j < nc; j++)
        {
            if (vettore[j] < min)
            {
                pos = j;
                min = vettore[j];
                scambi = 1; // Ho trovato l'elemento minimo
            }
            n_iter_int++;
        }
        if (scambi)
        {
            vettore[pos] = vettore[i];
            vettore[i] = min;
            n_scambi = scambi;
        }
        n_scambi_tot++;
        n_iter_ext++;
        n_tot = n_tot + 1 + n_iter_int;
        printf("\nIterazione esterna n.%d, numero iterazioni interne: %d, numero scambi: %d;", n_iter_ext, n_iter_int, n_scambi);
        n_iter_int = 0;
    }

    printf("\n\nNumero ITERAZIONI TOTALI della riga tramite SELECTION SORT = %d, numero SCAMBI TOTALI = %d.", n_tot, n_scambi_tot);
    printf("\n\nVettore ordinato tramite Selection Sort:");
    stampa_riga_ordinata(vettore, nc);
}
/* Nel Selection sort le iterazioni del ciclo esterno sono sempre pari a n-1
 * Per ogni passo, il ciclo esterno farà n-i iterazioni (quindi, alla fine dei conti,
 * si ritorna alla sommatoria dei primi (n-1) numeri naturali) = > dalla formula di gauss
 * n(n+1)/2 da la somma dei primi n numeri a cui bisogna sottrarre la singola iterazione che vedrebbe l'ultima componente del vettore
 * già ordinata. Infatti, per 30 elementi, si conferma 15*31 = 465 -1 = 464.
 */
void insertion_sort(int vett[max_l], int nc)
{
    // Variabili utili per l'algoritmo
    int i, j, tmp;
    // Variabili utili per l'esercizio
    int n_scambi, n_iter_ext = 0, n_iter_int = 0, n_tot = 0, n_scambi_tot = 0;

    for (i = 1; i < nc; i++)
    {
        tmp = vett[i];
        n_scambi = 0;
        j = i-1;
        while (j >= 0 && tmp < vett[j])
        {
            vett[j+1] = vett[j];
            j--;
            n_scambi++;
            n_iter_int++;
        }
        vett[j+1] = tmp;
        n_iter_ext++;
        n_tot = n_tot + 1 + n_iter_int;
        n_scambi_tot+=n_scambi;
        printf("\nIterazione esterna n.%d, numero iterazioni interne: %d, num_scambi = %d;", n_iter_ext, n_iter_int, n_scambi);
        n_iter_int = 0;
    }
    printf("\n\nNumero ITERAZIONI TOTALI della riga tramite INSERTION SORT = %d, numero di SCAMBI TOTALI = %d.", n_tot, n_scambi_tot);
    printf("\n\nVettore ordinato tramite INSERTION SORT: ");
    stampa_riga_ordinata(vett, nc);
}


void shell_sort(int v[max_l], int n)
{
    // Variabili utili per l'algoritmo
    int i, j,h=1, tmp;
    // Variabili utili per l'esercizio
    int n_scambi = 0, n_iter_ext = 0, n_iter_int, n_tot = 0, n_scambi_tot = 0;
    // SEQUENZA DI KNUKHT
    while(h <= n/3) // trovo il nodo massimo da cui partire
        h = 3*h+1;

    while (h>=1) // Il ciclo viene eseguito fin quando non confronto elemento per elemento (h = 1)
    {
        // INSERTION SORT
        for (i = h; i < n; i++)
        {
            n_scambi = 0;
            n_iter_int = 0;
            n_iter_ext++;
            tmp = v[i];
            j = i-h;
            while(j >= 0 && v[j]>tmp)
            {
                v[j+h] = v[j];
                j = j-h;
                n_scambi++;
                n_iter_int++;
            }
            v[j+h] = tmp;
            n_tot = n_tot + 1 + n_iter_int;
            printf("\nIterazione esterna n.%d, numero iterazioni interne: %d, num_scambi = %d;", n_iter_ext, n_iter_int, n_scambi);
            n_scambi_tot += n_scambi;
        }
        h = (h-1)/3; // nodo precedente
    }
    printf("\n\nNumero ITERAZIONI TOTALI della riga tramite SHELL SORT = %d, numero di SCAMBI TOTALI = %d.", n_tot, n_scambi_tot);
    printf("\n\nVettore ordinato tramite SHELL SORT: ");
    stampa_riga_ordinata(v, n);
}

void stampa_riga_ordinata(int vett[max_l], int nc)
{
    int i;
    printf("\n[ ");
    for (i = 0; i < nc; i++)
        printf("%d ", vett[i]);
    printf("]");
}