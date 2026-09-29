#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define BINARY_MAX_LENGTH 64
#define BUFFER_SIZE 128

long long binaryToDecimal(const char *binary) {
    long long decimal = 0;
    size_t length;
    size_t i;

    if (binary == NULL) {
        return -1;
    }

    length = strnlen(binary, BINARY_MAX_LENGTH + 1);

    if (length == 0 || length > BINARY_MAX_LENGTH) {
        return -1;
    }

    for (i = 0; i < length; i++) {
        if (binary[i] == '1') {
            size_t shift = length - 1 - i;
            if (shift >= (sizeof(long long) * 8 - 1)) {
                return -1;
            }
            long long power = 1LL << shift;
            if (power < 0) {
                return -1;
            }
            if (decimal > LLONG_MAX - power) {
                return -1;
            }
            decimal += power;
        } else if (binary[i] != '0') {
            return -1;
        }
    }

    return decimal;
}

int main(void) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    long long result;
    ssize_t len;

    printf("Enter a binary number: ");

    len = getline(&buffer, &buffer_size, stdin);
    if (len == -1) {
        fprintf(stderr, "Error reading input\n");
        free(buffer);
        return 1;
    }

    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
        len--;
    }

    if (len == 0 || len > BINARY_MAX_LENGTH) {
        fprintf(stderr, "Invalid input\n");
        free(buffer);
        return 1;
    }

    result = binaryToDecimal(buffer);

    if (result == -1) {
        fprintf(stderr, "Invalid binary number\n");
        free(buffer);
        return 1;
    }

    printf("Decimal equivalent: %lld\n", result);

    free(buffer);
    return 0;
}