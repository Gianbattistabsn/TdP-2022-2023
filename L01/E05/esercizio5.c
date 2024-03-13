/* Esercizio 5. Scrivere un programma “calcolatrice” che esegua le quattro operazioni aritmetiche di base
 * (addizione, sottrazione, divisione e moltiplicazione) tra due valori op1 e op2.
 * Realizzare un programma C che:
 * a) Acquisisca da tastiera utilizzando getchar l’operazione da eseguire (‘+’, ‘-‘, ‘*’ e ‘/’)
 * b) Acquisisca da tastiera utilizzando scanf i due operandi (float) (es. 21.0 2.0).
 * c) Stampi a schermo il carattere dell’operazione seguita dal risultato (es. / 10.50).
 * Approfondimento: Cosa succede quando op2 è uguale a zero?
 */
// N.B. L'approfondimento si trova alla fine del codice (circa riga 100):
#include <stdio.h>
// si sarebbe potuto evitare il buffer e i valori sentinella
// usando la libreria ctype per controllare che i valori inseriti fossero solo dei numeri.

float trova_risultato(char operazione, float op1, float op2, float result); // DICHIARO LA FUNZIONE TROVA RISULTATO
void clear_buffer(void);

int main(void)
{
    // INIZIALIZZAZIONE VARIABILI
    char operazione, buffer[2]; //inizializzo un buffer in modo da gestire eventuali errori
    float op1 = -4129421, op2 = -4129421, result = 0; // Assegno a op1 e op2 due valori "sentinella" per evitare errori.
    // Body
    printf("-----------------------\n"
           "|  Comandi:           |\n"
           "| + = Addizione       |\n"
           "| - = Sottrazione     |\n"
           "| * = Moltiplicazione |\n"
           "| / = Divisione       |\n"
           "-----------------------\n");
    printf("\nInserisci il simbolo dell'operazione da effettuare:");
    operazione = getchar();
    gets(buffer); // Prendo il buffer che prosegue da getchar(ovvero tutto ciò che segue l'operazione).
    if (buffer[0] != 0)
        /* Se il primo carattere del buffer è diverso da zero (indica \000), allora significa che
        // l'utente ha tentato di inserire, a seguito della richiesta del segno di operazione, un altro carattere.
           Di conseguenza, evito di continuare l'esecuzione del codice e genero l' errore uno. */
    {
        printf("\nErrore, operazione non valida");
        getchar();
        return 1;
    }
    if (operazione != '+' && operazione != '-' && operazione != '*' && operazione != '/')
    { //Controllo che il primo carattere inserito in input sia corretto, altrimenti genero l'errore uno.
        printf("\nErrore, operazione non valida.");
        getchar();
        return 1;
    }
    else
    {
        printf("\nInserisci il valore del primo operando:");
        scanf("%f", &op1);
        printf("\nInserisci il valore del secondo operando:");
        scanf("%f", &op2);
        if (op1 == -4129421 || op2 == -4129421) //controllo, tramite i valori sentinella definiti inizialmente
            // che entrambi gli operatori siano variati rispetto ai valori sentinella in quanto
            // tentando di assegnare loro (tramite input) dei caratteri, rimarranno invariati (-4129421)
        {
            printf("\nErrore, uno dei due operandi inseriti ha un formato non valido.");
            clear_buffer();
            getchar();
            return 2; // restituisce il codice errore 2 nel caso in cui si tenti di inserire valori non numerici.}
        }
        result = trova_risultato(operazione, op1, op2, result);
        if (result == -4129421) // solito valore sentinella nel caso di divisione per zero
        {
            clear_buffer();
            getchar();
            return 3; //restituisce il codice errore 3 in caso di divisione per zero
        }
        printf("\nLa tua operazione '%c' ha come risultato: %.2f", operazione, result);
        printf("\nPremi 'invio' per terminare l'esecuzione del programma.");
        clear_buffer();
        getchar();
        return 0;
    }
}

// DEFINISCO LA FUNZIONE 'trova_risultato' che ha bisogno dei parametri operazione, op1, op2 e risultato per funzionare.
float trova_risultato(char operazione, float op1, float op2, float risultato)
/* param operazione: definisce l'operazione che verrà svolta
 * param op1, op2: i due operandi con i quali effettuare l'operazione
 * param risultato: verrà restituito tramite return nel caso in cui non avvengano errori (ad esempio Zero Error). */
{
    switch (operazione) // uso un costrutto switch case o, equivalentemente, potrei usare una serie di if, else if, else.
    {
        case '+': {
            risultato = op1 + op2;
            break;
        }
        case '-': {
            risultato = op1 - op2;
            break;
        }
        case '*': {
            risultato = op1 * op2;
            break;
        }
        case '/':
            if (op2 != 0)  //cioè, se op2 è diverso da 0, allora effettua l'operazione
                risultato = op1 / op2;
            else // nel caso in cui l'op2 sia uguale a 0, restituisca il codice errore 2
            {
                printf("Zero Error: impossibile dividere per zero.");
                return -4129421; //restituisce un valore 'sentinella' utile per gestire gli errori.
            }
            // Non uso un default in quanto ho gestito anticipatamente il caso di operazioni diverse da + - / o *
    }
    return risultato;
}

void clear_buffer(void)
{
    while (getchar()!='\n')
        continue;
}

/* APPROFONDIMENTO:
 * RISPOSTA RAPIDA: Nel caso di un'operazione per zero, il risultato sarebbe 'inf', ecco il procedimento.
 * Nel caso in cui avessi lasciato da riga 88 a riga 95 in tal modo:
 * case '/':
    risultato = op1 / op2;
    break; (in realtà "inutile")
 * Avrei avuto il seguente output:
 * Inserisci il tipo di operazione da effettuare (+ - / *):
 * /
 * Inserisci il valore del primo operando:
 * 2
 * Inserisci il valore del secondo operando:
 * 0
 * La tua operazione '/' ha come risultato: inf
 * Process finished with exit code 0
 * Ho invece corretto il codice come precede anche per evitare un exit code 0 ma ritornando un errore visto
 * il tipo di operazione "illecita".
 * N.B.
 * Ho inoltre tentato di gestire il maggior numero di eccezioni in modo da esercitarmi in questo nuovo linguaggio.
 */