#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *abbreviate_road(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strnlen(input, 4096);
    char *result = malloc(input_len * 2 + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t i = 0, j = 0;
    while (i < input_len) {
        if (i + 3 < input_len &&
            tolower((unsigned char)input[i]) == 'r' &&
            tolower((unsigned char)input[i + 1]) == 'o' &&
            tolower((unsigned char)input[i + 2]) == 'a' &&
            tolower((unsigned char)input[i + 3]) == 'd') {
            
            if ((i == 0 || !isalpha((unsigned char)input[i - 1])) &&
                (i + 4 >= input_len || !isalpha((unsigned char)input[i + 4]))) {
                result[j++] = input[i];
                result[j++] = 'd';
                result[j++] = '.';
                i += 4;
                continue;
            }
        }
        result[j++] = input[i++];
    }
    result[j] = '\0';

    char *shrunk = realloc(result, j + 1);
    if (shrunk != NULL) {
        result = shrunk;
    }

    return result;
}

#define MAX_TESTS 6
#define MAX_RESULT_LEN 8192

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    const char *tests[MAX_TESTS];
    tests[0] = "123 road street";
    tests[1] = "road road road";
    tests[2] = "main street road";
    tests[3] = "roads and driveways";
    tests[4] = "Road";
    tests[5] = NULL;

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char results[MAX_TESTS][MAX_RESULT_LEN + 1];

    for (int i = 0; i < MAX_TESTS; i++) {
        char *abbreviated = abbreviate_road(tests[i]);
        if (abbreviated != NULL) {
            size_t len = strnlen(abbreviated, MAX_RESULT_LEN);
            if (len <= MAX_RESULT_LEN) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(results[i], abbreviated, len);
                results[i][len] = '\0';
            } else {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(results[i], abbreviated, MAX_RESULT_LEN);
                results[i][MAX_RESULT_LEN] = '\0';
            }
            free(abbreviated);
        } else {
            results[i][0] = '\0';
        }
    }

    for (int i = 0; i < MAX_TESTS; i++) {
        if (tests[i] == NULL) {
            printf("(null input)\n");
        } else if (results[i][0] == '\0') {
            printf("(allocation failed)\n");
        } else {
            printf("%s\n", results[i]);
        }
    }

    return 0;
}