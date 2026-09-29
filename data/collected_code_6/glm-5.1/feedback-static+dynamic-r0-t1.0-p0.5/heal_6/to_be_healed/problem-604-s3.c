#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

void reverse(char *str, size_t left, size_t right) {
    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

char *reverse_words(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t len = strnlen(input, SIZE_MAX);
    if (len == 0) {
        char *empty = malloc(1);
        if (empty == NULL) {
            return NULL;
        }
        empty[0] = '\0';
        return empty;
    }

    if (len == SIZE_MAX) {
        return NULL;
    }

    char *buffer = malloc(len + 1);
    if (buffer == NULL) {
        return NULL;
    }

    if (len + 1 <= len) {
        free(buffer);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, len + 1);

    reverse(buffer, 0, len - 1);

    size_t start = (size_t)-1;
    for (size_t i = 0; i <= len; i++) {
        if (buffer[i] != ' ' && start == (size_t)-1) {
            start = i;
        } else if ((buffer[i] == ' ' || buffer[i] == '\0') && start != (size_t)-1) {
            reverse(buffer, start, i - 1);
            start = (size_t)-1;
        }
    }

    return buffer;
}

int main(void) {
    const char *text = "Hello World from C";
    char *reversed = reverse_words(text);

    if (reversed == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("%s\n", reversed);

    free(reversed);
    reversed = NULL;

    return 0;
}