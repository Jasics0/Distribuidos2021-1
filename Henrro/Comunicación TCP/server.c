#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define PORT 2222
#define MAXLINE 4096
#define TRUE 1

char *invertir(char line[]);
char *limpiar(char line[]);

int crearsocket(int *port, int type)
{
    int sockfd;
    struct sockaddr_in adr;
    int longitud;

    if ((sockfd = socket(PF_INET, type, 0)) == -1)
    {
        perror("Error: Imposible crear socket");
        exit(2);
    }
    bzero((char *)&adr, sizeof(adr));
    adr.sin_port = htons(*port);
    adr.sin_addr.s_addr = htonl(INADDR_ANY);
    adr.sin_family = PF_INET;
    if (bind(sockfd, (struct sockaddr *)&adr, sizeof(adr)) == -1)
    {
        perror("Error: bind");
        exit(3);
    }
    longitud = sizeof(adr);

    if (getsockname(sockfd, &adr, &longitud))
    {
        perror("Error: Obtencion del nombre del sock");
        exit(4);
    }

    *port = ntohs(adr.sin_port);
    return (sockfd);
}

void sigchld()
{
    pid_t pid;
    int stat;

    pid = wait(&stat);
    fprintf(stderr, "Proceso hijo: %d terminado\n", pid);
    return;
}

int main(int argc, char *argv[])
{
    int sock_escucha, sock_servicio;
    struct sockaddr_in adr;
    int lgadr = sizeof(adr);
    int port = PORT;
    if (argc != 2)
    {
        fprintf(stderr, "Uso %s [port]\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[1]);

    if ((sock_escucha = crearsocket(&port, SOCK_STREAM)) == -1)
    {
        fprintf(stderr, "Error: No se pudo crear/conectar socket\n");
        exit(2);
    }

    signal(SIGCHLD, sigchld);

    listen(sock_escucha, 1024);

    fprintf(stdout, "Inicio servidor en el puerto %d\n", port);
    while (TRUE)
    {
        lgadr = sizeof(adr);
        sock_servicio = accept(sock_escucha, &adr, &lgadr);
        fprintf(stdout, "Servicio aceptado.\n");

        if (fork() == 0)
        {
            close(sock_escucha);

            servicio(sock_servicio);

            exit(0);
        }
    }
}

servicio(int sock)
{
    ssize_t n;
    char line[MAXLINE];
    limpiar(line);
    for (;;)
    {
        if ((n = read(sock, line, MAXLINE)) <= 0)
        {
            return;
        }
        printf(line);
        write(sock, invertir(line), n);
        limpiar(line);
    }
}

char reverseString(char line[])
{
    int l = strlen(line);
    char aux;
    int j = l - 1;
    for (int i = 0; i < l / 2; i++)
    {
        aux = line[i];
        line[i] = line[j];
        line[j] = aux;
    }

    return line;
}

char *invertir(char line[])
{
    int l = strlen(line);
    char aux;
    for (int i = 0, j = l - 1; i < (l / 2); i++, j--)
    {
        aux = line[i];
        line[i] = line[j];
        line[j] = aux;
    }
    return line;
}

char *limpiar(char line[])
{
    line = "";
    return line;
}
