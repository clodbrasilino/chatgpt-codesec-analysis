#include <stdio.h>
#include <stdlib.h>

#define MAX_STR_LEN 4096

void reverse_characters(char *start, char *end);
void reverse_words(char *str);

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

void reverse_words(char *str) {
    if (str == NULL) {
        return;
    }

    size_t length = 0;
    while (str[length] != '\0' && length < MAX_STR_LEN) {
        length++;
    }

    if (length == 0 || length >= MAX_STR_LEN) {
        return;
    }

    reverse_characters(str, str + length - 1);

    char *word_start = str;
    char *word_end = str;

    while (*word_end != '\0') {
        if (*word_end == ' ') {
            word_end++;
            continue;
        }

        word_start = word_end;
        while (*word_end != '\0' && *word_end != ' ') {
            word_end++;
        }

        reverse_characters(word_start, word_end - 1);
    }
}

int main(void) {
    const char *source = "the quick brown fox jumps over the lazy dog";
    
    size_t length = 0;
    while (source[length] != '\0' && length < MAX_STR_LEN) {
        length++;
    }

    if (length >= MAX_STR_LEN) {
        return EXIT_FAILURE;
    }

    char *mutable_str = (char *)malloc(length + 1);
    if (mutable_str == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < length; i++) {
        mutable_str[i] = source[i];
    }
    mutable_str[length] = '\0';

    reverse_words(mutable_str);
    printf("%s\n", mutable_str);

    free(mutable_str);
    mutable_str = NULL;

    return EXIT_SUCCESS;
}