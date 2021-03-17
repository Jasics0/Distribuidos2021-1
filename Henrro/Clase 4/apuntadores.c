#include <stdio.h>
struct est
{
    int x;
    long y;
};

int main(int argc, char const *argv[])
{
    struct est a;
    struct est *p;
    a.x = 8;
    a.y = 1e7;
    p = &a;
    (*p).y++;
    p->x++;
    printf("\n%d\n", a.x);
    printf("\n%ld\n", a.y);
    return 0;
}
