#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long binaryToDecimal(const char *binaryString) {
    if (binaryString == NULL) {
        return -1;
    }

    long long decimalValue = 0;
    size_t len = 0;

    for (const char *p = binaryString; *p != '\0'; p++) {
        if (len >= 63) {
            return -1;
        }
        if (*p != '0' && *p != '1') {
            return -1;
        }
        decimalValue = (decimalValue << 1) | (*p - '0');
        len++;
    }

    if (len == 0) {
        return -1;
    }

    return decimalValue;
}

int main(void) {
    size_t capacity = 128;
    size_t length = 0;
    char *binaryInput = malloc(capacity);

    if (binaryInput == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return EXIT_FAILURE;
    }

    int c;
    int hasInput = 0;

    while ((c = fgetc(stdin)) != EOF && c != '\n' && c != '\r') {
        hasInput = 1;
        binaryInput[length++] = (char)c;
        if (length >= capacity - 1) {
            capacity *= 2;
            char *newBuffer = realloc(binaryInput, capacity);
            if (newBuffer == NULL) {
                free(binaryInput);
                fprintf(stderr, "Memory allocation error\n");
                return EXIT_FAILURE;
            }
            binaryInput = newBuffer;
        }
    }

    if (!hasInput && c == EOF) {
        free(binaryInput);
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    binaryInput[length] = '\0';

    long long result = binaryToDecimal(binaryInput);
    free(binaryInput);

    if (result != -1) {
        printf("%lld\n", result);
    } else {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}