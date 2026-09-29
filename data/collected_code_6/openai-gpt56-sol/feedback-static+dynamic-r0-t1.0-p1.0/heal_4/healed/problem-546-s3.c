#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *find_last_char(const char *str, int ch)
{
    const char *last = NULL;
    unsigned char target = (unsigned char)ch;

    if (str == NULL) {
        return NULL;
    }

    do {
        if ((unsigned char)*str == target) {
            last = str;
        }
    } while (*str++ != '\0');

    return last;
}

static int read_line(char **line)
{
    char *buffer = NULL;
    size_t capacity = 128;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return 0;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *temporary;

            if (capacity > (size_t)-1 / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            temporary = realloc(buffer, new_capacity);
            if (temporary == NULL) {
                free(buffer);
                return 0;
            }

            buffer = temporary;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *character_line = NULL;
    const char *result;

    if (!read_line(&input)) {
        fputs("Failed to read the string.\n", stderr);
        return 1;
    }

    if (!read_line(&character_line) ||
        character_line[0] == '\0' ||
        character_line[1] != '\0') {
        fputs("Failed to read the character.\n", stderr);
        free(character_line);
        free(input);
        return 1;
    }

    result = find_last_char(input, (unsigned char)character_line[0]);

    if (result != NULL) {
        printf("%td\n", result - input);
    } else {
        puts("Character not found.");
    }

    free(character_line);
    free(input);
    return 0;
}