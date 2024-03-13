#include <stdio.h>
#include <string.h>
#define max_file_lengt 1000 //il massimo di righe del file
#define max_str_lenght 31 //il massimo di caratteri di ogni parola (30 + '\0')

typedef struct {
    char codice_tratta[max_str_lenght], partenza[max_str_lenght], destinazione[max_str_lenght];
    int anno, mese, giorno, ora_p, min_p, sec_p, ora_a, min_a, sec_a, ritardo;
} log;

typedef enum{r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_exit} comando_e;
//DICHIARAZIONE FUNZIONI
int leggi_file(FILE *fp_in, log vettore[max_file_lengt]);
void stampa_riga_log(log riga_vettore);
int leggiComando();
void menuParola(comando_e input, log vettore[max_file_lengt], int nr);
void controlla_stazione(char useful[max_file_lengt],log vettore[max_file_lengt], int nr, int p_or_d);
void controlla_ritardo(log vettore[max_file_lengt], int nr), controlla_r_tot(log vettore[max_file_lengt], int nr);
void controlla_data(log vettore[max_file_lengt], int nr);

int main(void)
{
    // DEFINIZIONE VARIABILI
    comando_e input = r_date;
    int num_righe = 0; //numero righe del file
    FILE *fp_in = NULL;
    log vettore[max_file_lengt];
    //BODY
    num_righe = leggi_file(fp_in, vettore); //tramite la funzione 'leggi_file', riempio il vettore di struct e ritorno il numero di righe
    fclose(fp_in);
    if(!num_righe) return num_righe; // in caso di errori termino l'esecuzione del programma
    // GESTIONE INPUT UTENTE
    while (input != r_exit && input != r_fine)
    {
        input = leggiComando(); //richiedo l'input nella funzione leggi_comando
        menuParola(input, vettore, num_righe); printf("\n"); // passo l'input alla funzione 'menuParola' che smisterà poi l'input ad altre funzioni
        if (input == r_exit) // se dovessero verificarsi errori con l'input:
            return r_exit;
    }
    return 0;
}


int leggi_file(FILE *fp_in, log v[max_file_lengt])
{
    char file_name[max_str_lenght];
    int num_righe, i = 0;
    //acquisizione nome file e controlli su righe
    printf("Inserire il nome del file di input: "); scanf("%s", file_name);
    if ((fp_in = fopen(file_name, "r")) == NULL){
        printf("\nErrore nell'apertura del file."); return 0;}
    fscanf(fp_in, "%d", &num_righe);
    //Stampo il file e riempio il vettore di struct con tutte le informazioni utili
    while (i < num_righe && fscanf(fp_in, "%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", v[i].codice_tratta, v[i].partenza, v[i].destinazione,
                                   &v[i].anno, &v[i].mese, &v[i].giorno, &v[i].ora_p, &v[i].min_p, &v[i].sec_p, &v[i].ora_a, &v[i].min_a, &v[i].sec_a, &v[i].ritardo) == 13){
        stampa_riga_log(v[i]);
        i++;}
    printf("\n");
    return num_righe; // ritorno al main il numero di righe che serviranno in altre funzioni
}

void stampa_riga_log(log riga_vettore) // Funzione utile per stampare una riga del vettore di struct che risponde a un certo pattern
{
    printf("\n%s %s %s %d/%d/%d %d:%d:%d %d:%d:%d %d", riga_vettore.codice_tratta, riga_vettore.partenza, riga_vettore.destinazione,
           riga_vettore.anno, riga_vettore.mese, riga_vettore.giorno, riga_vettore.ora_p, riga_vettore.min_p, riga_vettore.sec_p,
           riga_vettore.ora_a, riga_vettore.min_a, riga_vettore.sec_a, riga_vettore.ritardo);
}

int leggiComando()
{
    comando_e comando = 0;
    char cmd[max_str_lenght], words[r_exit][max_str_lenght] = {"date", "partenza", "capolinea", "ritardo", "ritardo_tot", "fine"};
    int trovato = 0;
    //ACQUISIZIONE COMANDO DA EFFETTUARE
    printf("\nInserire un comando tra \"date\", \"partenza\", \"capolinea\", \"ritardo\", \"ritardo_tot\" e \"fine\": ");
    scanf("%s", cmd); //acquisisco il comando
    while (comando < r_exit && !trovato) //controllo che il comando sia presente nella lista di parole WORDS
    {
        if (!strcmp(words[comando], cmd))
            trovato = 1;
        else
            comando ++;
    }
    return comando; //restituisco direttamente il numero del comando corrispondente
}


void menuParola(comando_e input, log vettore[max_file_lengt], int nr)
{
    char useful[max_str_lenght];
    switch(input)
    {
        case r_date: // elenca tutte le corse partite in un certo intervallo di date che verranno richieste nella funzione
        {controlla_data(vettore, nr);
            break;}
        case r_partenza:         // Per partenze e capolinea uso una sola funzione che ha bisogno del nome della stazione e di una variabile
        {
            printf("\nInserisci il nome della fermata di partenza da verificare:"); scanf("%s", useful);
            controlla_stazione(useful, vettore, nr, 0);
            break;
        }
        case r_capolinea:
        {
            printf("\nInserisci il nome della fermata capolinea da verificare:"); scanf("%s", useful);
            controlla_stazione(useful, vettore, nr, 1);
            break;
        }
        case r_ritardo:
        {controlla_ritardo(vettore, nr);
            break;}
        case r_ritardo_tot:
        {controlla_r_tot(vettore, nr);
            break;}
        case r_fine:{ //termina l'esecuzione del programma
            printf("\nArrivederci!"); break;}
        case r_exit: //in caso di errori:
            printf("\nErrore con l'acquisizione del comando");
    }
}

void controlla_r_tot(log vettore[max_file_lengt], int nr)
{
    char codice[max_str_lenght];
    int i = 0, ritardo_tot = 0;
    printf("Inserisci il codice tratta (GTTxxx): "); scanf("%s", codice);
    while (i < nr)
    {
        if(vettore[i].ritardo != 0 && !strcasecmp(vettore[i].codice_tratta, codice))
            ritardo_tot += vettore[i].ritardo;
        i++;
    }
    if (ritardo_tot > 0)
        printf("La corsa %s ha presentato un ritardo complessivo di %d minuti", codice, ritardo_tot);
    else
        printf("La corsa %s non ha mai presentato ritardo o non è presente nel database", codice);
}

void controlla_stazione(char useful[max_str_lenght], log vettore[max_file_lengt], int nr, int p_or_d)
/* Questa funzione controlla la stazione di partenza (p_or_d = 0) o la stazione di arrivo (p_or_d)=1
 * Quindi confronta la parola useful con le partenze o le destinazioni del vettore di struct */
{
    int i = 0, trovato = 0;
    while (i < nr)
    {
        if (!p_or_d &&!strcasecmp(vettore[i].partenza, useful)){
            stampa_riga_log(vettore[i]), trovato = 1;}
        else if (p_or_d && !strcasecmp(vettore[i].destinazione, useful)){
            stampa_riga_log(vettore[i]); trovato = 1;}
        i++;
    }
    if (!trovato)
        printf("\nNon ho trovato alcuna fermata chiamata '%s', riprova.", useful);
}

void controlla_data(log vettore[max_file_lengt], int nr)
{
    int vettore_date_inizio[3], vettore_date_fine[4], i=0, trovato = 0, inizio, fine, attuale;
    // Acquisizione intervalli di inizio e fine corsa
    printf("Inserisci la data di inizio (anno/mese/giorno):"); scanf("%d/%d/%d", &vettore_date_inizio[0], &vettore_date_inizio[1], &vettore_date_inizio[2]);
    printf("Inserisci la data di fine (anno/mese/giorno):"); scanf("%d/%d/%d", &vettore_date_fine[0], &vettore_date_fine[1], &vettore_date_fine[2]);
    //Definisco un metodo per verificare se una sta tra un'altra o meno; tecnicamente sarebbe più corretto usare strcmp e valutare delle intere stringhe
    //
    inizio = vettore_date_inizio[0] * 10000 + vettore_date_inizio[1]*100 + vettore_date_inizio[2];
    fine = vettore_date_fine[0] * 10000 + vettore_date_fine[1]*100 + vettore_date_fine[2];
    printf("\nScansiono le corse nell'intervallo di date da te indicato:\n");
    while(i < nr) //verifica degli intervalli di inizio e fine corsa con l'iesima struct presente nel vettore
    {
        attuale = vettore[i].anno * 10000 + vettore[i].mese *100 + vettore[i].giorno;
        if (attuale >= inizio && attuale <= fine)
        {trovato = 1; stampa_riga_log(vettore[i]);}
        i++;
    }
    if (!trovato)
        printf("Non ho trovato corse partite nelle date comprese tra %d/%d/%d e %d/%d/%d", vettore_date_inizio[0],
               vettore_date_inizio[1], vettore_date_inizio[2], vettore_date_fine[0], vettore_date_fine[1], vettore_date_fine[2]);
}
// Una funzione molto simile a 'controlla data' ma con il controllo ulteriore sui ritardi
void controlla_ritardo(log vettore[max_file_lengt], int nr)
{
    int vettore_date_inizio[3], vettore_date_fine[3], i=0, trovato = 0, inizio, fine, attuale;
    printf("Inserisci la data di inizio (anno/mese/giorno):"); scanf("%d/%d/%d", &vettore_date_inizio[0], &vettore_date_inizio[1], &vettore_date_inizio[2]);
    printf("Inserisci la data di fine (anno/mese/giorno):"); scanf("%d/%d/%d", &vettore_date_fine[0], &vettore_date_fine[1], &vettore_date_fine[2]);
    inizio = vettore_date_inizio[0] * 10000 + vettore_date_inizio[1]*100 + vettore_date_inizio[2];
    fine = vettore_date_fine[0] * 10000 + vettore_date_fine[1]*100 + vettore_date_fine[2];
    printf("\nScansiono le corse che hanno presentato ritardo nell'intervallo di date da te indicato:\n");
    while(i < nr)
    {
        if (vettore[i].ritardo > 0) // se il ritardo è uguale a zero non ha senso effettuare altri controlli.
        {
            attuale = vettore[i].anno * 10000 + vettore[i].mese *100 + vettore[i].giorno;
            if (attuale >= inizio && attuale <= fine)
            {trovato = 1; stampa_riga_log(vettore[i]);}
        }
        i++;
    }
    if (!trovato)
        printf("Non ho trovato ritardi nelle date comprese tra %d/%d/%d e %d/%d/%d", vettore_date_inizio[0],
               vettore_date_inizio[1], vettore_date_inizio[2], vettore_date_fine[0], vettore_date_fine[1], vettore_date_fine[2]);
}