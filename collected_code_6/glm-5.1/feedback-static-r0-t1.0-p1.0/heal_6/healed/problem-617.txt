#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int calculate_jumps(int a, int b, int d) {
    if (a <= 0 || b <= 0 || d < 0) {
        return -1;
    }
    if (d == 0) {
        return 0;
    }
    if (d % a == 0) {
        return d / a;
    }
    if (a > b) {
        int max_forward_jumps = d / a;
        for (int i = max_forward_jumps; i >= 0; i--) {
            int current_dist = i * a;
            if (current_dist <= d) {
                int diff = d - current_dist;
                if (diff % b == 0) {
                    return i + (diff / b);
                }
            } else {
                int diff = current_dist - d;
                if (diff % b == 0) {
                    return i + (diff / b);
                }
            }
        }
    }
    if (d % b == 0) {
        return d / b;
    }
    return -1;
}

int main(int argc, char * const argv[const]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    char *endptr;
    errno = 0;
    long val_a = strtol(argv[1], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[1] || val_a < INT_MIN || val_a > INT_MAX) {
        return EXIT_FAILURE;
    }
    errno = 0;
    long val_b = strtol(argv[2], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[2] || val_b < INT_MIN || val_b > INT_MAX) {
        return EXIT_FAILURE;
    }
    errno = 0;
    long val_d = strtol(argv[3], &endptr, 10);
    if (errno != 0 || *endptr != '\0' || endptr == argv[3] || val_d < INT_MIN || val_d > INT_MAX) {
        return EXIT_FAILURE;
    }
    int a = (int)val_a;
    int b = (int)val_b;
    int d = (int)val_d;
    int result = calculate_jumps(a, b, d);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}