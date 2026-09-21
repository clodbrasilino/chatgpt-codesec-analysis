#include <stdio.h>
#include <stdlib.h>

static void print_ascii_values(const char *string)
{
    if (string == NULL) {
        return;
    }

    while (*string != '\0') {
        if (printf("%u\n", (unsigned int)(unsigned char)*string) < 0) {
            return;
        }
        ++string;
    }
}

int main(void)
{
    char *string = NULL;
    size_t length = 0;
    size_t capacity = 0;
    int character;

    while ((character = fgetc(stdin)) != EOF && character != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_string;

            if (new_capacity <= capacity) {
                free(string);
                return 1;
            }

            new_string = realloc(string, new_capacity);
            if (new_string == NULL) {
                free(string);
                return 1;
            }

            string = new_string;
            capacity = new_capacity;
        }

        string[length++] = (char)character;
    }

    if (character == EOF && ferror(stdin)) {
        perror("fgetc");
        free(string);
        return 1;
    }

    if (string == NULL) {
        string = malloc(1);
        if (string == NULL) {
            return 1;
        }
    }

    string[length] = '\0';
    print_ascii_values(string);
    free(string);

    return ferror(stdout) ? 1 : 0;
}