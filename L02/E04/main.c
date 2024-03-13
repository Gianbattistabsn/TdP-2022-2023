#include <stdio.h>
#include <ctype.h>
// 248 diventa '2'-'0' = 2 + 0, poi '4'-'0' = 4, 4+1 = 5, '8' -'0' = 8, 8+2 = 0
int codifica (FILE *fin, FILE *fout);
int decodifica (FILE *fin, FILE *fout);
int main(void)
{
    FILE *f_in, *f_out;
    char scelta, nome_fin[20], nome_fout[20];
    printf("Vuoi codificare o decodificare un file:\n'C' per codificare, 'D' per decodificare.\n");
    scanf("%c", &scelta);
    if (toupper(scelta) != 'C' && toupper(scelta) != 'D')
    {
        printf("Errore nella scelta.");
        return 1;
    }
    else
    {
        printf("Inserisci il nome del file di input:");
        scanf("%s", &nome_fin);
        printf("Inserisci il nome del file di output:");
        scanf("%s", &nome_fout);
        f_in = fopen(nome_fin, "r");
        f_out = fopen(nome_fout, "w");
        if (f_in == NULL)
        {
            printf("Errore nell'apertura del file di input.");
            return 1;
        }
        if (f_out == NULL)
        {
            printf("Errore nell'apertura del file di output.");
            return 1;
        }
        if (toupper(scelta) == 'C')
        {
            codifica(f_in, f_out);
        }
        else
        {
            decodifica(f_in, f_out);
        }
    }
}

int codifica(FILE *fin, FILE *fout)
{
    int num=0, car=0, numero = 0, precedente = 1;
    char carattere = '$';

    while(!feof(fin))
    {
        fscanf(fin, "%c", &carattere); // scansiono il carattere
        if (isdigit(carattere)) // se è un numero
        {
            numero = (int)(carattere - '0' + num) % 10; // allora converto il numero in intero e lo stampo in modulo 10 (con il resto)
            fprintf(fout, "%d", numero);
            num++; // incremento
            precedente = 1; //cioè segno che ha letto un carattere non alfabetico
        }
        else if (isupper(carattere) || islower(carattere)) // se è un carattere maiuscolo o minuscolo
        {
            if (precedente != 1) // se il precedente era un altra lettera dell'alfabeto
            {
                if (isupper(carattere)) //se il carattere è maiuscolo
                {
                    carattere = ((carattere + car) - 'A') % 26 + 'A' ;
                    fprintf(fout, "%c", carattere);
                    car = carattere -'A';
                }
                else // se il carattere è minuscolo
                {
                    carattere = ((carattere + car) - 'a') % 26 + 'a' ;
                    fprintf(fout, "%c", carattere);
                    car = carattere -'a';
                }
            }
            else // altrimenti, se il precedente non era una una lettera dell'alfabeto
            {
                if (isupper(carattere)) // se il carattere che ho letto è maiuscolo
                        car = carattere - 'A'; // l'incremento sarà dato da carattere - 'A' posizioni più avanti
                else // se è minuscolo:
                    car = carattere -'a';
                fprintf(fout, "%c", carattere); // stampo comunque il carattere
                precedente = 2; // ora il precedente è un carattere (andrò a leggere un altro carattere magari)
            }
        }
        else // se il carattere che leggo è \n, un segno di punteggiatura etc:
        {
            fprintf(fout, "%c", carattere);
            precedente = 1;
        }
    }
    return 0;
}
int decodifica(FILE *fin, FILE *fout)
{
    return 0;
}