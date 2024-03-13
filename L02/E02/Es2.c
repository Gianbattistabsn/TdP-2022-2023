#include <stdio.h>
int main(void)
{
    int N,i;
    unsigned long long successivo,x_0 = 0, x_1 = 1, x_2 = 2;
    printf("Inserisci quante cifre della serie di Fibonacci vuoi vedere:\n");
    scanf("%d", &N);
    if (N>=2)
    {
        printf("0 1 ");
        for (i = 0; i < N; i++) {
            successivo = x_0 + x_1;
            x_0 = x_1;
            x_1 = successivo;
            printf("%llu ", successivo);
        }
        printf("\n0 1 1 "); x_1 = 1;
        for (i=0; i< N; i++)
        {
            successivo = (unsigned long long int)(x_1*x_2); // intero = 0 1 2 4 8 32 256 8192 2097152
            x_1 = x_2;
            x_2 = successivo;
            printf("%llu ", successivo);
        }
    }
    else if (N == 1)
        printf("0");
    else
    {
        printf("Errore, riavvia il programma e inserisci un altro numero\n");
        return 1;
    }
    return 0;
}