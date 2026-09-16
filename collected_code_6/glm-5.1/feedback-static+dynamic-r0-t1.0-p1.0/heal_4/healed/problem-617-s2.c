#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    double max_steps = d / b + 2.0;
    double min_res = -1.0;
    for (double x = 0.0; x <= max_steps; x += 1.0) {
        double rem = d - x * a;
        if (rem < 0.0) {
            break;
        }
        if (fmod(rem, b) == 0.0) {
            double y = rem / b;
            if (y >= 0.0) {
                if (x >= y) {
                    double res = x;
                    if (min_res == -1.0 || res < min_res) {
                        min_res = res;
                    }
                } else {
                    double res = y - x + 2.0 * x;
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
    if (result == floor(result)) {
        printf("%d\n", (int)result);
    } else {
        printf("%g\n", result);
    }
    return EXIT_SUCCESS;
}