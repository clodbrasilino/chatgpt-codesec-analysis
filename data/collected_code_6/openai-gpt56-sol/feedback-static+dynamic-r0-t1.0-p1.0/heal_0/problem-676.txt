#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int remove_non_alphanumeric(char *string)
{
    regex_t regex;
    regmatch_t match;
    size_t read_pos = 0;
    size_t write_pos = 0;
    int result;

    if (string == NULL) {
        return -1;
    }

    result = regcomp(&regex, "[[:alnum:]]", REG_EXTENDED);
    if (result != 0) {
        return -1;
    }

    while (string[read_pos] != '\0') {
        result = regexec(&regex, string + read_pos, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0 || match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        string[write_pos++] = string[read_pos + (size_t)match.rm_so];
        read_pos += (size_t)match.rm_eo;
    }

    string[write_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    char input[4096];

    if (fgets(input, sizeof input, stdin) == NULL) {
        if (ferror(stdin)) {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        return EXIT_FAILURE;
    }

    input[strcspn(input, "\n")] = '\0';

    if (remove_non_alphanumeric(input) != 0) {
        return EXIT_FAILURE;
    }

    if (puts(input) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}