#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

int countFlips(const char *str, size_t len) {
    int flips1 = 0, flips2 = 0;

    for (size_t i = 0; i < len; i++) {
        if (str[i] != (i % 2 == 0 ? '0' : '1')) {
            flips1++;
        } else {
            flips2++;
        }
    }

    return (flips1 < flips2) ? flips1 : flips2;
}

bool isValidBinaryString(const char *str, size_t len) {
    for (size_t i = 0; i < len; i++) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int main(void) {
    char *str = NULL;
    size_t size = 0;
    ssize_t len;

    printf("Enter a binary string: ");

    len = getline(&str, &size, stdin);

    if (len == -1) {
        printf("Invalid input\n");
        free(str);
        return 1;
    }

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    if (len == 0) {
        printf("Invalid input\n");
        free(str);
        return 1;
    }

    if (!isValidBinaryString(str, (size_t)len)) {
        printf("Invalid input: not a binary string\n");
        free(str);
        return 1;
    }

    int result = countFlips(str, (size_t)len);
    printf("Number of flips required: %d\n", result);

    free(str);
    return 0;
}