#include <stdio.h>

int last_digit_factorial(int n) {
    if (n == 0 || n == 1) {
        return 1;
    }
    int count = 0, i;
    /* Possible weaknesses found:
     * UBSan: signed integer overflow: 1220703125 * 5 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:1413,execs:569,op:havoc,rep:3)
     */
    for (i = 5; n / i >= 1; i *= 5) {
        count += n / i;
    }
    if (count > 1) {
        return 0;
    } else if (count == 1) {
        return 5;
    } else {
        n %= 10;
        switch (n) {
            case 2: return 2;
            case 3: return 6;
            case 4: return 4;
            case 6: return 6;
            case 7: return 2;
            case 8: return 4;
            case 9: return 8;
            default: return 1;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    printf("%d\n", last_digit_factorial(n));
    return 0;
}