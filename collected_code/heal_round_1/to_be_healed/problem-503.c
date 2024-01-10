#include<stdio.h>

int addConsecutiveNumbers(int* list, int length) {
    int sum = 0;
    for(int i = 0; i < length; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        sum += list[i];
    }
    return sum;
}

int main() {
    int list[] = {1, 2, 3, 4, 5};
    int length = sizeof(list) / sizeof(list[0]);
    int result = addConsecutiveNumbers(list, length);
    printf("Sum of consecutive numbers: %d\n", result);
    return 0;
}