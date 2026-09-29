#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool is_vowel(char c) {
    c = (char)tolower((unsigned char)c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U');
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

    strcpy(result, s);

    if (len == 0) {
        return result;
    }

    size_t left = 0;
    size_t right = len - 1;

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
    char buffer[2048];
    if (fgets(buffer, sizeof(buffer), stdin)) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        }
        char* reversed = reverse_vowels(buffer);
        if (reversed != NULL) {
            printf("%s", reversed);
            free(reversed);
        }
    }
    return EXIT_SUCCESS;
}