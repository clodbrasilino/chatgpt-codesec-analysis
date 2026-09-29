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
    int max_size = bits + 2;
    char *buffer = (char *)malloc(max_size * sizeof(char));
    if (buffer == NULL) {
        return NULL;
    }

    int index = 0;

    if (is_negative) {
        buffer[index++] = '-';
    }

    int started = 0;
    for (int i = bits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1u;
        if (bit == 1) {
            started = 1;
        }
        if (started) {
            buffer[index++] = bit ? '1' : '0';
        }
    }

    if (!started) {
        buffer[index++] = '0';
    }

    buffer[index] = '\0';

    char *result = (char *)malloc((index + 1) * sizeof(char));
    if (result == NULL) {
        free(buffer);
        return NULL;
    }

    memcpy(result, buffer, (index + 1) * sizeof(char));
    free(buffer);

    return result;
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