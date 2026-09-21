#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_vowel(char c) {
    char lower = c | 32;
    if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u') {
        return 1;
    }
    return 0;
}

char* reverse_vowels(const char* s) {
    if (s == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (s[len] != '\0') {
        len++;
    }

    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'len+1>0' is always true [knownConditionTrueFalse]
     */
    if (len + 1 > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, s, len + 1);
    }

    size_t left = 0;
    size_t right = len > 0 ? len - 1 : 0;

    while (left < right) {
        if (!is_vowel(result[left])) {
            left++;
            continue;
        }
        if (!is_vowel(result[right])) {
            if (right == 0) {
                break;
            }
            right--;
            continue;
        }

        char temp = result[left];
        result[left] = result[right];
        result[right] = temp;

        left++;
        if (right == 0) {
            break;
        }
        right--;
    }

    return result;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char* const argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char* reversed = reverse_vowels(argv[1]);
    if (reversed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", reversed);

    free(reversed);
    reversed = NULL;

    return EXIT_SUCCESS;
}