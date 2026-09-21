#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

static void report_regex_error(int status, const regex_t *regex,
                               const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);

    if (size == 0) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    char *message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed (unable to allocate error buffer)\n",
                operation);
        return;
    }

    (void)regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int split_at_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    int status;

    if (input == NULL) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, "[[:upper:]]", REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp");
        return EXIT_FAILURE;
    }

    cursor = input;

    while (*cursor != '\0') {
        status = regexec(&regex, cursor, 1, &match, 0);

        if (status == REG_NOMATCH) {
            if (fputs(cursor, stdout) == EOF ||
                fputc('\n', stdout) == EOF) {
                regfree(&regex);
                return EXIT_FAILURE;
            }
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (match.rm_so > 0) {
            size_t prefix_length = (size_t)match.rm_so;

            if (fwrite(cursor, 1, prefix_length, stdout) != prefix_length ||
                fputc('\n', stdout) == EOF) {
                regfree(&regex);
                return EXIT_FAILURE;
            }

            cursor += prefix_length;
        }

        if (fputc((unsigned char)*cursor, stdout) == EOF) {
            regfree(&regex);
            return EXIT_FAILURE;
        }

        ++cursor;

        while (*cursor != '\0') {
            status = regexec(&regex, cursor, 1, &match, 0);

            if (status == REG_NOMATCH) {
                if (fputs(cursor, stdout) == EOF ||
                    fputc('\n', stdout) == EOF) {
                    regfree(&regex);
                    return EXIT_FAILURE;
                }

                while (*cursor != '\0') {
                    ++cursor;
                }
                break;
            }

            if (status != 0) {
                report_regex_error(status, &regex, "regexec");
                regfree(&regex);
                return EXIT_FAILURE;
            }

            if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
                regfree(&regex);
                return EXIT_FAILURE;
            }

            if (match.rm_so > 0) {
                if (fputc('\n', stdout) == EOF) {
                    regfree(&regex);
                    return EXIT_FAILURE;
                }
                break;
            }

            if (fputc((unsigned char)*cursor, stdout) == EOF) {
                regfree(&regex);
                return EXIT_FAILURE;
            }

            ++cursor;
        }

        if (*cursor == '\0' && status != REG_NOMATCH) {
            if (fputc('\n', stdout) == EOF) {
                regfree(&regex);
                return EXIT_FAILURE;
            }
        }
    }

    regfree(&regex);
    return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    return split_at_uppercase(argv[1]);
}