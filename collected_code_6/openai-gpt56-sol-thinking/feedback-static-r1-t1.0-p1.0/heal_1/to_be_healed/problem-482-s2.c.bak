#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t size = regerror(error_code, regex, NULL, 0);
    char *message = malloc(size);

    if (message == NULL) {
        fputs("Unable to allocate memory for regex error message\n", stderr);
        return;
    }

    regerror(error_code, regex, message, size);
    fprintf(stderr, "Regex error: %s\n", message);
    free(message);
}

int find_sequences(const char *text)
{
    regex_t regex = {0};
    regmatch_t match;
    const char *cursor;
    size_t remaining;
    int result;

    if (text == NULL) {
        fputs("Input string is NULL\n", stderr);
        return -1;
    }

    result = regcomp(&regex, "[A-Z][a-z]+", REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        return -1;
    }

    cursor = text;
    remaining = strlen(text);

    while (remaining > 0) {
        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
         */
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            fputs("Invalid regex match range\n", stderr);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         *  start is assigned '(unsigned long)match.rm_so' here.
         */
        size_t start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'end=(unsigned long)match.rm_eo', assigned value is less than symbolic=start
         */
        size_t end = (size_t)match.rm_eo;
        /* Possible weaknesses found:
         *  Assignment 'length=end-start', assigned value is less than 0
         */
        size_t length = end - start;

        /* Possible weaknesses found:
         *  Condition 'fwrite(cursor+start,1,length,stdout)!=length' is always true
         *  Condition 'fwrite(cursor+start,1,length,stdout)!=length' is always true [knownConditionTrueFalse]
         */
        if (fwrite(cursor + start, 1, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            fputs("Failed to write output\n", stderr);
            regfree(&regex);
            return -1;
        }

        cursor += end;
        remaining -= end;
    }

    regfree(&regex);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1]) != 0) {
        return EXIT_FAILURE;
    }

    if (fflush(stdout) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}