#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *message)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *buffer = malloc(size);

    if (buffer == NULL) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    regerror(status, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int find_sequences(const char *text)
{
    static const char pattern[] =
        "(^|[^a-z_])([a-z]+_[a-z]+)($|[^a-z_])";
    regex_t regex;
    regmatch_t matches[4];
    const char *cursor = text;
    int status;
    int found = 0;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp failed");
        return -1;
    }

    while ((status = regexec(&regex, cursor, 4, matches, 0)) == 0) {
        regoff_t match_start = matches[2].rm_so;
        regoff_t match_end = matches[2].rm_eo;
        size_t length;

        if (match_start < 0 || match_end <= match_start) {
            fprintf(stderr, "Invalid regular expression match\n");
            regfree(&regex);
            return -1;
        }

        length = (size_t)(match_end - match_start);

        if (fwrite(cursor + (size_t)match_start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fprintf(stderr, "Output failed\n");
            regfree(&regex);
            return -1;
        }

        cursor += (size_t)match_end;

        if (found == INT_MAX) {
            fprintf(stderr, "Too many matches\n");
            regfree(&regex);
            return -1;
        }

        ++found;
    }

    if (status != REG_NOMATCH) {
        report_regex_error(status, &regex, "regexec failed");
        regfree(&regex);
        return -1;
    }

    regfree(&regex);
    return found;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *const argv[const])
{
    int result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <text>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    result = find_sequences(argv[1]);
    return result < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}