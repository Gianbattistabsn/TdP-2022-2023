#include <stdio.h>
#include <math.h>
#define maxN 30

void ruota(int v[maxN], int N, int P, int dir);

int main(void)
{
    // V è il vettore, P la posizione da cui far ruotare, dir la direzione, N la lunghezza del vettore.
    int V[maxN], P = -1, dir = 0, N = 0, cont = 1;
    printf("Inserisci il numero di interi che vuoi inserire nel vettore: ");
    if (scanf("%d", &N) != 1){
        printf("\nErrore nell'acquisizione."); return 1;}
    if (N <= maxN)
        while (cont <= N)
        {
            printf("\nintero n^ %d:", cont);
            if (scanf("%d", &V[cont-1]) == 1) // lo assegno a cont-1 ma stampo cont così che si veda quale numero sto inserendo
                cont++;
            else{
                printf("Errore nell'acquisizione dell'intero numero %d", cont); return 2;}
        }
    else{
        printf("\nErrore: puoi inserire al massimo %d interi", maxN); return 3;}

    while(P != 0)
    {
        printf("\nInserisci il numero della posizione da cui vuoi far ruotare il vettore (P=0) per terminare:"); scanf(" %d", &P);
        if (P > N)
            P = P%N;
        if (P!= 0)
        {
            printf("\nInserisci la direzione (-1 per ruotare a destra, 1 per ruotare a sinistra):"); scanf(" %d", &dir);
            ruota(V, N, P, dir);
        }
        else
            printf("Termino l'esecuzione del programma, arrivederci!");
    }
    return 0;
}

void ruota(int V[], int N, int P, int dir)
{
    int V_ris[N], cont, posizione;
    if(dir == -1) // se devo spostare verso destra
    {
        for (cont = 0; cont < N; cont ++)
        {
            if ((cont+P) < N) //se, spostandolo, non 'sforo' verso destra
                posizione = cont + P; //allora sposto la posizione di P caselle più avanti verso dx
            else // se sforo le N-1 posizioni verso destra
                posizione = (cont+P)%N; //il resto della divisione intera tra la somma della posizione + l'offset mi restituisce la posizione
            V_ris[posizione] = V[cont];
        }
    }
    else if(dir == 1) // se devo spostare verso sinistra
    {
        for (cont = N-1; cont >= 0; cont--)
        {
            if (cont - P >= 0) // se non sforo verso sinistra
                posizione = cont-P; //sposto la posizione di P caselle più a sinistra
            else //altrimenti, se vado troppo a sinistra, significa che devo andare a riempire le posizioni rimanenti a partire da sx verso destra
                posizione = abs(N + cont - P);
            V_ris[posizione] = V[cont];
        }
    }
    else
        printf("\nErrore nella direzione, il vettore restera' invariato"); // gestisco qui l'errore della direzione
    if (dir == 1 || dir == -1)
    {
        printf("\nIl vettore risultante e':\n[ ");
        for(cont =0; cont < N; cont++)
        {
            printf("%d ", V_ris[cont]);
            V[cont] = V_ris[cont]; // così al main ritorna il vettore risultante.
        }
        printf("]");
    }
}