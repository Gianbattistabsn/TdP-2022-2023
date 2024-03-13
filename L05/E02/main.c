#include <stdio.h>
#include <string.h>
#define maxL 200 //maxLenght riga
#define maxC 30 //max ricodifiche

typedef struct {
    char parola[maxL+1];
    int codifica;
} dizionario;

int leggi_diz(FILE *diz, dizionario vettore_diz[maxC]);
void codifica(FILE *fp_in, FILE *fp_out, dizionario vettore_diz[maxC], int num_diz);

int main(void)
{
    FILE *fp_in, *fp_diz, *fp_out;

    char nome_diz[30], file_in[30], file_out[30];
    dizionario vettore_diz[maxC]; //creo un vettore di dizionari
    int num_diz;
    // Lettura fp_diz
    printf("Inserisci il nome del file contenente il dizionario:"); scanf("%s", nome_diz);
    fp_diz = fopen(nome_diz, "r");
    if (fp_diz == NULL){
        printf("\nErrore nell'apertura del file dizionario."); return 1;}
    //creazione vettore di dizionari
    num_diz = leggi_diz(fp_diz, vettore_diz); fclose(fp_diz); //leggi diz ritorna il numero effettivo di dizionari, inoltre chiudo il file
    if (num_diz == 0)
        return 2; //se il numero di dizionari letti fosse zero, non avrebbe senso continuare il programma
    // Letture file sorgente e apertura file di output
    printf("\nInserisci il nome del file sorgente:"); scanf("%s", file_in);
    fp_in = fopen(file_in, "r");
    printf("\nInserisci il nome del file di output:"); scanf("%s", file_out);
    fp_out = fopen(file_out, "w");
    //codifico il file di input e lo stampo in output
    if (fp_in != NULL && fp_out != NULL)
        codifica(fp_in, fp_out, vettore_diz, num_diz);
    else{
        printf("\nErrore nei file di input/output."); return 3;}
    fclose(fp_in); fclose(fp_out);
    return 0;
}


int leggi_diz(FILE *diz, dizionario vettore_diz[maxC])
{
    int num_diz = 0, i;
    if (fscanf(diz, "%d ", &num_diz) != 1)
        return 0;
    for (i = 0; i < num_diz; i++){
        fscanf(diz," $%d$", &vettore_diz[i].codifica);
        fscanf(diz, "%s", vettore_diz[i].parola);
        }
    return num_diz;
}


void codifica(FILE *fp_in, FILE *fp_out, dizionario vettore_diz[maxC], int num_diz)
{
    int i, j, cont, trovato;
    char riga[maxL+1];

    while(fgets(riga, maxL, fp_in) != NULL) // itero sulle righe del file
    {
        for (i = 0; i < strlen(riga); i++) //itero sulla posizione i-esima della riga
        {
            trovato = 0;
            if (riga[i] != ' ' && riga[i] != '\n')
                for (j = 0; j < num_diz; j++) // itero sui dizionari
                {
                    if (riga[i] == vettore_diz[j].parola[0])  //se la lettera della riga i-esima è uguale alla prima lettera della parola del dizionario j-esimo
                    {
                        trovato = 1;
                        for (cont = 0; cont < strlen(vettore_diz[j].parola) && trovato == 1; cont++)
                            if (riga[i + cont] != vettore_diz[j].parola[cont]) // se la parola del dizionario j-esimo non è contenuta nella parola
                                trovato = 0; // allora esco dal ciclo
                    }
                    if (trovato) { //se vale ancora trovato == 1, allora stampo la codifica al posto della parola
                        fprintf(fp_out, "$%d$", vettore_diz[j].codifica);
                        i = (int)(i + strlen(vettore_diz[j].parola) - 1); // incremento il contatore delle i delle parole che ho già stampato -1 (verrà sistemata dall'i++);
                        break;}
                }
            if (!trovato)
                fprintf(fp_out, "%c", riga[i]);
        }
    }
}


