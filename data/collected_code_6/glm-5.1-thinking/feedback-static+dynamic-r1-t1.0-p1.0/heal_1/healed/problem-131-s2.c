#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_vowel(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void reverse_vowels(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return;
    }

    size_t left = 0;
    size_t right = len - 1;

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
    char original[] = "hello world";
    size_t len = sizeof(original) - 1;
    char *buffer = malloc(len + 1);

    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, original, len + 1);

    printf("Original: %s\n", buffer);
    reverse_vowels(buffer, len);
    printf("Reversed: %s\n", buffer);

    free(buffer);
    buffer = NULL;

    return EXIT_SUCCESS;
}