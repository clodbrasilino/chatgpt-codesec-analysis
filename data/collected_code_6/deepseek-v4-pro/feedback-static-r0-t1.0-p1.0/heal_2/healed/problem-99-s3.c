#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char *decimal_to_binary(int decimal) {
    unsigned int num;
    int is_negative = 0;
    int bits = sizeof(num) * 8;

    if (decimal == 0) {
        char *result = (char *)malloc(2 * sizeof(char));
        if (result == NULL) {
            return NULL;
        }
        result[0] = '0';
        result[1] = '\0';
        return result;
    }

    if (decimal == INT_MIN) {
        char *result = (char *)malloc((bits + 1) * sizeof(char));
        if (result == NULL) {
            return NULL;
        }
        result[0] = '1';
        for (int i = 1; i < bits; i++) {
            result[i] = '0';
        }
        result[bits] = '\0';
        return result;
    }

    if (decimal < 0) {
        is_negative = 1;
        num = (unsigned int)(-decimal);
        num = ~num + 1;
    } else {
        num = (unsigned int)decimal;
    }

    char *binary = (char *)malloc((bits + 1) * sizeof(char));
    if (binary == NULL) {
        return NULL;
    }

    int index = 0;
    for (int i = bits - 1; i >= 0; i--) {
        binary[index++] = (num & (1u << i)) ? '1' : '0';
    }
    binary[index] = '\0';

    int first_one = 0;
    while (first_one < bits - 1 && binary[first_one] == '0') {
        first_one++;
    }

    size_t trimmed_len = (size_t)(index - first_one);
    char *trimmed = (char *)malloc(trimmed_len + 1);
    if (trimmed == NULL) {
        free(binary);
        return NULL;
    }

    if (trimmed_len > 0) {
        size_t src_len = (size_t)(index - first_one);
        if (src_len > trimmed_len) {
            src_len = trimmed_len;
        }
        memmove(trimmed, binary + first_one, src_len);
    }
    trimmed[trimmed_len] = '\0';
    free(binary);
    return trimmed;
}

int main(void) {
    int numbers[] = {0, 1, 2, 5, 10, 255, 256, -1, -2, -15, 1024, -1024, -2147483647 - 1};
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