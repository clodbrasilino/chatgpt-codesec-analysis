#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char *decimal_to_binary(int decimal) {
    if (decimal == 0) {
        char *result = (char *)malloc(2 * sizeof(char));
        if (result == NULL) {
            return NULL;
        }
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    unsigned int num;
    int is_negative = 0;

    if (decimal < 0) {
        is_negative = 1;
        if (decimal == INT_MIN) {
            num = (unsigned int)INT_MIN;
        } else {
            num = (unsigned int)(-decimal);
        }
    } else {
        num = (unsigned int)decimal;
    }

    int bits = sizeof(num) * 8;
    char *binary = (char *)malloc((bits + 2) * sizeof(char));
    if (binary == NULL) {
        return NULL;
    }

    int index = 0;
    if (is_negative) {
        binary[index++] = '-';
    }

    int started = 0;
    for (int i = bits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1u;
        if (bit == 1) {
            started = 1;
        }
        if (started) {
            binary[index++] = bit ? '1' : '0';
        }
    }

    if (!started) {
        binary[index++] = '0';
    }

    binary[index] = '\0';

    size_t trimmed_size = (size_t)index + 1;
    char *trimmed = (char *)malloc(trimmed_size);
    if (trimmed == NULL) {
        free(binary);
        return NULL;
    }

    if (trimmed_size <= (size_t)(bits + 2)) {
        memcpy(trimmed, binary, trimmed_size);
    } else {
        free(binary);
        free(trimmed);
        return NULL;
    }

    free(binary);
    return trimmed;
}

int main(void) {
    int numbers[] = {0, 1, 2, 5, 10, 255, 256, -1, -2, -15, 1024, -1024};
    int count = sizeof(numbers) / sizeof(numbers[0]);

    for (int i = 0; i < count; i++) {
        char *binary = decimal_to_binary(numbers[i]);
        if (binary == NULL) {
            fprintf(stderr, "Memory allocation failed for %d\n", numbers[i]);
            continue;
        }
        printf("%d in binary: %s\n", numbers[i], binary);
        free(binary);
    }

    return 0;
}