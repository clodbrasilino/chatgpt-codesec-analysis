#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static void report_regex_error(const char *message, int status,
                               const regex_t *regex)
{
    size_t size = regerror(status, regex, NULL, 0);
    char *buffer;

    if (size == 0) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    buffer = malloc(size);
    if (buffer == NULL) {
        fprintf(stderr, "%s\n", message);
        return;
    }

    (void)regerror(status, regex, buffer, size);
    fprintf(stderr, "%s: %s\n", message, buffer);
    free(buffer);
}

static int find_adverbs(const char *sentence, size_t sentence_length)
{
    static const char pattern[] = "\\b[A-Za-z]+ly\\b";
    regex_t regex;
    regmatch_t match;
    char *input;
    size_t offset = 0;
    int status;

    if (sentence == NULL || sentence_length == SIZE_MAX) {
        return EXIT_FAILURE;
    }

    input = malloc(sentence_length + 1);
    if (input == NULL) {
        fputs("Memory allocation failed\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < sentence_length; ++i) {
        if (sentence[i] == '\0') {
            fputs("Input contains an embedded null byte\n", stderr);
            free(input);
            return EXIT_FAILURE;
        }
        input[i] = sentence[i];
    }
    input[sentence_length] = '\0';

    status = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (status != 0) {
        report_regex_error("Regex compilation failed", status, &regex);
        free(input);
        return EXIT_FAILURE;
    }

    while (offset < sentence_length) {
        size_t remaining = sentence_length - offset;
        size_t relative_start;
        size_t relative_end;
        size_t start;
        size_t end;
        size_t match_length;

        status = regexec(&regex, input + offset, 1, &match, 0);
        if (status == REG_NOMATCH) {
            break;
        }

        if (status != 0) {
            report_regex_error("Regex matching failed", status, &regex);
            regfree(&regex);
            free(input);
            return EXIT_FAILURE;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            fputs("Invalid regex match\n", stderr);
            regfree(&regex);
            free(input);
            return EXIT_FAILURE;
        }

        relative_start = (size_t)match.rm_so;
        relative_end = (size_t)match.rm_eo;

        if (relative_start > remaining || relative_end > remaining ||
            relative_start > SIZE_MAX - offset ||
            relative_end > SIZE_MAX - offset) {
            fputs("Invalid regex match position\n", stderr);
            regfree(&regex);
            free(input);
            return EXIT_FAILURE;
        }

        start = offset + relative_start;
        end = offset + relative_end;
        match_length = end - start;

        if (match_length > (size_t)INT_MAX) {
            fputs("Regex match is too long to print\n", stderr);
            regfree(&regex);
            free(input);
            return EXIT_FAILURE;
        }

        printf("%.*s: [%zu, %zu)\n", (int)match_length,
               input + start, start, end);

        offset = end;
    }

    regfree(&regex);
    free(input);
    return EXIT_SUCCESS;
}

int main(void)
{
    char *sentence = NULL;
    size_t capacity = 0;
    ssize_t length;
    size_t input_length;
    int result;

    fputs("Enter a sentence: ", stdout);
    fflush(stdout);

    length = getline(&sentence, &capacity, stdin);
    if (length < 0) {
        fputs("Failed to read input\n", stderr);
        free(sentence);
        return EXIT_FAILURE;
    }

    input_length = (size_t)length;

    if (input_length > 0 && sentence[input_length - 1] == '\n') {
        sentence[--input_length] = '\0';
    }

    if (input_length > 0 && sentence[input_length - 1] == '\r') {
        sentence[--input_length] = '\0';
    }

    result = find_adverbs(sentence, input_length);
    free(sentence);
    return result;
}