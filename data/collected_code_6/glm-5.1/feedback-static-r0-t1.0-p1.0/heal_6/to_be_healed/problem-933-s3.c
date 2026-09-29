#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *camel_to_snake(const char *camel_str) {
    if (camel_str == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(camel_str);

    if (input_len == 0) {
        char *empty = malloc(1);
        if (empty) empty[0] = '\0';
        return empty;
    }

    size_t max_len = input_len * 2 + 1;
    char *temp1 = malloc(max_len);
    char *temp2 = malloc(max_len);

    if (temp1 == NULL || temp2 == NULL) {
        free(temp1);
        free(temp2);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(temp1, camel_str, input_len + 1);

    size_t current_len = input_len;
    size_t offset = 0;

    while (offset < current_len) {
        size_t match_pos = 0;
        int found = 0;

        for (size_t i = offset; i + 1 < current_len; i++) {
            if (islower((unsigned char)temp1[i]) && isupper((unsigned char)temp1[i + 1])) {
                match_pos = i + 1;
                found = 1;
                break;
            }
        }

        if (!found) {
            break;
        }

        size_t prefix_len = match_pos - 1;
        size_t suffix_len = current_len - match_pos;

        if (prefix_len + 2 + suffix_len < max_len) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp2, temp1, prefix_len);
            temp2[prefix_len] = '_';
            temp2[prefix_len + 1] = tolower((unsigned char)temp1[match_pos]);
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(temp2 + prefix_len + 2, temp1 + match_pos + 1, suffix_len);
            current_len = prefix_len + 2 + suffix_len;
            temp2[current_len] = '\0';

            if (current_len + 1 <= max_len) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(temp1, temp2, current_len + 1);
            }
        }
        offset = prefix_len + 2;
    }

    size_t final_len = current_len + 1;
    char *final_str = malloc(final_len);
    if (final_str == NULL) {
        free(temp1);
        free(temp2);
        return NULL;
    }

    if (final_len <= max_len) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(final_str, temp1, final_len);
    }

    free(temp1);
    free(temp2);

    return final_str;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camel_case_string>\n", argv[0]);
        return 1;
    }

    char *snake_str = camel_to_snake(argv[1]);
    if (snake_str == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return 1;
    }

    printf("%s\n", snake_str);

    free(snake_str);
    return 0;
}