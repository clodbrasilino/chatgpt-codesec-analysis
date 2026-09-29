#include <stdio.h>
#include <stdbool.h>

bool is_in_sequence(int n) {
    /* Possible weaknesses found:
     *  The scope of the variable 'c' can be reduced. [variableScope]
     *  Variable 'c' is assigned a value that is never used. [unreadVariable]
     */
    int a = 0, b = 1, c = 0;
    while (a <= n) {
        if (a == n) return true;
        /* Possible weaknesses found:
         * UBSan: signed integer overflow: 1134903170 + 1836311903 cannot be represented in type 'int' (AFL crash: id:000000,sig:06,src:000001,time:3376,execs:1273,op:havoc,rep:13)
         */
        c = a + b;
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