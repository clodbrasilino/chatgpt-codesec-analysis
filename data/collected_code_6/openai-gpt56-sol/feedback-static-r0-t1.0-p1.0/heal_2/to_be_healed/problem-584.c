#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'SIZE_MAX' is defined in header '<stdint.h>'; this is probably fixable by adding '#include <stdint.h>'
  */

static void report_regex_error(int error_code, const regex_t *regex,
                               const char *prefix)
{
    size_t size = regerror(error_code, regex, NULL, 0);
    char *message = malloc(size);

    if (message == NULL) {
        fprintf(stderr, "%s\n", prefix);
        return;
    }

    regerror(error_code, regex, message, size);
    fprintf(stderr, "%s: %s\n", prefix, message);
    free(message);
}

static int find_adverbs(const char *sentence)
{
    static const char pattern[] =
        "(^|[^[:alpha:]])([[:alpha:]]+ly)([^[:alpha:]]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    int count = 0;
    int result = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);

    if (result != 0) {
        report_regex_error(result, &regex, "Regex compilation failed");
        return -1;
    }

    while (sentence[offset] != '\0') {
        result = regexec(&regex, sentence + offset, 4, matches, 0);

        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex, "Regex execution failed");
            regfree(&regex);
            return -1;
        }

        if (matches[2].rm_so < 0 || matches[2].rm_eo <= matches[2].rm_so) {
            fprintf(stderr, "Unexpected regex match state\n");
            regfree(&regex);
            return -1;
        }

        size_t relative_start = (size_t)matches[2].rm_so;
        size_t relative_end = (size_t)matches[2].rm_eo;

        /* Possible weaknesses found:
         *  use of undeclared identifier 'SIZE_MAX'
         *  'SIZE_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         */
        if (relative_start > SIZE_MAX - offset ||
            /* Possible weaknesses found:
             *  use of undeclared identifier 'SIZE_MAX'
             */
            relative_end > SIZE_MAX - offset) {
            fprintf(stderr, "Input position overflow\n");
            regfree(&regex);
            return -1;
        }

        size_t start = offset + relative_start;
        size_t end = offset + relative_end;
        size_t length = end - start;

        if (length > (size_t)INT_MAX) {
            fprintf(stderr, "Matched word is too long\n");
            regfree(&regex);
            return -1;
        }

        printf("%.*s: position %zu\n", (int)length, sentence + start, start);

        if (count == INT_MAX) {
            fprintf(stderr, "Too many matches\n");
            regfree(&regex);
            return -1;
        }

        ++count;
        offset = end;
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&sentence, &capacity, stdin);

    if (length < 0) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fprintf(stderr, "No input provided\n");
        }

        free(sentence);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (sentence[length - 1] == '\n' || sentence[length - 1] == '\r')) {
        sentence[--length] = '\0';
    }

    int count = find_adverbs(sentence);
    free(sentence);

    if (count < 0) {
        return EXIT_FAILURE;
    }

    printf("Total adverbs: %d\n", count);
    return EXIT_SUCCESS;
}