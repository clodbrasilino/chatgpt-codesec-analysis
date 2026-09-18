#include <stdio.h>
#include <math.h>

int is_perfect_square(int n) {
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:609,execs:265,op:havoc,rep:4)
     */
    int root = (int)sqrt(n);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -2147483648 * -2147483648 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:609,execs:265,op:havoc,rep:4)
     */
    return n == root * root;
}

int main() {
    int num;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        return 1;
    }

    if (is_perfect_square(num)) {
        printf("The square root of %d is %d\n", num, (int)sqrt(num));
    } else {
        printf("%d is not a perfect square\n", num);
    }

    return 0;
}