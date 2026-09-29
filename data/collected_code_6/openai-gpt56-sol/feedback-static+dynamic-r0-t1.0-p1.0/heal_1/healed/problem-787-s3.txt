#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int matches(const char *string)
{
    return string != NULL && strcmp(string, "abbb") == 0;
}

int main(void)
{
    char *input = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int ch;

    while ((ch = getchar()) != '\n' && ch != '\r' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 16 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        return 1;
    }

    if (input == NULL) {
        input = malloc(1);
        if (input == NULL) {
            return 1;
        }
    }

    input[length] = '\0';
    puts(matches(input) ? "Match" : "No match");

    free(input);
    return 0;
}