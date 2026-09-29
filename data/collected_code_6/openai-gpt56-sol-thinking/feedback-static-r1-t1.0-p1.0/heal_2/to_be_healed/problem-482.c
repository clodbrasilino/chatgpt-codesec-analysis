#include <inttypes.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t required = regerror(error_code, regex, NULL, 0);
    char *message;

    if (required == 0) {
        fputs("Unknown regular expression error\n", stderr);
        return;
    }

    message = malloc(required);
    if (message == NULL) {
        fputs("Unable to allocate memory for the error message\n", stderr);
        return;
    }

    regerror(error_code, regex, message, required);
    fprintf(stderr, "Regular expression error: %s\n", message);
    free(message);
}

static int find_sequences(const char *input, FILE *output)
{
    static const char pattern[] = "[A-Z][a-z]+";
    regex_t regex;
    const char *cursor;
    int result;

    if (input == NULL || output == NULL) {
        fputs("Invalid function argument\n", stderr);
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        return -1;
    }

    cursor = input;

    for (;;) {
        regmatch_t match;
        size_t start;
        size_t end;
        size_t length;

        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
             */
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_so > (uintmax_t)SIZE_MAX ||
            (uintmax_t)match.rm_eo > (uintmax_t)SIZE_MAX) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         *  start is assigned '(unsigned long)match.rm_so' here.
         */
        start = (size_t)match.rm_so;
        /* Possible weaknesses found:
         *  Assignment 'end=(unsigned long)match.rm_eo', assigned value is less than symbolic=start
         */
        end = (size_t)match.rm_eo;
        /* Possible weaknesses found:
         *  Assignment 'length=end-start', assigned value is less than 0
         */
        length = end - start;

        /* Possible weaknesses found:
         *  Condition 'fwrite(cursor+start,1,length,output)!=length' is always true [knownConditionTrueFalse]
         *  Condition 'fwrite(cursor+start,1,length,output)!=length' is always true
         */
        if (fwrite(cursor + start, 1, length, output) != length ||
            fputc('\n', output) == EOF) {
            fputs("Failed to write output\n", stderr);
            regfree(&regex);
            return -1;
        }

        cursor += end;
    }

    regfree(&regex);

    if (fflush(output) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return -1;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    const char *program_name =
        argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n", program_name);
        return EXIT_FAILURE;
    }

    if (find_sequences(argv[1], stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}