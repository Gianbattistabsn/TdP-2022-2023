#include <stdio.h>
#include <ctype.h>
int comprimi(FILE *input, FILE *output, int scritti);
int decomprimi(FILE *input, FILE *decompresso, int scritti);
int main(void)
{
    FILE *fp_input, *fp_output, *fp_decompressione;
    char scelta_1; //nome_input[20], nome_output[20];
    int scritti = 0;
    printf("%s", "Vuoi comprimere o decomprimere il file?\n'C' per comprimere, 'D' per decomprimere.\n");
    scanf("%c", &scelta_1);
    /* if (toupper(scelta_1) == 'C' || toupper(scelta_1) == 'D')
    {
        printf("Inserisci il nome del file in input:");
        scanf("%s", &nome_input);
        printf("\nInserisci il nome del file di output:");
        scanf(" %s", &nome_output);
    } */ //Nel caso in cui si volesse ricevere da tastiera il nome dei file basterebbe sostituire a "sorgente.txt", nome_input e rimuovere il commento
    if (toupper(scelta_1) == 'C') // se la scelta è uguale a 'C' o 'c'
    {
        fp_input = fopen("sorgente.txt", "r");
        fp_output = fopen("compresso.txt", "w");
        if (fp_input == NULL || fp_output == NULL)
        {
            printf("Errore nell'apertura dei file");
            return 0; // restituisco il numero dei caratteri scritti
        }
        scritti = comprimi(fp_input, fp_output, scritti); // numero dei caratteri scritti
        fclose(fp_input);
        fclose(fp_output);
    }
    else if (toupper(scelta_1) == 'D') //se la scelta è uguale a 'D' o 'd'
    {
        fp_input = fopen("compresso.txt", "r");
        fp_decompressione = fopen("decompresso.txt", "w");
        if (fp_input == NULL || fp_output == NULL)
        {
            printf("Errore nell'apertura dei file");
            return 0; // restituisco il numero dei caratteri scritti
        }
        scritti = decomprimi(fp_input, fp_decompressione, scritti); //numero dei caratteri scritti
        fclose(fp_input);
        fclose(fp_output);
    }
    else // se la scelta non dovesse essere nè C, c, D o d, allora restituisco errore e 0 (caratteri scritti)
    {
        printf("Errore nella scelta.");
        return 0; // restituisco il numero dei caratteri scritti
    }


    return scritti; // restituisco il numero dei caratteri scritti come richiesto
}
int comprimi(FILE *input, FILE *output, int scritti)
{
    int first = 1, cont = 0;
    char carattere_p, carattere_s;
    while (!feof(input)) {
        if (first) //in ogni caso, alla prima iterazione, prendo il primo carattere e lo stampo in output in quanto non può avere precedenti
        {
            fscanf(input, "%c", &carattere_p); //scansiono il primo carattere (precede tutti gli altri)
            fprintf(output, "%c", carattere_p); //lo stampo in output
            first = 0; //segnalo che first diventa falso così da non dover più entrare in questo if
            scritti++;
        }
        fscanf(input, "%c", &carattere_s); // prendo il carattere successivo
        if (!feof(input))
        {
            if (carattere_p == carattere_s) // se i due caratteri sono uguali
            {
                cont ++; //inceremento il contatore
                if (cont == 9)
                {
                    fprintf(output, "$%d", cont); //stampo per quante volte è stato letto il carattere che segue
                    cont = 0; //resetto il contatore così che possa verificare se dopo ci siano altre ripetizioni
                    carattere_p = '$'; //impostando il carattere che precede a un valore sentinella
                    scritti+=2;
                }
            }
            else // se i due caratteri non sono uguali
            {
                if (cont == 0) //se cont è zero allora significa che non lo sono mai stati e quindi stampo il carattere che segue
                {
                    fprintf(output, "%c", carattere_s); scritti++;
                }
                else if (cont == 1) //se cont è uguale a uno, significa che il carattere che precede è ripetuto una volta
                    // ma era già stato stampato una volta, quindi stampo un'altra volta il carattere che "precede" e una il carattere che segue
                {
                    fprintf(output, "%c%c", carattere_p, carattere_s); scritti+=2;
                }
                else // se cont è maggiore di uno, allora stampo quante volte è ripetuto il carattere che precede e stampo il successivo
                {
                    fprintf(output, "$%d%c", cont, carattere_s); scritti+=3;
                }
                cont = 0; // resetto il contatore
                carattere_p = carattere_s; // pongo il carattere che precede = quello che segue così da poter ricominciare il ciclo
            }
        }
        else // se sono arrivato alla fine del file e quindi carattere che segue == EOF, il carattere che precede è necessariamente
        // diverso da EOF.
        {
            if (cont > 1) // se cont è maggiore di uno, allora stampo quante volte è ripetuto il carattere che precede
                //era già stato stampato sicuramente prima del $ il carattere che precede
            {
                fprintf(output, "$%d", cont); scritti+=2;
            }
            else if (cont == 1) //se cont è uguale a uno, significa che il carattere che precede è ripetuto una volta
                // ma era già stato stampato, quindi stampo un'altra volta il carattere che "segue" che in realtà sarebbe EOF in questo momento.
            {
                fprintf(output, "%c", carattere_p); scritti++;
            }
        }
    }
    return scritti;
}
int decomprimi(FILE *input, FILE *decompresso, int scritti)
{
    int first = 1, cont = 0;
    char carattere_p, carattere_s;
    while (!feof(input)) {
        if (first) //in ogni caso, alla prima iterazione, prendo il primo carattere e lo stampo in output in quanto non può avere precedenti
        {
            fscanf(input, "%c", &carattere_p); //scansiono il primo carattere (precede tutti gli altri)
            fprintf(decompresso, "%c", carattere_p); //lo stampo in output
            scritti++;
            first = 0; //segnalo che first diventa falso così da non dover più entrare in questo if
        }
        fscanf(input, "%c", &carattere_s); // prendo il carattere successivo
        if (!feof(input))
        {

            if (carattere_s == '$') // se i due caratteri sono uguali
            {
                fscanf(input, "%c", &carattere_s);
                cont = (int)(carattere_s-'0');
                for (cont; cont > 0; cont--)
                {
                    fprintf(decompresso, "%c", carattere_p);
                    scritti ++;
                }
            }
            else // se non è uguale al dollaro, allora stampa normalmente il carattere successivo
            {
                fprintf(decompresso, "%c", carattere_s);
                carattere_p = carattere_s;
                scritti++;
            }
        }
    }
    return scritti;
}