#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected '111', got <no output>
  *  test case 0 failed: expected '1000', got <no output>
  *  test case 1 failed: expected '10010', got <no output>
  */

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[bits + 2];
    int index = 0;
    
    if (is_negative) {
        temp[index++] = '-';
    }

    int started = 0;
    for (int i = bits - 1; i >= 0; i--) {
        int bit = (num >> i) & 1u;
        if (bit == 1) {
            started = 1;
        }
        if (started) {
            temp[index++] = bit ? '1' : '0';
        }
    }

    if (!started) {
        temp[index++] = '0';
    }

    temp[index] = '\0';

    char *trimmed = (char *)malloc((index + 1) * sizeof(char));
    if (trimmed == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(trimmed, temp, index + 1);

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