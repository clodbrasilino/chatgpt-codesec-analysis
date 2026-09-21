#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char *word = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != EOF && ch != '\n' && ch != '\r') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *new_word = realloc(word, new_capacity);

            if (new_word == NULL) {
                free(word);
                return 1;
            }

            word = new_word;
            capacity = new_capacity;
        }

        word[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(word);
        return 1;
    }

    if (word == NULL) {
        if (ch == EOF) {
            return 0;
        }

        word = malloc(1);
        if (word == NULL) {
            return 1;
        }
    }

    word[length] = '\0';

    puts(contains_z(word) ? "Match" : "No match");

    free(word);
    return 0;
}