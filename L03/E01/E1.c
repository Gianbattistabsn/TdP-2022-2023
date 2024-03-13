#include <stdio.h>
#include <ctype.h>
#define filein "input.txt"
#define fileout "testo.txt"

void elaborazione_testo(FILE *fp_in, FILE * fp_out, int MAXC);

int main(void)
{
    FILE *fp_in, *fp_out;
    int MAXC = 25;

    fp_in = fopen(filein, "r");
    fp_out = fopen(fileout, "w");
    if (fp_in == NULL)
    {
        printf("Errore nell'apertura del file di input"); return 1;
    }
    if (fp_out == NULL)
    {
        printf("Errore nell'apertura del file di output"); return 1;
    }
    elaborazione_testo(fp_in, fp_out, MAXC);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}

void elaborazione_testo(FILE *fp_in, FILE * fp_out, int MAXC)
{
    int caratteri_letti = 0, caratteri_scritti = 0, maiusc_flag = 0;
    char char_p, char_s; //char che precede, char che segue
    fscanf(fp_in, "%c", &char_p);
    fscanf(fp_in, "%c", &char_s);
    while (!feof(fp_in)) //fin quando char_s != EOF
    {
        if (caratteri_scritti < MAXC) // se i caratteri che ho scritto sono < 25
        {
            if (isdigit(char_p)) // se il carattere è un numero
                fprintf(fp_out, "%c", '*'); // lo sostituisco con *
            else if (ispunct(char_p)) // se è un segno di interpunzione, stampo il segno
            {
                fprintf(fp_out, "%c", char_p);
                if (!isspace(char_s)) // e se il segno non è seguito da spazio, stampo lo spazio
                {
                    fprintf(fp_out, "%c", ' ');
                    caratteri_scritti++; //incremento i caratteri scritti in quanto 'non farebbe parte' del testo originale
                }
                if (char_p == '!' || char_p == '?' || char_p == '.') // se inoltre, successivamente dovrà essere stampato un carattere maiuscolo
                    maiusc_flag = 1;
            }
            else if (isalpha(char_p) && maiusc_flag) //se il carattere è una lettera e il flag del maiuscolo è vero
            {
                fprintf(fp_out, "%c", toupper(char_p));
                maiusc_flag = 0;
            }
            else if (char_p == '\n' || char_p == EOF)
            {
                while (caratteri_scritti < MAXC)
                {
                    fprintf(fp_out, "%c", ' ');
                    caratteri_scritti++;
                }
                fprintf(fp_out, "| c: %d\n", caratteri_letti);
                caratteri_letti = -1; //imposto caratteri letti e scritti pari a -1 così che, quando andrò a capo, saranno 0.
                caratteri_scritti = -1;
            }
            else // se è un carattere 'standard'
                fprintf(fp_out, "%c", char_p);

            char_p = char_s;
            fscanf(fp_in, "%c", &char_s);
            caratteri_letti++; //incremento il numero di caratteri scritti e letti in quanto, per ogni iterazione, sicuramente
            caratteri_scritti++; // stampo e leggo almeno un carattere  (o reimposto a zero nel caso di un \n).
        }
        else if (caratteri_scritti == MAXC) // se i caratteri che ho scritto sono uguali a 25
        {
            fprintf(fp_out, "| c: %d\n", caratteri_letti); //stampo il numero effettivo dei caratteri letti dal testo
            caratteri_letti = 0;
            caratteri_scritti =0;
        }
        if (feof(fp_in)) // se arrivo alla fine del file
        {
            while (caratteri_scritti < MAXC) // se dovessero mancare spazi ai '25' caratteri stampati
            {
                fprintf(fp_out, "%c", ' '); // allora stampo tanti spazi quanti ne servono
                caratteri_scritti++;
            }
            fprintf(fp_out, "| c: %d\n", caratteri_letti); // stampo il numero dei caratteri originali del testo
        }
    }
}