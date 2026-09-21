#include <stdint.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_regex_error(int status, const regex_t *regex, const char *message)
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

static int find_five_letter_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]{5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t text_length = strlen(text);
    int status = regcomp(&regex, pattern, REG_EXTENDED);

    if (status != 0) {
        print_regex_error(status, &regex, "Regex compilation failed");
        return EXIT_FAILURE;
    }

    while (offset < text_length) {
        status = regexec(&regex, text + offset, 4, matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            print_regex_error(status, &regex, "Regex matching failed");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so ||
            (uintmax_t)matches[2].rm_eo > (uintmax_t)(text_length - offset)) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        {
            size_t start = (size_t)matches[2].rm_so;
            size_t length = (size_t)(matches[2].rm_eo - matches[2].rm_so);

            if (length > 0 &&
                fwrite(text + offset + start, 1, length, stdout) != length) {
                fprintf(stderr, "Output failed\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }

            if (fputc('\n', stdout) == EOF) {
                fprintf(stderr, "Output failed\n");
                regfree(&regex);
                return EXIT_FAILURE;
            }
        }

        if (matches[2].rm_eo == 0) {
            ++offset;
        } else {
            offset += (size_t)matches[2].rm_eo;
        }
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    size_t total_length = 1;
    size_t position = 0;
    size_t *lengths;
    char *text;
    int result;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if ((size_t)(argc - 1) > SIZE_MAX / sizeof(*lengths)) {
        fprintf(stderr, "Input is too large\n");
        return EXIT_FAILURE;
    }

    lengths = malloc((size_t)(argc - 1) * sizeof(*lengths));
    if (lengths == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(argv[i]);
        size_t separator = i + 1 < argc ? 1U : 0U;

        if (length > SIZE_MAX - total_length ||
            separator > SIZE_MAX - total_length - length) {
            fprintf(stderr, "Input is too large\n");
            free(lengths);
            return EXIT_FAILURE;
        }

        lengths[i - 1] = length;
        total_length += length + separator;
    }

    text = malloc(total_length);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        free(lengths);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length = lengths[i - 1];

        if (length != 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(text + position, argv[i], length);
            position += length;
        }

        if (i + 1 < argc) {
            text[position++] = ' ';
        }
    }

    text[position] = '\0';
    free(lengths);

    result = find_five_letter_words(text);
    free(text);
    return result;
}