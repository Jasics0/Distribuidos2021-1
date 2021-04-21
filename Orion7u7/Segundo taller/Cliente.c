#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define SIZE 256
#define MAXLINE 4096

void str_echo(FILE *fp, int sock);

int main(int argc, char *argv[])
{
    int sock;
    char com[SIZE];
    struct sockaddr_in adr;
    struct hostent *hp, *gethostbyname();

    if(argc !=3)
    {
        fprintf(stderr, "Uso: %s <host> <port>\n", argv[0]);
        exit(1);
    }
}