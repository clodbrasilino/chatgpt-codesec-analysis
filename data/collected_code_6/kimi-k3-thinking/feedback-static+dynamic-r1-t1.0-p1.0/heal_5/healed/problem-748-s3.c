#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LENGTH 1048576

static void report_regex_error(int errcode, const regex_t *regex, const char *context)
{
    size_t needed;
    char *errbuf;

    needed = regerror(errcode, regex, NULL, 0);
    if (needed == 0) {
        fprintf(stderr, "%s failed: error code %d\n", context, errcode);
        return;
    }

    errbuf = malloc(needed);
    if (errbuf == NULL) {
        fprintf(stderr, "%s failed: error code %d (unable to allocate error buffer)\n",
                context, errcode);
        return;
    }

    regerror(errcode, regex, errbuf, needed);
    errbuf[needed - 1] = '\0';
    fprintf(stderr, "%s failed: %s\n", context, errbuf);
    free(errbuf);
}

char *add_spaces_before_capitals(const char *input)
{
    regex_t regex;
    regmatch_t match[3];
    const char *pattern = "\\([a-z]\\)\\([A-Z]\\)";
    size_t input_len;
    size_t capacity;
    size_t length;
    char *result;
    const char *cursor;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    input_len = strnlen(input, MAX_INPUT_LENGTH);
    if (input_len == MAX_INPUT_LENGTH) {
        return NULL;
    }
    if (input_len > (SIZE_MAX - 1) / 2) {
        return NULL;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret != 0) {
        report_regex_error(ret, &regex, "regcomp");
        return NULL;
    }

    capacity = input_len * 2 + 1;
    result = malloc(capacity);
    if (result == NULL) {
        fprintf(stderr, "malloc failed\n");
        regfree(&regex);
        return NULL;
    }

    length = 0;
    cursor = input;

    while (*cursor != '\0') {
        size_t cursor_offset;
        size_t cursor_len;
        size_t prefix_len;
        size_t remaining;
        int written;

        ret = regexec(&regex, cursor, 3, match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            report_regex_error(ret, &regex, "regexec");
            free(result);
            regfree(&regex);
            return NULL;
        }

        cursor_offset = (size_t)(cursor - input);
        if (cursor_offset > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        cursor_len = input_len - cursor_offset;

        if (match[1].rm_so < 0 || match[1].rm_eo < 0 ||
            match[1].rm_eo <= match[1].rm_so ||
            (size_t)match[1].rm_eo > cursor_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        prefix_len = (size_t)match[1].rm_eo;
        remaining = capacity - length;

        if (prefix_len > remaining || remaining - prefix_len < 2) {
            fprintf(stderr, "output buffer overflow prevented\n");
            free(result);
            regfree(&regex);
            return NULL;
        }

        written = snprintf(result + length, remaining, "%.*s", (int)prefix_len, cursor);
        if (written < 0 || (size_t)written != prefix_len) {
            fprintf(stderr, "output buffer overflow prevented\n");
            free(result);
            regfree(&regex);
            return NULL;
        }

        length += prefix_len;
        result[length] = ' ';
        length++;
        cursor += prefix_len;
    }

    {
        size_t cursor_offset = (size_t)(cursor - input);
        size_t tail_len;
        size_t remaining;
        int written;

        if (cursor_offset > input_len) {
            free(result);
            regfree(&regex);
            return NULL;
        }

        tail_len = input_len - cursor_offset;
        remaining = capacity - length;

        if (tail_len >= remaining) {
            fprintf(stderr, "output buffer overflow prevented\n");
            free(result);
            regfree(&regex);
            return NULL;
        }

        written = snprintf(result + length, remaining, "%.*s", (int)tail_len, cursor);
        if (written < 0 || (size_t)written != tail_len) {
            fprintf(stderr, "output buffer overflow prevented\n");
            free(result);
            regfree(&regex);
            return NULL;
        }

        length += tail_len;
        result[length] = '\0';
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *input = "HelloWorldThisIsARegexExample";
    char *output;

    output = add_spaces_before_capitals(input);
    if (output == NULL) {
        fprintf(stderr, "Failed to process input string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", input);
    printf("Output: %s\n", output);

    free(output);
    return EXIT_SUCCESS;
}