#include <stdio.h>
#include <stdlib.h>

int is_abundant(int num) {
    if (num <= 1) {
        return 0;
    }

    int sum = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            sum += i;
            if (i != num / i) {
                sum += num / i;
            }
        }
    }

    if (sum > num) {
        return 1;
    }

    return 0;
}

int main(int argc, char * const argv[const]) {
    int number;

    if (argc == 2) {
        number = atoi(argv[1]);
    } else {
        if (scanf("%d", &number) != 1) {
            return 1;
        }
    }

    if (number <= 0) {
        return 1;
    }

    if (is_abundant(number)) {
        printf("1\n");
    } else {
        printf("0\n");
    }

    return 0;
}