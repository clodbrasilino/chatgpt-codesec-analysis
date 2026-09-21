#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    char *word = NULL;
    size_t capacity = 0;
    size_t length = 0;
    int ch;

    while ((ch = getchar()) != EOF && ch != '\n' && ch != '\r') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 64 : capacity * 2;
            char *resized = realloc(word, new_capacity);

            if (resized == NULL) {
                free(word);
                return 1;
            }

            word = resized;
            capacity = new_capacity;
        }

        word[length++] = (char)ch;
    }

    if (ferror(stdin)) {
        free(word);
        return 1;
    }

    if (ch == EOF && length == 0) {
        free(word);
        return 0;
    }

    if (length + 1 >= capacity) {
        char *resized = realloc(word, length + 1);

        if (resized == NULL) {
            free(word);
            return 1;
        }

        word = resized;
    }

    word[length] = '\0';
    puts(contains_z(word) ? "match" : "no match");

    free(word);
    return 0;
}