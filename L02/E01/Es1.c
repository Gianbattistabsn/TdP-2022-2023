#include <stdio.h>
#include <ctype.h>

int main(void)
{
    //Dichiarazione variabili
    int opMax, opMin, op1 = -1, op2 = -1, resto = 1, first = 1, passo = 1;
    //body
    printf("Inserisci i numeri di cui vuoi sapere il MCD (es: 32 18):\n");
    scanf("%d %d", &op1, &op2);
    if (op1 != -1 && op2 != -1) //-1 è un valore 'sentinella'; nel caso in cui si tenti di inserire una lettera, si entrerebbe
        // nell'else e si darebbe errore
    {
        if (op1 == 1 || op2 == 1) // evito di fare iterazioni inutili nel caso in cui uno dei due valori sia 1, il MCD è sempre 1
            printf("Il massimo comun divisore tra %d e %d e': 1", op1, op2);
        else if (op1 == op2) // Se dovessero essere uguali, allora il MCD è il numero stesso
            printf("Il massimo comun divisore tra %d e %d e': %d", op1, op2, op1);
        else if (op1 != 0 && op2 !=0) //Nel caso in cui siano entrambi diversi tra loro, da zero e da uno allora inizio a iterare seguendo l'algoritmo proposto
        {
            while (resto != 0)  //fin quando il resto è diverso da 0 si va avanti con il ciclo
            {
                if (first) // se è la prima volta che viene eseguito il ciclo
                {
                    if (op1 < 0 || op2 < 0)  // se uno dei due valori risulta essere negativo
                    {
                        printf("Errore, inserisci solo valori positivi"); // allora restituisco errore
                        return 1;
                    }
                    if (op1 < op2) // imposto i valori massimi
                    {
                        opMax = op2;
                        opMin = op1;
                        first = 0; // non faccio ripetere il ciclo
                    }
                    else
                    {
                        opMax = op1;
                        opMin = op2;
                        first = 0;
                    }
                }
                resto = opMax % opMin; //calcolo il resto tra opMax e opMin
                printf("%d) %d %% %d = %d\n", passo, opMax, opMin, resto); // Opzionale, stampo il passaggio effettuato
                passo++; //OPZIONALE, incremento il numero di passaggi necessari per ottenere il MCD
                if (resto != 0) //se il resto è diverso da zero, allora
                {
                    opMax = opMin; //imposto il valore massimo al valore minimo e il minimo al resto
                    opMin = resto; //opMin nella penultima iterazione del ciclo assumerà il valore di MCD, in quanto nella successiva sarebbe zero
                }
            }
            printf("Il massimo comun divisore tra %d e %d e' il numero: %d", op1, op2, opMin);
        }
        else // se uno dei due valori inseriti risulta essere zero o non valido
        {
            printf("Errore, impossibile valutare il massimo comune divisore tra i numeri da te inseriti.");
            return 1;
        }
    }
    else //nel caso in cui op1 o op2 siano uguali al valore sentinella -1
    {
        printf("Errore, non riconosco uno dei due numeri"); //restituisco l'errore
        return 1;
    }
    return 0;
}