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

    size_t len = strlen(s);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    memcpy(result, s, len + 1);

    if (len == 0) {
        return result;
    }

    size_t left = 0;
    size_t right = len - 1;

    while (left < right) {
        if (!is_vowel(result[left])) {
            left++;
            continue;
        }
        if (!is_vowel(result[right])) {
            right--;
            continue;
        }

        char temp = result[left];
        result[left] = result[right];
        result[right] = temp;

        left++;
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