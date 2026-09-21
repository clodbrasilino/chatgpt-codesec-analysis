#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_characters(char *start, char *end);
void reverse_words(char *str, size_t max_length);

void reverse_characters(char *start, char *end) {
    if (start == NULL || end == NULL) {
        return;
    }

    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

void reverse_words(char *str, size_t max_length) {
    if (str == NULL || max_length == 0) {
        return;
    }

    size_t length = 0;
    while (length < max_length && str[length] != '\0') {
        length++;
    }

    if (length == 0) {
        return;
    }

    reverse_characters(str, str + length - 1);

    char *word_start = str;
    char *word_end = str;

    while (*word_end != '\0' && (size_t)(word_end - str) < length) {
        if (*word_end == ' ') {
            word_end++;
            continue;
        }

        word_start = word_end;
        while (*word_end != '\0' && *word_end != ' ' && (size_t)(word_end - str) < length) {
            word_end++;
        }

        reverse_characters(word_start, word_end - 1);
    }
}

int main(void) {
    const char source[] = "the quick brown fox jumps over the lazy dog";
    size_t buffer_size = sizeof(source);

    char *mutable_str = (char *)malloc(buffer_size);
    if (mutable_str == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(mutable_str, source, buffer_size);

    reverse_words(mutable_str, buffer_size);
    printf("%s\n", mutable_str);

    free(mutable_str);
    mutable_str = NULL;

    return EXIT_SUCCESS;
}