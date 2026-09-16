#include <stdio.h>
#include <stdlib.h>

double min_jumps(double a, double b, double d) {
    if (d == 0.0) {
        return 0.0;
    }
    if (a == 0.0 && b == 0.0) {
        return -1.0;
    }
    if (a == 0.0) {
        if (fmod(d, b) == 0.0) {
            return d / b;
        } else {
            return -1.0;
        }
    }
    if (b == 0.0) {
        if (fmod(d, a) == 0.0) {
            double jumps = d / a;
            if (jumps > 0.0) {
                return jumps;
            }
        }
        return -1.0;
    }
    double max_steps = d / a + 2.0;
    double min_res = -1.0;
    for (double y = 0.0; y <= max_steps; y += 1.0) {
        double rem = d - y * b;
        if (rem < 0.0) {
            break;
        }
        if (fmod(rem, a) == 0.0) {
            double x = rem / a;
            if (x >= 0.0) {
                if (x >= y) {
                    double res = x - y + 2.0 * y;
                    if (min_res == -1.0 || res < min_res) {
                        min_res = res;
                    }
                } else {
                    double res = y;
                    if (min_res == -1.0 || res < min_res) {
                        min_res = res;
                    }
                }
            }
        }
    }
    return min_res;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <jumpA> <jumpB> <distance>\n", argv[0]);
        return EXIT_FAILURE;
    }
    char *endptr_a, *endptr_b, *endptr_d;
    double a = strtod(argv[1], &endptr_a);
    double b = strtod(argv[2], &endptr_b);
    double d = strtod(argv[3], &endptr_d);
    if (*endptr_a != '\0' || *endptr_b != '\0' || *endptr_d != '\0') {
        fprintf(stderr, "Invalid number input\n");
        return EXIT_FAILURE;
    }
    if (a < 0.0 || b < 0.0 || d < 0.0) {
        fprintf(stderr, "Inputs must be non-negative\n");
        return EXIT_FAILURE;
    }
    double result = min_jumps(a, b, d);
    if (result == (int)result) {
        printf("%d\n", (int)result);
    } else {
        printf("%g\n", result);
    }
    return EXIT_SUCCESS;
}