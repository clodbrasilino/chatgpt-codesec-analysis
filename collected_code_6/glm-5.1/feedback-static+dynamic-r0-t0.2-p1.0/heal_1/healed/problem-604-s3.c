#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char *start, char *end) {
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char* reverse_words(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }

    if (len == 0) {
        return str;
    }

    char *result = (char *)malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i <= len; i++) {
        result[i] = str[i];
    }

    reverse(result, result + len - 1);

    char *word_start = result;
    char *current = result;

    while (*current) {
        if (*current == ' ') {
            reverse(word_start, current - 1);
            current++;
            word_start = current;
        } else {
            current++;
        }
    }

    reverse(word_start, current - 1);

    return result;
}

int main() {
    char str[] = "Hello World from C";
    char *reversed = reverse_words(str);

    if (reversed != NULL) {
        printf("Original: %s\n", str);
        printf("Reversed: %s\n", reversed);
        free(reversed);
    } else {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    return 0;
}