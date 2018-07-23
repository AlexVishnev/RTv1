#include <stdio.h>
#include <stdlib.h>

/* Fucking converter file into string
 * Dirty unsave code
 * Fuck youserlf, motherfacker!
 */
void read_file(char **file_str)
{
    FILE *f = fopen("textfile.txt", "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);

    char *fucking_tmp;
    fucking_tmp = malloc(fsize + 1);
    fread(fucking_tmp, fsize, 1, f);
    fclose(f);

    fucking_tmp[fsize] = 0;

    printf("File: \n%s", fucking_tmp);
    *file_str = fucking_tmp; 
}

/* Ebbaniy stud a ne main */
void main(void)
{
    char *file_str;
    read_file(&file_str);
    printf("Will fuck your Mom!\n%s", file_str);
}