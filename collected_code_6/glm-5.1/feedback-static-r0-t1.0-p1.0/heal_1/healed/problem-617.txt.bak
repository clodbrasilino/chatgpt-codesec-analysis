#include <stdio.h>
#include <stdlib.h>

int calculate_jumps(int a, int b, int d) {
    if (a <= 0 || b <= 0) {
        return -1;
    }
    if (d < 0) {
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
            int diff = d - current_dist;
            if (diff < 0) {
                diff = -diff;
            }
            if (diff % b == 0) {
                return i + (diff / b);
            }
        }
    }
    if (d % b == 0) {
        return d / b;
    }
    return -1;
}

int main(int argc, char * const argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int d = atoi(argv[3]);
    int result = calculate_jumps(a, b, d);
    printf("%d\n", result);
    return EXIT_SUCCESS;
}