#include <stdio.h>
#include <unistd.h>
int main(int argc, char **argv)
{
    int p1, p2, p3, p4, p5;

    p1 = fork();
    p2 = fork();

    if (p1 == 0 && p2 != 0)
    {
        p3 = fork();
    }
    while (1);
}