#include <stdio.h>

int gcd(int a, int b){
    if(b == 0)
        return a;
    return gcd(b, a % b);
}

/* Possible weaknesses found:
 *  expected '=', ',', ';', 'asm' or '__attribute__' at end of input
 */
int isCop