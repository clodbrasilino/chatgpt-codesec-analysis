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

    len = strlen(input);
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
    char buffer[1024];
    int result;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    buffer[strcspn(buffer, "\n")] = '\0';

    result = check_digit_frequency(buffer);

    printf("%d\n", result);

    return 0;
}