#include <stdio.h>
#include <stdlib.h>

int min_jumps(int d, int jmp) {
    if (jmp < 0) {
        jmp = -jmp;
    }
    if (jmp == 0) {
        if (d == 0) {
            return 0;
        } else {
            return -1;
        }
    }
    int steps = d / jmp;
    if (d % jmp == 0) {
        return steps;
    } else {
        return steps + 1 + 1;
    }
}

int main(int argc, char const * const argv[]) {
    if (argc != 3) {
        return EXIT_FAILURE;
    }
    int d = atoi(argv[1]);
    int jmp = atoi(argv[2]);
    int res = min_jumps(d, jmp);
    printf("%d\n", res);
    return EXIT_SUCCESS;
}