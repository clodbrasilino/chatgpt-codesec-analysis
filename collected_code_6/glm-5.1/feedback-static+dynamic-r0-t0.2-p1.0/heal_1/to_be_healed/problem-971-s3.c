#include <stdio.h>
#include <stdlib.h>

int find_max_segments(int n, int a, int b, int c) {
    if (n < 0) {
        return -1;
    }
    if (n == 0) {
        return 0;
    }

    int res_a = find_max_segments(n - a, a, b, c);
    int res_b = find_max_segments(n - b, a, b, c);
    int res_c = find_max_segments(n - c, a, b, c);

    int max_res = -1;
    if (res_a > max_res) {
        max_res = res_a;
    }
    if (res_b > max_res) {
        max_res = res_b;
    }
    if (res_c > max_res) {
        max_res = res_c;
    }

    if (max_res == -1) {
        return -1;
    }

    return max_res + 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Usage: %s <n> <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr;
    long val_n = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0' || val_n < 0) {
        fprintf(stderr, "Invalid input for n\n");
        return EXIT_FAILURE;
    }

    long val_a = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0' || val_a <= 0) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }

    long val_b = strtol(argv[3], &endptr, 10);
    if (*endptr != '\0' || val_b <= 0) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }

    long val_c = strtol(argv[4], &endptr, 10);
    if (*endptr != '\0' || val_c <= 0) {
        fprintf(stderr, "Invalid input for c\n");
        return EXIT_FAILURE;
    }

    int n = (int)val_n;
    int a = (int)val_a;
    int b = (int)val_b;
    int c = (int)val_c;

    int result = find_max_segments(n, a, b, c);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}