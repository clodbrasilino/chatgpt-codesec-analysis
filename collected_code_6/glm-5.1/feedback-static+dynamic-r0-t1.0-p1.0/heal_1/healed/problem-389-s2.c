#include <stdio.h>
#include <stdlib.h>

int lucas(int n) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 2;
    }
    if (n == 1) {
        return 1;
    }
    int prev2 = 2;
    int prev1 = 1;
    int current = 0;
    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2;
        prev2 = prev1;
        prev1 = current;
    }
    return current;
}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr;
    long val = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val < 0 || val > 46) {
        fprintf(stderr, "Error: n must be a non-negative integer within 32-bit signed range (0-46).\n");
        return EXIT_FAILURE;
    }
    int result = lucas((int)val);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}