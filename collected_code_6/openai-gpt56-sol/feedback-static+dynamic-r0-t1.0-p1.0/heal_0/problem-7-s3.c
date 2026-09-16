#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static int print_matching_words(const char *text)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    const char pattern[] = "[[:alnum:]_]{4,}";

    if (text == NULL) {
        return -1;
    }

    if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
        return -1;
    }

    cursor = text;

    while (*cursor != '\0') {
        int result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        {
            size_t length = (size_t)(match.rm_eo - match.rm_so);

            if (fwrite(cursor + match.rm_so, 1, length, stdout) != length ||
                fputc('\n', stdout) == EOF) {
                regfree(&regex);
                return -1;
            }
        }

        cursor += match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return EXIT_FAILURE;
    }

    if (print_matching_words(line) != 0) {
        free(line);
        return EXIT_FAILURE;
    }

    free(line);
    return EXIT_SUCCESS;
}