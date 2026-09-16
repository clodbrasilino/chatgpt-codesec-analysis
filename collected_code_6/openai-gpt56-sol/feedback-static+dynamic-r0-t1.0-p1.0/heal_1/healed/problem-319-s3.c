#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int find_five_letter_words(const char *text)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]{5})([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    int status;

    status = regcomp(&regex, pattern, REG_EXTENDED);
    if (status != 0) {
        char error_message[256];

        regerror(status, &regex, error_message, sizeof error_message);
        fprintf(stderr, "Regex compilation failed: %s\n", error_message);
        return EXIT_FAILURE;
    }

    while (text[offset] != '\0') {
        status = regexec(&regex, text + offset, 4, matches, 0);

        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            char error_message[256];

            regerror(status, &regex, error_message, sizeof error_message);
            fprintf(stderr, "Regex matching failed: %s\n", error_message);
            regfree(&regex);
            return EXIT_FAILURE;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return EXIT_FAILURE;
        }

        printf("%.*s\n",
               (int)(matches[2].rm_eo - matches[2].rm_so),
               text + offset + (size_t)matches[2].rm_so);

        offset += (size_t)matches[2].rm_eo;
    }

    regfree(&regex);
    return EXIT_SUCCESS;
}

int main(int argc, char *const argv[])
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
        size_t length = strlen(argv[i]);
        size_t separator_length = i + 1 < argc ? 1U : 0U;

        if (length > SIZE_MAX - total_length ||
            separator_length > SIZE_MAX - total_length - length) {
            fprintf(stderr, "Input is too large\n");
            return EXIT_FAILURE;
        }

        total_length += length + separator_length;
    }

    text = malloc(total_length);
    if (text == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; ++i) {
        size_t length = strlen(argv[i]);

        memcpy(text + position, argv[i], length);
        position += length;

        if (i + 1 < argc) {
            text[position++] = ' ';
        }
    }

    text[position] = '\0';

    result = find_five_letter_words(text);
    free(text);

    return result;
}