#include <time.h>
#include <stdio.h>

#include "log.h"

void save_in_log(char msg[], char status[]){
    // Open CSV file
    FILE *arq;
    arq = fopen("./dados.csv", "r+");
    if (arq)
    {
        // If exists go to end
        fseek(arq, 0, SEEK_END);
    }
    else
    {
        // Oppen in append mode
        arq = fopen("./dados.csv", "a");

        // header
        fprintf(arq, "Command, Status, Data\n");
    }

    if (arq)
    {
        time_t rawtime;
        struct tm *timeinfo;

        time(&rawtime);
        timeinfo = localtime(&rawtime);

        fprintf(arq, "%s, %s, %s", msg, status, asctime(timeinfo));
    }
    // else
    // {
    //     printf("Nao foi possivel criar/abrir o arquivo em modo escrita. Permissoes?\n");
    //     exit(-1);
    // }

    // close CSV file
    fclose(arq);
}