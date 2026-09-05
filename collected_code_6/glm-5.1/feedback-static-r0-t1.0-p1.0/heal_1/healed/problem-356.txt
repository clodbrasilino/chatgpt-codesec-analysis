#include <stdio.h>
#include <stdlib.h>

int find_third_angle(int a, int b) {
    int sum = a + b;
    if (sum <= 0 || sum >= 180) {
        exit(EXIT_FAILURE);
    }
    return 180 - sum;
}

int main(int argc, char * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }

    char *endptr1;
    long val1 = strtol(argv[1], &endptr1, 10);
    if (*endptr1 != '\0' || val1 <= 0 || val1 >= 180) {
        return EXIT_FAILURE;
    }

    char *endptr2;
    long val2 = strtol(argv[2], &endptr2, 10);
    if (*endptr2 != '\0' || val2 <= 0 || val2 >= 180) {
        return EXIT_FAILURE;
    }

    int third = find_third_angle((int)val1, (int)val2);
    printf("%d\n", third);

    return EXIT_SUCCESS;
}