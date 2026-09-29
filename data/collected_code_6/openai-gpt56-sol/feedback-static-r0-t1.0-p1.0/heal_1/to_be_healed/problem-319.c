#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_five_character_words(const char *text)
{
    const char *pattern = "(^|[^[:alnum:]_])([[:alpha:]]{5})($|[^[:alnum:]_])";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    int status;

    if (text == NULL) {
        return 1;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char message[256];
        regerror(status, &regex, message, sizeof(message));
        fprintf(stderr, "regcomp failed: %s\n", message);
        return 1;
    }

    while (text[offset] != '\0') {
        status = regexec(&regex, text + offset, 4, matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char message[256];
            regerror(status, &regex, message, sizeof(message));
            fprintf(stderr, "regexec failed: %s\n", message);
            regfree(&regex);
            return 1;
        }

        if (matches[2].rm_so < 0 || matches[2].rm_eo < matches[2].rm_so) {
            regfree(&regex);
            return 1;
        }

        printf("%.*s\n",
               (int)(matches[2].rm_eo - matches[2].rm_so),
               text + offset + (size_t)matches[2].rm_so);

        offset += (size_t)matches[2].rm_eo;
    }

    regfree(&regex);
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    size_t total_length = 1;
    size_t position = 0;
    char *text;
    int result;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <text>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(argv[i]);

        if (length > SIZE_MAX - total_length - 1) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        total_length += length;
        if (i + 1 < argc) {
            ++total_length;
        }
    }

    text = malloc(total_length);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t length = strlen(argv[i]);

        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(text + position, argv[i], length);
        position += length;

        if (i + 1 < argc) {
            text[position++] = ' ';
        }
    }
    text[position] = '\0';

    result = find_five_character_words(text);
    free(text);

    return result == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}