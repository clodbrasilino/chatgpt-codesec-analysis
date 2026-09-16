#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *text)
{
    static const char pattern[] = "(^|[^a-z_])([a-z]+_[a-z]+)([^a-z_]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int result;
    int found = 0;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        char message[256];

        regerror(result, &regex, message, sizeof(message));
        fprintf(stderr, "regcomp failed: %s\n", message);
        return -1;
    }

    while ((result = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        regoff_t start = matches[2].rm_so;
        regoff_t end = matches[2].rm_eo;

        if (start < 0 || end < start) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return -1;
        }

        if (printf("%.*s\n", (int)(end - start), cursor + start) < 0) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return -1;
        }

        cursor += end;
        ++found;
    }

    if (result != REG_NOMATCH) {
        char message[256];

        regerror(result, &regex, message, sizeof(message));
        fprintf(stderr, "regexec failed: %s\n", message);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return found;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    if (result < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}