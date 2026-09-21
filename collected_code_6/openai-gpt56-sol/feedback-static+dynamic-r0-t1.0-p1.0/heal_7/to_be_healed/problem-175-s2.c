#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  test case 0 failed: expected True, got 0
  */

static bool is_valid_parentheses(const char *str)
{
    if (str == NULL) {
        return false;
    }

    size_t balance = 0;

    for (; *str != '\0'; ++str) {
        if (*str == '(') {
            ++balance;
        } else if (*str == ')') {
            if (balance == 0) {
                return false;
            }
            --balance;
        } else {
            return false;
        }
    }

    return balance == 0;
}

static char *read_line(FILE *stream)
{
    if (stream == NULL) {
        return NULL;
    }

    size_t capacity = 128;
    size_t length = 0;
    char *line = malloc(capacity);

    if (line == NULL) {
        return NULL;
    }

    for (;;) {
        if (length + 1 == capacity) {
            size_t new_capacity = capacity * 2;
            char *resized = realloc(line, new_capacity);

            if (resized == NULL) {
                free(line);
                return NULL;
            }

            line = resized;
            capacity = new_capacity;
        }

        if (fgets(line + length, (int)(capacity - length), stream) == NULL) {
            if (ferror(stream)) {
                free(line);
                return NULL;
            }
            break;
        }

        while (line[length] != '\0' && line[length] != '\n') {
            ++length;
        }

        if (line[length] == '\n') {
            line[length] = '\0';
            break;
        }
    }

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    return line;
}

int main(void)
{
    char *input = read_line(stdin);

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    bool valid = is_valid_parentheses(input);
    free(input);

    if (printf("%s\n", valid ? "True" : "False") < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}