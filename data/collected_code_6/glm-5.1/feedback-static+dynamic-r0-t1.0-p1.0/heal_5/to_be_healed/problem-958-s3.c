#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected 'I', got <no output>
  *  test case 1 failed: expected 'L', got <no output>
  *  test case 2 failed: expected 'IV', got <no output>
  */

char* int_to_roman(int num) {
    if (num <= 0 || num > 3999) {
        return NULL;
    }

    const int values[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const char* const symbols[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    const size_t sym_lengths[] = {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1};

    size_t buffer_size = 16;
    char* result = (char*)malloc(buffer_size * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    size_t offset = 0;

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            if (offset + sym_lengths[i] + 1 > buffer_size) {
                size_t new_buffer_size = (offset + sym_lengths[i] + 1) * 2;
                char* new_result = (char*)realloc(result, new_buffer_size * sizeof(char));
                if (new_result == NULL) {
                    free(result);
                    return NULL;
                }
                result = new_result;
                buffer_size = new_buffer_size;
            }
            if (buffer_size - offset >= sym_lengths[i]) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + offset, symbols[i], sym_lengths[i]);
            }
            offset += sym_lengths[i];
            num -= values[i];
        }
    }
    result[offset] = '\0';

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    char* endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 1 || val > 3999) {
        fprintf(stderr, "Error: Input must be an integer between 1 and 3999.\n");
        return 1;
    }

    char* roman = int_to_roman((int)val);

    if (roman == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    printf("%s\n", roman);

    free(roman);

    return 0;
}