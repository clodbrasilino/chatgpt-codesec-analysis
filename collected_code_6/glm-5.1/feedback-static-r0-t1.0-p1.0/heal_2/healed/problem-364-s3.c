#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}

int count_flips(const char *str) {
    int len = strlen(str);
    if (len == 0) {
        return 0;
    }

    int flip1 = 0;
    int flip2 = 0;

    for (int i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            exit(EXIT_FAILURE);
        }

        if (i % 2 == 0) {
            if (str[i] != '0') flip1++;
            if (str[i] != '1') flip2++;
        } else {
            if (str[i] != '1') flip1++;
            if (str[i] != '0') flip2++;
        }
    }

    return min(flip1, flip2);
}

int main(int argc, char const * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <binary_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int result = count_flips(argv[1]);
    printf("%d\n", result);

    return EXIT_SUCCESS;
}