#include <stdio.h>
#include <math.h>

int findSquareRoot(int num) {
    /* Possible weaknesses found:
     * UBSan: nan is outside the range of representable values of type 'int' (AFL crash: id:000000,sig:06,src:000001,time:265,execs:125,op:havoc,rep:3)
     */
    int sqrtNum = (int)sqrt(num);
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: -2147483648 * -2147483648 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:265,execs:125,op:havoc,rep:3)
     */
    if (sqrtNum * sqrtNum == num) {
        return sqrtNum;
    } else {
        return -1;
    }
}

int main() {
    int num;
    printf("Enter a perfect square number: ");
    scanf("%d", &num);

    int result = findSquareRoot(num);
    if (result != -1) {
        printf("Square root of %d is %d\n", num, result);
    } else {
        printf("%d is not a perfect square number\n", num);
    }

    return 0;
}