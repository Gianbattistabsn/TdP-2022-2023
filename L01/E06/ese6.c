// ESERCIZIO 6
/*Partendo dal codice dell’esercizio precedente, scrivere un programma C che legga da file
 * una serie di operazione da eseguire e scriva su un altro file l’operazione eseguita ed il
 * risultato dell’operazione con due cifre decimali.
 */

// Esempio di dati utilizzati: (Ho voluto aggiungere un'operazione 'sbagliata' e una divisione per zero in modo da gestire gli errori di queste ultime.
// + 15.225 30.51
// - 42.1 10.01
// * 0.62 2.4
// / 5.0 2.5
// x 2.0 3.0
// / 100.0 0.0
// Tento di utilizzare un'approccio di lettura parola per parola tramite fscanf().
// quindi operazione sarà data dal primo carattere, op1 dalla prima "stringa" che va castata e op2 dalla seconda.
#include <stdio.h>

float trova_risultato(char operazione, float op1, float op2, float risultato, int riga); // DICHIARO LA FUNZIONE TROVA RISULTATO USATA PRECEDENTEMENTE

int main(void)
{
    // DICHIRAZIONE VARIABILI
    FILE *f_input, *f_output;
    char operazione;
    int riga = 1;
    float op1, op2, risultato = 0;
    //ASSEGNAZIONE VARIABILI
    // Apro il file con le operazioni dalla directory dove è salvato in lettura
    f_input = fopen("Operazioni.txt", "r");
    // Apro il file di output in scrittura
    f_output = fopen("Output.txt", "w");
    // Il file Output non era ancora stato da me creato, ho "scoperto" che, come in Python, viene creato in automatico nel caso in cui prima non esistesse.

    // GESTIONE ERRORI FILE:
    if (f_input == NULL)
    {
        printf("Errore nell'apertura del file di input");
        return 1;
    }
    if (f_output == NULL)
    {
        printf("Errore nell'apertura del file di output");
        return 2;
    }
    // SVOLGIMENTO
    printf("\n%s", "Benvenuto nella calcolatrice");
    printf("\nHo trascitto i seguenti risultati nel file di output:");
    while (!feof(f_input)) // Corrisponde a un while not (funzione end of file(file di input))
        // cioè il ciclo while va avanti fin quando non si arriva alla fine del file di input.
    {
        if (!feof(f_input))
        {
            fscanf(f_input, "%c", &operazione); //scansiono il primo carattere e lo assegno alla variabile operazione tramite puntatore
            fscanf(f_input, "%f", &op1); // scansiono il primo float e lo assegno al primo operando
            fscanf(f_input, "%f", &op2); // scansiono il secondo float e lo assegno al secondo operando
            getc(f_input); // leggo il '\n' in modo da proseguire nella lettura fino alla fine del file (-1):
            risultato = trova_risultato(operazione, op1, op2, risultato, riga);
            if (risultato != 101010)
            {
                printf("\n\n%c %f %f", operazione, op1, op2); // Volevo verificare che il file di input venisse letto correttamente quindi stampo il file di input a schermo
                fprintf(f_output, "%d) %c %.2f\n", riga, operazione, risultato); //
            }
            else
                fprintf(f_output, "%d) Errore.\n", riga);
            riga ++; //incremento la riga (mi serve solo per gestire un'eccezione (nel caso di segno errato nel file di input segnalo anche la riga).
        }
    }
    fclose(f_input); // chiusura dei file di input
    fclose(f_output); // e output
    printf("\nPremi invio per terminare l'esecuzione del programma: ");
    getchar(); // in modo che dal .exe non si chiuda immediatamente

    return 0;
}

float trova_risultato(char operazione, float op1, float op2, float risultato, int riga)
/* param operazione: definisce l'operazione che verrà svolta
 * param op1, op2: i due operandi con i quali effettuare l'operazione
 * param risultato: verrà restituito tramite return nel caso in cui non avvengano errori (ad esempio Zero Error). */
{
    risultato = 0;
    switch(operazione) // uso un costrutto switch case o, equivalentemente, potrei usare una serie di if, else if, else.
    {
        case '+':
        {
            risultato = op1 + op2;
            break;
        }
        case '-':
        {
            risultato = op1 - op2;
            break;
        }
        case '*':
        {
            risultato = op1 * op2;
            break;
        }
        case '/':
        {
            if (op2 != 0)  //cioè, se op2 è diverso da 0, allora effettua l'operazione
                risultato = op1 / op2;
            else // nel caso in cui l'op2 sia uguale a 0, restituisca il codice errore 2
            {
                printf("\n\nZero Error: impossibile dividere per zero alla riga n^%d.", riga);
                return 101010; // restituisco il valore 101010 nel caso di errori.
            }
            break;
        }
            // NOTA: Al contrario dell'esercizio precedente, qui mi serve un default (in quanto non ho gestito gli errori delle operazioni)
        default:
        {
            printf("\n\nErrore, l'operazione alla riga n^%d non e' supportata.", riga);
            return 101010; // restituisco il valore 101010 nel caso di errori.
        }

    }
    return risultato;
}