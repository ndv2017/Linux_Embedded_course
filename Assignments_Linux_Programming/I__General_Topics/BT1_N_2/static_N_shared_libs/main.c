#include <stdio.h>
#include "inc/mymath.h"
#include "inc/hivion.h"
#include "inc/hello.h"

int main()
{
    int a = 9, b = 7;
    printf("\nMultiple of %d and %d is %d\n", a, b, multi(a, b));
    hello();
    hivion();

    return 0;
}