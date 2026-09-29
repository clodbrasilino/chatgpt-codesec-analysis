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

    len = strnlen(input, 1023);
    if (len == 0) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        if (input[i] < '0' || input[i] > '9') {
            return 0;
        }
        int digit = input[i] - '0';
        counts[digit]++;
        if (counts[digit] > digit) {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[]) {
    char *buffer = NULL;
    size_t max_len = 1023;
    size_t buffer_size = max_len + 1;
    int result;

    buffer = (char *)malloc(buffer_size);
    if (buffer == NULL) {
        return 1;
    }

    if (fgets(buffer, buffer_size, stdin) == NULL) {
        free(buffer);
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = check_digit_frequency(buffer);

    printf("%d\n", result);

    free(buffer);

    return 0;
}