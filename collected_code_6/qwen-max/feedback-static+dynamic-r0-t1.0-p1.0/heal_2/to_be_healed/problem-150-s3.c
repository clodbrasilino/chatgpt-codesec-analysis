#include <stdio.h>
#include <stdbool.h>

bool is_in_sequence(int n) {
    int a = 0, b = 1;
    while (a <= n) {
        if (a == n) return true;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1134903170 + 1836311903 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000006,time:4333,execs:1933,op:havoc,rep:4)
         */
        int c = a + b;
        a = b;
        b = c;
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (is_in_sequence(num)) {
        printf("Number is in the sequence\n");
    } else {
        printf("Number is not in the sequence\n");
    }
    return 0;
}