#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <inttypes.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

static void report_regex_error(int error_code, const regex_t *regex,
                               const char *message)
{
    size_t size = regerror(error_code, regex, NULL, 0);
    char *buffer = malloc(size);

    if (buffer == NULL) {
        fprintf(stderr, "%s: unable to allocate error buffer\n", message);
        return;
    }

    regerror(error_code, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int find_adverbs(const char *sentence, size_t length)
{
    static const char pattern[] =
        "(^|[^[:alnum:]_])([[:alpha:]]+ly)([^[:alnum:]_]|$)";
    regex_t regex;
    regmatch_t matches[4];
    size_t offset = 0;
    int result;
    int count = 0;

    if (sentence == NULL) {
        return -1;
    }

    if (memchr(sentence, '\0', length + 1) != sentence + length) {
        fprintf(stderr, "Invalid input string\n");
        return -1;
    }

    result = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (result != 0) {
        report_regex_error(result, &regex, "Regex compilation failed");
        return -1;
    }

    while (offset <= length) {
        size_t remaining = length - offset;

        matches[0].rm_so = 0;
        matches[0].rm_eo = (regoff_t)remaining;

        result = regexec(&regex, sentence + offset, 4, matches, 0);
        if (result == REG_NOMATCH) {
            break;
        }

        if (result != 0) {
            report_regex_error(result, &regex, "Regex matching failed");
            regfree(&regex);
            return -1;
        }

        if (matches[2].rm_so < 0 ||
            matches[2].rm_eo < matches[2].rm_so ||
            (uintmax_t)matches[2].rm_eo > (uintmax_t)remaining) {
            fprintf(stderr, "Invalid regex match\n");
            regfree(&regex);
            return -1;
        }

        {
            size_t relative_start = (size_t)matches[2].rm_so;
            size_t relative_end = (size_t)matches[2].rm_eo;
            size_t start = offset + relative_start;
            size_t end = offset + relative_end;
            size_t word_length = end - start;

            if (word_length > (size_t)INT_MAX) {
                fprintf(stderr, "Matched word is too long\n");
                regfree(&regex);
                return -1;
            }

            printf("%.*s: position %zu\n",
                   (int)word_length, sentence + start, start);

            if (count == INT_MAX) {
                fprintf(stderr, "Too many matches\n");
                regfree(&regex);
                return -1;
            }
            ++count;

            if (end <= offset) {
                fprintf(stderr, "Regex did not advance\n");
                regfree(&regex);
                return -1;
            }

            offset = end;
        }
    }

    regfree(&regex);
    return count;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0;
    size_t length;
    ssize_t characters_read;
    int count;

    errno = 0;
    characters_read = getline(&sentence, &capacity, stdin);
    if (characters_read < 0) {
        if (ferror(stdin)) {
            perror("Failed to read input");
        } else {
            fprintf(stderr, "No input provided\n");
        }
        free(sentence);
        return EXIT_FAILURE;
    }

    length = (size_t)characters_read;

    if (length > 0 && sentence[length - 1] == '\n') {
        sentence[--length] = '\0';
        if (length > 0 && sentence[length - 1] == '\r') {
            sentence[--length] = '\0';
        }
    }

    count = find_adverbs(sentence, length);
    free(sentence);

    if (count < 0) {
        return EXIT_FAILURE;
    }

    printf("Total adverbs: %d\n", count);
    return EXIT_SUCCESS;
}