#include <stdio.h>

int main(void)
{
   FILE *fp_read, *fp_write; // definisco i file che saranno puntati ad una certa cella di memoria
   char file_char, choice; //definisco due char (file char conterrà i singoli caratteri mentre choice sarà quella da tastiera
   fp_read = fopen("C:\\Users\\gianb\\Desktop\\Uni\\TdP\\Laboratori\\Lab01\\ese2\\Guide.txt", "r"); //apro il file Guido
   fp_write = fopen("C:\\Users\\gianb\\Desktop\\Uni\\TdP\\Laboratori\\Lab01\\ese2\\Output.txt", "w"); //apro il file in scrittura
   if (fp_read == NULL) //se il file di lettura da errore
   {
       printf("Errore nell'apertura del file\n");
       return 1;
   }
   if (fp_write == NULL) //se il file di scrittura è "vuoto"
   {
       printf("Errore nell'apertura del file\n");
       return 2;
   }

   printf("Scegli se scrivere su console (C) o su file (F): ");
   choice = getchar(); //getchar mi fa leggere un solo carattere e si usa da console (getc da file)
   while (!feof(fp_read)) //while not function end of file
   // cioè fin quando non arrivo alla fine del file
       {
       file_char = fgetc(fp_read); //carattere = filegetchar(file)

       {
           switch(choice) // diciamo un if, elif, else
           {
               case 'C':
                   printf("\nChar printed on the console: %c", file_char);
                   break;
               case 'F':
                   fputc(file_char, fp_write);
                   printf("\nChar saved on file: %c", file_char);
                   // putchar(file_char); metterei il carattere dopo i :
                   break;
               default: // qualunque altra scelta:
                   printf("Wrong choice\n");
                   return 3;
           }
       }
   }
   fclose(fp_read); // chiudo i file
   fclose(fp_write);
   return 0;
}