#include <stdio.h>

#define filein "numeri.txt"

void verifica_sequenza(FILE *fin);

int main()
{
    FILE *fin;
    fin = fopen(filein, "r");
    if (fin == NULL)
    {
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    verifica_sequenza(fin);
    fclose(fin);
    return 0;
}

void verifica_sequenza(FILE *fin)
{
    int num_p = 0, num_s = 0, da_confrontare = 0, max, min, scartati = 0, condizione_1, condizione_div, verificati = 0;
    fscanf(fin, "%d", &num_p); // scansiono i primi due numeri in quanto il controllo parte dal terzo
    fscanf(fin, "%d", &num_s);
    if (num_p > max)
    {
        max = num_p; min = num_s;
    }
    else
    {
        min = num_p; max = num_s;
    }
    while(!feof(fin))
    {
        if (fscanf(fin, "%d", &da_confrontare) == 1) // controllo di non aver letto l'eof
        {
            condizione_1 = (num_p + num_s == da_confrontare || num_p - num_s == da_confrontare || num_p * num_s == da_confrontare);
            // spezzo le due condizioni per maggiore leggibilità
            condizione_div = ((num_s != 0) && num_p / num_s == da_confrontare);
            if (condizione_1 || condizione_div) // se le condizioni sono soddisfatte, controllo anche max e min
            {
                if (da_confrontare > max)
                    max = da_confrontare;
                if (da_confrontare < min)
                    min = da_confrontare;
                num_p = num_s;
                num_s = da_confrontare;
                verificati ++;
            }
            else
            {
                scartati++; // incremento il numero degli scartati (non rispettano nessuna delle condizioni)
                printf("Ho scartato il numero %d\n", da_confrontare);
                num_p = num_s; // il numero che precede diventa quello che segue
                fscanf(fin, "%d", &da_confrontare); // scansiono il numero che seguirà in quanto,
                // come da testo, scarto del tutto il numero che non rispetta nessuna condizione
                num_s = da_confrontare; //num_s diventa il numero che segue quello scartato
            }
        }
    }
    printf("Controllo su %d numeri terminato con %d numeri verificati\n\n", verificati+scartati, verificati);
    printf("Numero massimo: %d\nNumero minimo: %d\nNumeri scartati: %d", max, min, scartati);
}