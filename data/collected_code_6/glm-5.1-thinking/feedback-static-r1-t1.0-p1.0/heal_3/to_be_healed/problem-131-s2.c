#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void reverse_vowels(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return;
    }

    size_t left = 0;
    size_t right = strnlen(str, size);

    if (right == 0) {
        return;
    }
    right--;

    while (left < right) {
        while (left < right && !is_vowel(str[left])) {
            left++;
        }
        while (left < right && !is_vowel(str[right])) {
            right--;
        }
        if (left < right) {
            char temp = str[left];
            str[left] = str[right];
            str[right] = temp;
            left++;
            right--;
        }
    }
}

int main(void) {
    const char *original = "hello world";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(original) + 1;
    char *buffer = malloc(len);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    snprintf(buffer, len, "%s", original);

    printf("Original: %s\n", buffer);
    reverse_vowels(buffer, len);
    printf("Reversed: %s\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}