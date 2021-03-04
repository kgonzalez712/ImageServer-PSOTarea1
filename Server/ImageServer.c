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
void handle_connection(int sock)
{
    int n;
    char buffer[MAXLINE];

    bzero(buffer, MAXLINE);
    n = read(sock, buffer, MAXLINE - 1);
    if (n < 0)
        error("ERROR reading from socket");
    //printf("Here is the message: %s\n", buffer);
    printf("%s\n", buffer);
    FILE *fp;

    fp = fopen("/home/kvn-95/Test/temp.txt", "w+");
    fprintf(fp, buffer);
    fclose(fp);

    return (0);
    n = write(sock, "I got your message", 18);
    if (n < 0)
        error("ERROR writing to socket");
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

    /*
    Sockets
    */
    int sockfd, newsockfd, pid, e;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len;
    char buffer[MAXLINE];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        error("[-]ERROR opening socket");
        exit(1);
    }
    printf("[+] Server Socket created. \n");

    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    /*
        Binding socket to specified port
    */
    e = bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (e < 0)
    {
        error("[-]ERROR in binding socket to port");
        exit(1);
    }
    printf("[+]Binding done successfully \n");

    e = listen(sockfd, 10);
    if (e == 0)
    {
        printf("[+]Listening on the specified port.. \n);
    }
    else
    {
        error("[-]ERROR while listening");
        exit(1);
    }

    cli_len = sizeof(cli_addr);
    while (1)
    {
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
        if (newsockfd < 0)
            error("ERROR on accept");
        pid = fork();
        if (pid < 0)
            error("ERROR on fork");
        if (pid == 0)
        {
            close(sockfd);
            handle_connection(newsockfd);
            exit(0);
        }
        else
            close(newsockfd);
    } /* end of while */
    close(sockfd);

    return 0;
}