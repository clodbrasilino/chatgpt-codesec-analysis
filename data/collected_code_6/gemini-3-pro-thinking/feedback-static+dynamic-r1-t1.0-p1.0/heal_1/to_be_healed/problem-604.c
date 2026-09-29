#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(str);
    if (length == 0) {
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t length = strlen(source);

    char *mutable_str = (char *)malloc(length + 1);
    if (mutable_str == NULL) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(mutable_str, source, length + 1);

    reverse_words(mutable_str);
    printf("%s\n", mutable_str);

    free(mutable_str);
    mutable_str = NULL;

    return EXIT_SUCCESS;
}