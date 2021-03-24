#include <stdio.h>
#include <unistd.h>

int main()
{
    int b, c, d, e, f;

    b = fork();
    if (b != 0)
    {
        c = fork();
        if (c == 0)
        {
            d = fork();
            if (d != 0)
            {
                e = fork();
                if (e != 0)
                {
                    f = fork();
                }
            }
        }
    }
    while (1)
    {
    }
}