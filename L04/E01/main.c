#include <stdio.h>
#define len_max 30
int leggi_vettore_da_file(FILE *fp_in, int vettore[len_max]);
void sottosequenze(int vettore[len_max], int N);

int main(void)
{
    FILE *fp_in = NULL;
    int V[len_max] = {0}, lunghezza_effettiva;
    char nome_file[20];
    printf("Inserisci il nome del file da cui estrapolare gli interi del vettore:\n"
           "N.B. Il file dovra' contenere ad esempio 1 2 3 4 5 0 1 . . .\n"
           "Nome file: ");
    scanf("%s", nome_file);
    fp_in = fopen(nome_file, "r");
    if (fp_in == NULL)
    {
        printf("\nErrore nell'apertura del file");
        return 1;
    }
    //Leggo il file
    lunghezza_effettiva = leggi_vettore_da_file(fp_in, V);
    printf("\nNel vettore sono presenti %d interi", lunghezza_effettiva);
    sottosequenze(V, lunghezza_effettiva);
    fclose(fp_in);
    return 0;
}


int leggi_vettore_da_file(FILE *fp_in, int vettore[])
{
    int i = 0, valore;
    printf("\nHo letto i seguenti valori:\n[ ");
    while(!feof(fp_in) && i < len_max)
    {
        if (fscanf(fp_in, "%d", &valore) == 1) {
            vettore[i] = valore;
            printf("%d ", vettore[i++]);
        }
    }
    printf("]");
    if (i == len_max)
        printf("\n!!!Ho smesso di leggere il file al %d-esimo intero!!!", i);
    return i;
}

void sottosequenze(int vettore[len_max], int N)
{
    int max_lenght = 0, cont = 0, i, j; //implicitamente imposto tutte le lunghezze a 0;
    // trovo la lunghezza massima di ogni sotto-intervallo
    for (i = 0; i < N; i++)
    {
        if(vettore[i] != 0)
            cont++;
        else
        {
            if (cont >= max_lenght)
                max_lenght = cont;
            cont = 0;
        }
    }
    printf("\nAl massimo posso dividere il vettore in sotto-intervalli da %d interi ciascuno", max_lenght);
    // stampo le sottosequenze di lunghezza massima esistenti (non contenenti zeri)
    cont = 0;
    for(i=0; i < N; i++) //controllo, su tutto il vettore le varie sotto-sequenze
    {
        if(vettore[i] != 0)
            cont++;
        else
            cont = 0;
        if(cont == max_lenght) //se ho una sotto-sequenza con dim=max_lenght
        {
            printf("\n[ ");
            for(j = (i +1 - max_lenght); j <= i; j++) //stampo dal primo carattere != 0 che è = i+1-max_lengt
                printf("%d ", vettore[j]);
            printf("]");
            cont = 0;
        }
    }
}
