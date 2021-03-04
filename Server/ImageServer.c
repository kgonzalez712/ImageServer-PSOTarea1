/* 
    Included Libraries used for the server
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
    Defined Variables used
*/
#define MAXLINE 4096
char bufP[100];
char bufC[100];
char bufH[100];
char bufL[100];
int PORT;
char *PATHC;
char *PATHH;
char *PATHL;

void LoadConfig()
{
    FILE *ptr = fopen("config.conf", "r");
    if (ptr == NULL)
    {
        printf("no such file.");
    }

    fscanf(ptr, "%*s %s", bufP);
    PORT = atoi(bufP);
    fscanf(ptr, "%*s %s", bufC);
    PATHC = bufC;
    fscanf(ptr, "%*s %s", bufH);
    PATHH = bufH;
    fscanf(ptr, "%*s %s", bufL);
    PATHL = bufL;

    fclose(ptr);
}
int main()
{
    //Loading the Configuration File
    printf("Loading Configuration File... \n");
    printf(". \n");
    printf(".. \n");
    LoadConfig();
    printf("... \n");
    printf("Server Port: %d\n", PORT);
    printf("Dominant Color Path: %s\n", PATHC);
    printf("Histogram Path: %s\n", PATHH);
    printf("Log File Path: %s\n", PATHL);

    printf("Configuration File Ready! \n");

    return 0;
}