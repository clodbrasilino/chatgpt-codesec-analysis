#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int contains_z(const char *word)
{
    return word != NULL && strchr(word, 'z') != NULL;
}

int main(void)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char word[MAX_INPUT_LENGTH + 1];

    if (fgets(word, sizeof word, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        word[0] = '\0';
    } else {
        size_t length = strcspn(word, "\r\n");

        if (word[length] == '\0' && length == MAX_INPUT_LENGTH) {
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != '\r' && ch != EOF) {
                while ((ch = fgetc(stdin)) != '\n' && ch != '\r' && ch != EOF) {
                }

                if (ferror(stdin)) {
                    return EXIT_FAILURE;
                }

                return EXIT_FAILURE;
            }
        }

        word[length] = '\0';
    }

    puts(contains_z(word) ? "Match" : "No match");
    return EXIT_SUCCESS;
}