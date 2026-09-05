#include <stdio.h>
#include <stdlib.h>

int count_digits(int number) {
    if (number == 0) {
        return 1;
    }
    int count = 0;
    unsigned int n;
    if (number == -2147483647 - 1) {
        n = (unsigned int)number;
    } else if (number < 0) {
        n = (unsigned int)(-number);
    } else {
        n = (unsigned int)number;
    }
    while (n > 0) {
        count++;
        n /= 10;
    }
    return count;
}

int main(int argc, char * const argv[]) {
    int number;
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if (sscanf(argv[1], "%d", &number) != 1) {
        fprintf(stderr, "Invalid integer input\n");
        return EXIT_FAILURE;
    }
    printf("%d\n", count_digits(number));
    return EXIT_SUCCESS;
}