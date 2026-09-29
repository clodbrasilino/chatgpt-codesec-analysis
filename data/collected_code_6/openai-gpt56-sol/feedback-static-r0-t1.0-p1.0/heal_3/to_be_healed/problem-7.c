#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
/* Possible weaknesses found:
 *  include '<string.h>' or provide a declaration of 'strlen'
 */
#include <stdint.h>

static void report_regex_error(int status, const regex_t *regex, const char *operation)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *message;

    if (size == 0 || size > SIZE_MAX) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    message = malloc(size);
    if (message == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    (void)regerror(status, regex, message, size);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int find_words(const char *text)
{
    static const char pattern[] = "[[:alnum:]_]{4,}";
    regex_t regex;
    const char *cursor = text;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        report_regex_error(status, &regex, "regcomp");
        return EXIT_FAILURE;
    }

    while (*cursor != '\0') {
        regmatch_t match;

        status = regexec(&regex, cursor, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error(status, &regex, "regexec");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
             */
            match.rm_eo <= match.rm_so) {
            fprintf(stderr, "Invalid regular-expression match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        {
            /* Possible weaknesses found:
             *  include the header <string.h> or explicitly provide a declaration for 'strlen'
             * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
             *  implicit declaration of function 'strlen' [-Wimplicit-function-declaration]
             *  call to undeclared library function 'strlen' with type 'unsigned long (const char *)'; ISO C99 and later do not support implicit function declarations [-Wimplicit-function-declaration]
             */
            size_t remaining = strlen(cursor);
            /* Possible weaknesses found:
             *  start is assigned '(unsigned long)match.rm_so' here.
             */
            size_t start = (size_t)match.rm_so;
            /* Possible weaknesses found:
             *  Assignment 'end=(unsigned long)match.rm_eo', assigned value is less than symbolic=start
             */
            size_t end = (size_t)match.rm_eo;
            size_t length;

            /* Possible weaknesses found:
             *  Condition 'end<=start' is always true [knownConditionTrueFalse]
             *  Condition 'end<=start' is always true
             */
            if (start > remaining || end > remaining || end <= start) {
                fprintf(stderr, "Invalid regular-expression match\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }

            length = end - start;

            if (fwrite(cursor + start, sizeof(char), length, stdout) != length) {
                fprintf(stderr, "Failed to write output\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }

            if (fputc('\n', stdout) == EOF) {
                fprintf(stderr, "Failed to write output\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }

            cursor += end;
        }
    }

    regfree(&regex);

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Failed to write output\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
    const char *program =
        argc > 0 && argv[0] != NULL ? argv[0] : "program";

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"text\"\n", program);
        return EXIT_FAILURE;
    }

    return find_words(argv[1]);
}