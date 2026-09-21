#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static int is_vowel(char c) {
    char lower = c | 32;
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}

char *reverse_vowels(const char *s) {
    if (s == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(s);

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, s, len + 1);
    } else {
        result[0] = '\0';
    }

    size_t left = 0;
    size_t right = len > 0 ? len - 1 : 0;

    while (left < right) {
        while (left < right && !is_vowel(result[left])) {
            left++;
        }
        while (left < right && !is_vowel(result[right])) {
            right--;
        }
        if (left < right) {
            char temp = result[left];
            result[left] = result[right];
            result[right] = temp;
            left++;
            right--;
        }
    }

    return result;
}

int main(void) {
    const char *input = "hello world";
    char *reversed = reverse_vowels(input);

    if (reversed != NULL) {
        printf("Original: %s\n", input);
        printf("Reversed: %s\n", reversed);
        free(reversed);
    }

    return 0;
}