#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *text)
{
    static const char pattern[] =
        "(^|[^a-z_])([a-z]+(_[a-z]+)+)([^a-z_]|$)";
    regex_t regex;
    regmatch_t matches[5];
    const char *cursor = text;
    int status;
    int count = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char message[256];

        regerror(status, &regex, message, sizeof(message));
        fprintf(stderr, "regcomp failed: %s\n", message);
        return -1;
    }

    while ((status = regexec(&regex, cursor, 5, matches, 0)) == 0) {
        const regoff_t start = matches[2].rm_so;
        const regoff_t end = matches[2].rm_eo;

        if (start < 0 || end <= start) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return -1;
        }

        printf("%.*s\n", (int)(end - start), cursor + start);
        ++count;
        cursor += end;
    }

    if (status != REG_NOMATCH) {
        char message[256];

        regerror(status, &regex, message, sizeof(message));
        fprintf(stderr, "regexec failed: %s\n", message);
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return count;
}

int main(int argc, char *const argv[])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}