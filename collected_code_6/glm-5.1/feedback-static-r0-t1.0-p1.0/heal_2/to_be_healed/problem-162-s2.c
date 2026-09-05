#include <stdio.h>
#include <stdlib.h>

int calculate_sum(int n) {
    if (n <= 0) {
        return 0;
    }
    int sum = 0;
    int current = n;
    while (current > 0) {
        sum += current;
        if (current > 1) {
            current -= 2;
        } else {
            current = 0;
        }
    }
    return sum;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 2147483647) {
        return EXIT_FAILURE;
    }
    int n = (int)val;
    int result = calculate_sum(n);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}