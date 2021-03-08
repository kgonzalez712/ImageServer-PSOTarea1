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
int Cont_len;
int Cont_line;
char *PATHC;
char *PATHH;
char *PATHL;

int stringSearch(char s1[], char s2[])
{
    //char s1[] = "Content-Lenght: 117890";
    //char s2[] = "Content-Length:";
    char bufP[100];
    int n = 0;
    int m = 0;
    int times = 0;
    int len = strlen(s2); // contains the length of search string

    while (s1[n] != '\0')
    {

        if (s1[n] == s2[m])
        { // if first character of search string matches

            // keep on searching

            while (s1[n] == s2[m] && s1[n] != '\0')
            {
                n++;
                m++;
            }

            // if we sequence of characters matching with the length of searched string
            if (m == len && (s1[n] == ' ' || s1[n] == '\0'))
            {
                FILE *fpss;
                fpss = fopen("CLength.txt", "w");
                printf("\n");
                // BINGO!! we find our search string.
                printf("Found Content-Length! \n");
                fputs(s1, fpss);
                fclose(fpss);
            }
        }
        else
        { // if first character of search string DOES NOT match
            while (s1[n] != ' ')
            { // Skip to next word
                n++;
                if (s1[n] == '\0')
                    break;
            }
        }

        n++;
        m = 0; // reset the counter to start from first character of the search string.
    }

    return 0;
}

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

int parseRequest()
{
    FILE *fpr = fopen("Request.txt", "r");
    // ...

    char chunk[128];
    int current_line = 0;

    // Store the chunks of text into a line buffer
    size_t len = sizeof(chunk);
    char *line = malloc(len);
    if (line == NULL)
    {
        perror("Unable to allocate memory for the line buffer.");
        exit(1);
    }

    // "Empty" the string
    line[0] = '\0';
    // ...

    while (fgets(chunk, sizeof(chunk), fpr) != NULL)
    {
        current_line++;
        // Resize the line buffer if necessary
        size_t len_used = strlen(line);
        size_t chunk_used = strlen(chunk);

        if (len - len_used < chunk_used)
        {
            len *= 2;
            if ((line = realloc(line, len)) == NULL)
            {
                perror("Unable to reallocate memory for the line buffer.");
                free(line);
                exit(1);
            }
        }

        // Copy the chunk to the end of the line buffer
        strncpy(line + len_used, chunk, len - len_used);
        len_used += chunk_used;

        // Check if line contains '\n', if yes process the line of text
        if (line[len_used - 1] == '\n')
        {
            //fputs(line, stdout);
            Cont_line = current_line + 1;
            stringSearch(line, "Content-Length:");
            // "Empty" the line buffer
            line[0] = '\0';
        }
    }
    free(line);
    fclose(fpr);
}

void getContent(int line_no)
{
    char str[256];
    FILE *rfl, *rfl2;

    int cur_line = 0;

    rfl = fopen("Request.txt", "r");

    rfl2 = fopen("Content.txt", "w");
    printf("Getting the request content! \n");

    while (fgets(str, 255, rfl) != NULL)
    {
        cur_line++;
        if (cur_line >= line_no)
        {
            fputs(str, rfl2);
        }
    }
    fclose(rfl);
    fclose(rfl2);
}

void handle_connection(int sock)
{
    int n;
    char buffer[MAXLINE];

    bzero(buffer, MAXLINE);
    n = read(sock, buffer, MAXLINE - 1);
    if (n < 0)
        error("ERROR reading from socket");
    //Read the client request
    printf("%s\n", buffer);
    FILE *fphc, *fpcl, *fpc;
    fphc = fopen("Request.txt", "w+");
    fprintf(fphc, buffer);
    fclose(fphc);
    fphc = fopen("Log.txt", "a");
    fprintf(fphc, "\nRequest from Client: \n");
    fprintf(fphc, buffer);
    fclose(fphc);
    //Parsing the request
    parseRequest();
    //Getting content size
    fpcl = fopen("CLength.txt", "r");
    fscanf(fpcl, "%*s %s", bufP);
    Cont_len = atoi(bufP);
    fclose(fpcl);
    //Getting content
    getContent(Cont_line);
    //Reading the Image
    printf("Done!... Starting image Procesing... \n");
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
        printf("[+]Listening on the specified port.. \n");
        printf("\n");
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