#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

static int count_lists_in_tuple(const char *tuple, size_t *count)
{
    size_t lists = 0;
    size_t square_depth = 0;
    int in_string = 0;
    int escaped = 0;
    char quote = '\0';

    if (tuple == NULL || count == NULL) {
        return -1;
    }

    for (const char *p = tuple; *p != '\0'; ++p) {
        unsigned char ch = (unsigned char)*p;

        if (in_string) {
            if (escaped) {
                escaped = 0;
            } else if (ch == '\\') {
                escaped = 1;
            } else if (ch == (unsigned char)quote) {
                in_string = 0;
            }
            continue;
        }

        if (ch == '\'' || ch == '"') {
            in_string = 1;
            quote = (char)ch;
        } else if (ch == '[') {
            if (square_depth == 0) {
                ++lists;
            }
            ++square_depth;
        } else if (ch == ']') {
            if (square_depth == 0) {
                return -1;
            }
            --square_depth;
        }
    }

    if (in_string || square_depth != 0) {
        return -1;
    }

    *count = lists;
    return 0;
}

int main(void)
{
    char tuple[4096];
    size_t count = 0;

    if (fgets(tuple, sizeof tuple, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(tuple, '\n') == NULL && !feof(stdin)) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (count_lists_in_tuple(tuple, &count) != 0) {
        fputs("Invalid tuple representation.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%zu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}