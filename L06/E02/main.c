#include <stdio.h>
#include <ctype.h>
#include <string.h>

typedef struct{
    char nome_seq[20];
    int ripetizioni[10];
    char parola_effettiva[10][25];
    int cont;
}sequenze;

int leggi_sequenza(FILE *fp_seq, sequenze vettore_struct[]);
void verifica_sequenze(FILE *fp_open, sequenze vettore_struct[], int num_seq);
void stampa_vettore_struct(sequenze vettore_struct[], int num_seq);

int main(void)
{
    FILE *fp_in_seq, *fp_in;
    char sequenza[20], input[20];
    sequenze vettore_struct[20];
    int num_seq;
    printf("Inserire nome file sequenze:"); scanf("%s", sequenza);
    printf("\nInserisci nome file input:"); scanf("%s", input);
    fp_in = fopen(input, "r");
    fp_in_seq = fopen(sequenza, "r");
    if (fp_in != NULL && fp_in_seq != NULL)
    {
        num_seq = leggi_sequenza(fp_in_seq, vettore_struct);
        verifica_sequenze(fp_in, vettore_struct, num_seq);
        stampa_vettore_struct(vettore_struct, num_seq);
    }
    else
        printf("\nErrore nell'acquisizione del file.");

    return 0;
}


int leggi_sequenza(FILE *fp_seq, sequenze vettore_struct[])
{
    int num_seq, i;
    fscanf(fp_seq, "%d", &num_seq);
    printf("\nHo trovato %d sequenze:", num_seq);
    for (i=0; i < num_seq; i++)
    {
        fscanf(fp_seq, "%s", vettore_struct[i].nome_seq);
        vettore_struct[i].cont = 0;
        printf("\n%s", vettore_struct[i].nome_seq);
    }
    return num_seq;
}


void verifica_sequenze(FILE *fp_open, sequenze vettore_struct[], int num_seq)
{
    char parola_attuale[25];
    int i, j,k, trovato, cont_parole = 1;
    while (fscanf(fp_open, "%s", parola_attuale) == 1)
    {
        for (j = 0; j < strlen(parola_attuale)-1; j++)
            if (ispunct(parola_attuale[j]))
                cont_parole+=1;
        for(i=0; i < num_seq; i++) //CICLO SULLE SEQUENZE
        {
            trovato = 0;
            for (j = 0; j < strlen(parola_attuale); j++) //CICLO SUI CARATTERI DELLA PAROLA
            {
                for (k = 0; k < strlen(vettore_struct[i].nome_seq); k++)  // CICLO SUI CARATTERI DELLA SOTTOSEQ.
                {
                    if (tolower(vettore_struct[i].nome_seq[k]) == tolower(parola_attuale[j + k]))
                        trovato = 1;
                    else {
                        trovato = 0;
                        break;
                    }
                }
                if (trovato)
                {
                    strcpy(vettore_struct[i].parola_effettiva[vettore_struct[i].cont], parola_attuale);
                    vettore_struct[i].ripetizioni[vettore_struct[i].cont] = cont_parole;
                    vettore_struct[i].cont += 1;
                    break;
                }
            }
        if(trovato)
            break;
        }
        cont_parole+=1;
    }
}

void stampa_vettore_struct(sequenze vettore_struct[], int num_seq)
{
    int i, contatore_rip, j;
    for (i=0; i < num_seq; i++)
    {
        contatore_rip = vettore_struct[i].cont;
        if (contatore_rip == 0)
            printf("\nNon ho trovato alcuna sottosequenza '%s' nel testo.", vettore_struct[i].nome_seq);
        else
        {
            printf("\nLa sottosequenza '%s' e' stata trovata:", vettore_struct[i].nome_seq);
            for (j = 0; j < contatore_rip; j++)
                printf("\n   Nella parola '%s' in posizione %d", vettore_struct[i].parola_effettiva[j],
                       vettore_struct[i].ripetizioni[j]);
        }
    }
}