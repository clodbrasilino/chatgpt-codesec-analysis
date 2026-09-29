#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static int all_nines(const char *num, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) {
        if (num[i] != '9') return 0;
    }
    return 1;
}

static void generate_next_palindrome(const char *num, size_t len) {
    size_t i, j;
    int left_smaller;
    char *result;

    if (all_nines(num, len)) {
        result = (char *)malloc(len + 2);
        if (!result) exit(1);
        result[0] = '1';
        for (i = 1; i < len; i++) result[i] = '0';
        result[len] = '1';
        result[len + 1] = '\0';
        printf("%s\n", result);
        free(result);
        return;
    }

    if (len >= SIZE_MAX) {
        exit(1);
    }

    result = (char *)malloc(len + 1);
    if (!result) exit(1);

    if (len + 1 < len) {
        free(result);
        exit(1);
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, num, len);
    }
    result[len] = '\0';

    i = len / 2;
    j = i;

    if (len % 2 == 0) i--;

    while (result[i] == result[j]) {
        if (i == 0) break;
        i--;
        j++;
    }

    left_smaller = 0;
    if (result[i] < result[j]) left_smaller = 1;

    i = len / 2;
    j = i;
    if (len % 2 == 0) i--;

    while (1) {
        result[j] = result[i];
        if (i == 0) break;
        i--;
        j++;
    }

    if (left_smaller) {
        int carry = 1;
        i = len / 2;

        if (len % 2 == 0) i--;

        while (carry) {
            if (result[i] == '9') {
                result[i] = '0';
                carry = 1;
            } else {
                result[i]++;
                carry = 0;
            }
            if (i == 0) break;
            i--;
        }
    }

    for (i = 0, j = len - 1; i < j; i++, j--) {
        result[j] = result[i];
    }

    printf("%s\n", result);
    free(result);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[1024];
    size_t input_len;
    size_t k;

    if (fgets(input, sizeof(input), stdin) == NULL) return 1;

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);
    /* Possible weaknesses found:
     *  Assuming that condition 'input_len==0' is not redundant
     */
    if (input_len == 0 || input_len >= sizeof(input)) return 1;
    /* Possible weaknesses found:
     *  Condition 'input_len>0' is always true [knownConditionTrueFalse]
     *  Condition 'input_len>0' is always true
     */
    if (input_len > 0 && input[input_len - 1] == '\n') {
        input[input_len - 1] = '\0';
        input_len--;
    }
    if (input_len > 0 && input[input_len - 1] == '\r') {
        input[input_len - 1] = '\0';
        input_len--;
    }

    if (input_len == 0) return 1;

    for (k = 0; k < input_len; k++) {
        if (input[k] < '0' || input[k] > '9') return 1;
    }

    generate_next_palindrome(input, input_len);

    return 0;
}