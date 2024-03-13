#include <stdio.h>
#include <ctype.h>
#define filein "expr.txt"
void verifica_sequenza(FILE *fin);

int main()
{
    FILE *fin;
    fin = fopen(filein, "r");
    if (fin == NULL)
    {
        printf("Errore nell'apertura del file");
        return 1;
    }
    verifica_sequenza(fin);
    fclose(fin);
    return 0;
}

void verifica_sequenza(FILE *fin)
{
    int cont_exp = 1, errore_num = 0, errore_op = 0;
    char p_char, s_char, riga_intera[30];
    p_char = getc(fin); s_char = getc(fin);
    while (!feof(fin))
    {
        if (s_char == ' ')
            s_char = getc(fin);
        if(s_char == EOF)
            break;
        if (p_char == '(' && (s_char != '(' && !isdigit(s_char)))
            errore_num = 1;
        if ((p_char == ')' || isdigit(p_char)) && (s_char != ')' && s_char != '\n' && (s_char != '+' && s_char != '-' && s_char != '*' && s_char != '/')))
            errore_num = 1;
        if ((p_char == '+' || p_char == '-' || p_char == '*' || p_char == '/') && !isdigit(s_char) && s_char != '(')
            errore_op = 1;
        if (errore_num || errore_op)
        {
            printf("Errore nella riga %d\n", cont_exp);
            while (p_char != '\n')
            {
                p_char = s_char;
                s_char = getc(fin);
            }
            errore_num = 0; errore_op = 0;
            cont_exp++;
        }
        p_char = s_char;
        s_char = getc(fin);
        if (p_char == '\n')
        {
            cont_exp++;
            errore_num = 0; errore_op = 0;
        }

    }

}