#include <stdio.h>
#include <stdlib.h>

int is_even(int num) {
    return (num & 1) == 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    long val = strtol(argv[1], NULL, 10);
    if (val < INT_MIN || val > INT_MAX) {
        return 1;
    }

    int num = (int)val;
    if (is_even(num)) {
        printf("Even\n");
    } else {
        printf("Odd\n");
    }

    return 0;
}