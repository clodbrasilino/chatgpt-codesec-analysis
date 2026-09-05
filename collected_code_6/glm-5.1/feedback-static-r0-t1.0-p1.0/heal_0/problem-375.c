#include <stdio.h>
#include <stdlib.h>

int round_to_nearest_multiple(int num, int multiple) {
    if (multiple == 0) {
        exit(EXIT_FAILURE);
    }
    int quotient = num / multiple;
    int remainder = num % multiple;
    if (remainder < 0) {
        remainder = -remainder;
        multiple = -multiple;
    }
    if (remainder * 2 >= multiple) {
        if ((num < 0) == (multiple < 0)) {
            quotient++;
        } else {
            quotient--;
        }
    }
    return quotient * multiple;
}

int main() {
    int n = 17;
    int m = 5;
    int result = round_to_nearest_multiple(n, m);
    printf("%d\n", result);
    return 0;
}