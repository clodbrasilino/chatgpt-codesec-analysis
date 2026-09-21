#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_digit_frequency(const char *input) {
    size_t len;
    size_t i;
    int counts[10] = {0};

    if (input == NULL) {
        return 0;
    }

    len = strnlen(input, 1024);
    if (len == 0 || input[len] != '\0') {
        return 0;
    }

    for (i = 0; i < len; i++) {
        int digit = input[i] - '0';
        if (digit < 0 || digit > 9) {
            return 0;
        }
        counts[digit]++;
        if (counts[digit] > digit) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    char *buffer = malloc(1024);
    if (buffer == NULL) {
        return 1;
    }

    if (fgets(buffer, 1024, stdin) == NULL) {
        free(buffer);
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    int result = check_digit_frequency(buffer);

    printf("%d\n", result);

    free(buffer);
    return 0;
}