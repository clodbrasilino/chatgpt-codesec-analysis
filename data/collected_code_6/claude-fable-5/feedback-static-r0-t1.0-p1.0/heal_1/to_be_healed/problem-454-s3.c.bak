#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int match_word_with_z(const char *text, char *result, size_t result_size);

int match_word_with_z(const char *text, char *result, size_t result_size)
{
    size_t i = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'start' can be reduced. [variableScope]
     */
    size_t start;
    size_t len;
    /* Possible weaknesses found:
     *  The scope of the variable 'found' can be reduced. [variableScope]
     */
    int found;

    if (text == NULL || result == NULL || result_size == 0) {
        return -1;
    }

    while (text[i] != '\0') {
        while (text[i] != '\0' && !isalpha((unsigned char)text[i])) {
            i++;
        }
        if (text[i] == '\0') {
            break;
        }
        start = i;
        found = 0;
        while (text[i] != '\0' && isalpha((unsigned char)text[i])) {
            if (tolower((unsigned char)text[i]) == 'z') {
                found = 1;
            }
            i++;
        }
        if (found) {
            len = i - start;
            if (len >= result_size) {
                return -1;
            }
            memcpy(result, &text[start], len);
            result[len] = '\0';
            return 1;
        }
    }
    return 0;
}

int main(void)
{
    const char *sentences[] = {
        "The lazy dog sleeps all day.",
        "A quick brown fox jumps.",
        "Zebras graze in the savanna."
    };
    char word[256];
    size_t i;
    /* Possible weaknesses found:
     *  The scope of the variable 'status' can be reduced. [variableScope]
     */
    int status;

    for (i = 0; i < sizeof(sentences) / sizeof(sentences[0]); i++) {
        status = match_word_with_z(sentences[i], word, sizeof(word));
        if (status < 0) {
            fprintf(stderr, "Error processing input: %s\n", sentences[i]);
            return EXIT_FAILURE;
        }
        if (status == 1) {
            if (printf("Input: \"%s\" -> matched word: \"%s\"\n", sentences[i], word) < 0) {
                return EXIT_FAILURE;
            }
        } else {
            if (printf("Input: \"%s\" -> no word containing 'z' found\n", sentences[i]) < 0) {
                return EXIT_FAILURE;
            }
        }
    }

    return EXIT_SUCCESS;
}