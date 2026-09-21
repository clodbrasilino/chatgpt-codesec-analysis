#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void report_regex_error(int error_code, const regex_t *regex)
{
    size_t required;
    char *message;

    required = regerror(error_code, regex, NULL, 0);
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

static int find_sequences(const char *input, size_t input_length, FILE *output)
{
    static const char pattern[] = "[A-Z][a-z]+";
    regex_t regex;
    regmatch_t match;
    char *buffer;
    const char *cursor;
    size_t remaining;
    int result;

    if (input == NULL || output == NULL || input_length == SIZE_MAX) {
        fputs("Invalid function argument\n", stderr);
        return -1;
    }

    if (memchr(input, '\0', input_length) != NULL) {
        fputs("Input contains an embedded null character\n", stderr);
        return -1;
    }

    buffer = malloc(input_length + 1);
    if (buffer == NULL) {
        fputs("Unable to allocate memory for input\n", stderr);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, input, input_length);
    buffer[input_length] = '\0';

    result = regcomp(&regex, pattern, REG_EXTENDED);
    if (result != 0) {
        report_regex_error(result, &regex);
        free(buffer);
        return -1;
    }

    cursor = buffer;
    remaining = input_length;

    for (;;) {
        result = regexec(&regex, cursor, 1, &match, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        if (match.rm_so < 0 ||
            /* Possible weaknesses found:
             *  Assuming that condition 'match.rm_eo<=match.rm_so' is not redundant
             */
            match.rm_eo <= match.rm_so ||
            (uintmax_t)match.rm_eo > (uintmax_t)remaining) {
            fputs("Invalid match offsets returned by regexec\n", stderr);
            regfree(&regex);
            free(buffer);
            return -1;
        }

        {
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
             *  Condition 'fwrite(cursor+start,1,length,output)!=length' is always true [knownConditionTrueFalse]
             *  Condition 'fwrite(cursor+start,1,length,output)!=length' is always true
             */
            if (fwrite(cursor + start, 1, length, output) != length ||
                fputc('\n', output) == EOF) {
                fputs("Failed to write output\n", stderr);
                regfree(&regex);
                free(buffer);
                return -1;
            }

            cursor += end;
            remaining -= end;
        }
    }

    regfree(&regex);
    free(buffer);

    if (fflush(output) == EOF) {
        fputs("Failed to flush output\n", stderr);
        return -1;
    }

    return 0;
}

/* Possible weaknesses found:
 * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
 */
int main(int argc, char *argv[const])
{
    const char *input;
    const char *cursor;
    size_t input_length;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s \"string\"\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
        return EXIT_FAILURE;
    }

    input = argv[1];
    input_length = 0;

    for (cursor = input; *cursor != '\0'; ++cursor) {
        if (input_length == SIZE_MAX) {
            fputs("Input is too long\n", stderr);
            return EXIT_FAILURE;
        }
        ++input_length;
    }

    if (find_sequences(input, input_length, stdout) != 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}