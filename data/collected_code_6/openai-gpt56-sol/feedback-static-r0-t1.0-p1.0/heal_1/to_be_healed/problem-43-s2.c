#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static int find_sequences(const char *text)
{
    const char *pattern = "(^|[^a-z_])([a-z]+_[a-z]+)([^a-z_]|$)";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int result;
    int found = 0;

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char message[256];

        regerror(result, &regex, message, sizeof(message));
        fprintf(stderr, "regcomp failed: %s\n", message);
        return -1;
    }

    while ((result = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        size_t start;
        size_t length;

        if (matches[2].rm_so < 0 || matches[2].rm_eo < matches[2].rm_so) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return -1;
        }

        start = (size_t)matches[2].rm_so;
        length = (size_t)(matches[2].rm_eo - matches[2].rm_so);

        if (printf("%.*s\n", (int)length, cursor + start) < 0) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return -1;
        }

        cursor += matches[2].rm_eo;
        found++;
    }

    if (result != REG_NOMATCH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
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
int main(int argc, char *argv[])
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