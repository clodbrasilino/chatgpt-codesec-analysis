#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int remove_parenthesis_area(char *string)
{
    char *read_position;
    char *write_position;
    size_t depth = 0;

    if (string == NULL) {
        return -1;
    }

    for (read_position = string; *read_position != '\0'; ++read_position) {
        if (*read_position == '(') {
            ++depth;
        } else if (*read_position == ')') {
            if (depth == 0) {
                return -1;
            }
            --depth;
        }
    }

    if (depth != 0) {
        return -1;
    }

    depth = 0;
    write_position = string;

    for (read_position = string; *read_position != '\0'; ++read_position) {
        if (*read_position == '(') {
            ++depth;
        } else if (*read_position == ')') {
            --depth;
        } else if (depth == 0) {
            *write_position++ = *read_position;
        }
    }

    *write_position = '\0';
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        if (fprintf(stderr, "Usage: %s \"text\"\n", argv[0]) < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (remove_parenthesis_area(argv[1]) != 0) {
        if (fprintf(stderr, "Error: unbalanced parentheses\n") < 0) {
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }

    if (puts(argv[1]) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}