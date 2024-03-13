//
// Created by gianbattista on 03/03/2023.
//
#include <stdio.h>
int main(void)
{
    int x, y; /* Se uso 0.9 e lo assegno ad x mi assegna 0.0 perchè lo avevo dichiarato come intero quindi lo tronca */
    float z;

    printf("Inserisci un numero intero: ");
    scanf("%d", &x); //scansiono un intero che punti a x
    y = 3;
    printf("%f\n",(float)x);
    z = (float) (x)/y;
    printf("%d/%d = %.3f\n", x,y,z);
    return 0;
}
