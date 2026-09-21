#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* remove_k_length_words(const char* str, int k) {
    if (str == NULL || k < 0) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(str);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t res_idx = 0;
    size_t i = 0;

    while (str[i] != '\0') {
        if (isalpha((unsigned char)str[i])) {
            size_t word_start = i;
            size_t word_len = 0;

            while (str[i] != '\0' && isalpha((unsigned char)str[i])) {
                word_len++;
                i++;
            }

            if (word_len != (size_t)k) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(result + res_idx, str + word_start, word_len);
                res_idx += word_len;
            }
        } else {
            result[res_idx++] = str[i++];
        }
    }

    result[res_idx] = '\0';
    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <string> <k>\n", argv[0]);
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
     */
    int k = atoi(argv[2]);
    if (k < 0) {
        fprintf(stderr, "Error: k must be a non-negative integer.\n");
        return 1;
    }

    char* modified_str = remove_k_length_words(argv[1], k);
    if (modified_str == NULL) {
        fprintf(stderr, "Error: Memory allocation failed or invalid input.\n");
        return 1;
    }

    printf("%s\n", modified_str);

    free(modified_str);
    modified_str = NULL;

    return 0;
}