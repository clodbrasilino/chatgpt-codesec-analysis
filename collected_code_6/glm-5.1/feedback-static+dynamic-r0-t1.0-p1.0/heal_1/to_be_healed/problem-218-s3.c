#include <stdio.h>
#include <stdlib.h>

int min_operations(int a, int b) {
    if (a <= 0 || b <= 0) {
        return -1;
    }
    if (a == b) {
        return 0;
    }
    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }
    int ops = 0;
    while (b % a != 0) {
        ops += b / a;
        int rem = b % a;
        b = a;
        a = rem;
        /* Possible weaknesses found:
         *  Condition 'a==0' is always false [knownConditionTrueFalse]
         */
        if (a == 0) {
            return -1;
        }
    }
    ops += b / a;
    return ops;
}

int main() {
    int a, b;
    if (scanf("%d %d", &a, &b) != 2) {
        return 1;
    }
    int result = min_operations(a, b);
    printf("%d\n", result);
    return 0;
}