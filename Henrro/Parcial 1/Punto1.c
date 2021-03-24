#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int p1, p2, p3, p4, p5;
    p1 = fork();
    if (p1 != 0)
    {
        p2 = fork();
        if (p2 == 0)
        {
            p3 = fork();
            if (p3 != 0)
            {
                p4 = fork();
                if (p4 != 0)
                {
                    p5 = fork();
                }
            }
        }
    }
    while (1);
}
