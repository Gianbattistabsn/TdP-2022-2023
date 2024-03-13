
#include <stdio.h>
int main() {
    FILE *fp_read, *fp_write_odd, *fp_write_even;
    char file_string[100], name[20];
    int counter = 0;
    fp_read = fopen("C:\\Users\\gianb\\Desktop\\UNI\\TdP\\Laboratori\\Lab01\\ese3\\Bronte.txt", "r");
    fp_write_odd = fopen("C:\\Users\\gianb\\Desktop\\UNI\\TdP\\Laboratori\\Lab01\\ese3\\Output_odd.txt", "w");
    fp_write_even = fopen("C:\\Users\\gianb\\Desktop\\UNI\\TdP\\Laboratori\\Lab01\\ese3\\Output_even.txt", "w");

    if (fp_read == NULL) {
        printf("Error opening file\n");
        return 1;
    }
    if (fp_write_odd == NULL) {
        printf("Error opening file\n");
        return 2;
    }
    if (fp_write_even == NULL) {
        printf("Error opening file\n");
        return 3;
    }
    printf("What's your name?");
    gets(name);  //getstring, andrebbe bene anche scanf("%s", &name)
    while (!feof(fp_read)) {
        counter++; //incremento il contatore ogni riga (al primo è dispari)
        if (counter%2==0) {
            fscanf(fp_read, "%s", file_string); // scansiono il file di lettura come stringa e lo metto in file_string
            // fscanf SCANSIONA PAROLA PER PAROLA, non riga per riga!!
            if (!feof(fp_read)) {
                printf("%s\nI am reading:\n%s\n\n", name, file_string);
                fprintf(fp_write_even, "%s\n", file_string);
            }
        }
        else {
            fgets(file_string, 100, fp_read); //filegetstring(lo metti in file_string), massimo 100, dal file fp_read)
            if (!feof(fp_read)) {
                puts(name); //
                puts("I am reading:");
                puts(file_string);
                fputs(file_string, fp_write_odd);
                //fileputstring(cosa ci metto, dove)
            }
        }
    }
    fclose(fp_read);
    fclose(fp_write_even);
    fclose(fp_write_odd);
    return 0;
}
