#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool reserve_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || capacity == NULL || required == 0U) {
        return false;
    }

    if (required <= *capacity) {
        return true;
    }

    new_capacity = (*capacity == 0U) ? 64U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return false;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return true;
}

static bool append_escaped_literal(char **pattern, size_t *length,
                                   size_t *capacity, const char *literal)
{
    static const char metacharacters[] = ".^$[](){}*+?|\\";
    const unsigned char *cursor;

    if (pattern == NULL || length == NULL || capacity == NULL ||
        literal == NULL) {
        return false;
    }

    cursor = (const unsigned char *)literal;

    while (*cursor != '\0') {
        bool needs_escape =
            strchr(metacharacters, (int)*cursor) != NULL;
        size_t additional = needs_escape ? 2U : 1U;
        size_t required;

        if (*length > SIZE_MAX - additional - 1U) {
            return false;
        }

        required = *length + additional + 1U;

        if (!reserve_buffer(pattern, capacity, required)) {
            return false;
        }

        if (needs_escape) {
            (*pattern)[(*length)++] = '\\';
        }

        (*pattern)[(*length)++] = (char)*cursor;
        (*pattern)[*length] = '\0';
        ++cursor;
    }

    return true;
}

static char *build_pattern(const char *const literals[], size_t count)
{
    char *pattern = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    size_t i;

    if (literals == NULL || count == 0U) {
        return NULL;
    }

    if (!reserve_buffer(&pattern, &capacity, 1U)) {
        return NULL;
    }

    pattern[0] = '\0';

    for (i = 0U; i < count; ++i) {
        if (literals[i] == NULL || literals[i][0] == '\0') {
            free(pattern);
            return NULL;
        }

        if (i != 0U) {
            if (length > SIZE_MAX - 2U ||
                !reserve_buffer(&pattern, &capacity, length + 2U)) {
                free(pattern);
                return NULL;
            }

            pattern[length++] = '|';
            pattern[length] = '\0';
        }

        if (!append_escaped_literal(&pattern, &length, &capacity,
                                    literals[i])) {
            free(pattern);
            return NULL;
        }
    }

    return pattern;
}

static void report_regex_error(int status, const regex_t *regex,
                               const char *operation)
{
    size_t required;
    char *message;

    if (regex == NULL || operation == NULL) {
        return;
    }

    required = regerror(status, regex, NULL, 0U);
    if (required == 0U) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    message = malloc(required);
    if (message == NULL) {
        fprintf(stderr, "%s failed with error code %d\n", operation, status);
        return;
    }

    regerror(status, regex, message, required);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static int find_literal_strings(const char *text,
                                const char *const literals[],
                                size_t literal_count)
{
    regex_t regex;
    regmatch_t match;
    char *pattern;
    const char *cursor;
    size_t offset = 0U;
    int status;
    int result = EXIT_SUCCESS;

    if (text == NULL || literals == NULL || literal_count == 0U) {
        return EXIT_FAILURE;
    }

    pattern = build_pattern(literals, literal_count);
    if (pattern == NULL) {
        return EXIT_FAILURE;
    }

    status = regcomp(&regex, pattern, REG_EXTENDED);
    free(pattern);

    if (status != 0) {
        report_regex_error(status, &regex, "regcomp");
        return EXIT_FAILURE;
    }

    cursor = text;

    for (;;) {
        size_t start;
        size_t end;
        size_t length;

        status = regexec(&regex, cursor, 1U, &match, 0);
        if (status != 0) {
            break;
        }

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            result = EXIT_FAILURE;
            break;
        }

        start = (size_t)match.rm_so;
        end = (size_t)match.rm_eo;
        length = end - start;

        if (length == 0U || offset > SIZE_MAX - start) {
            result = EXIT_FAILURE;
            break;
        }

        printf("Match at index %zu: ", offset + start);
        if (fwrite(cursor + start, 1U, length, stdout) != length ||
            fputc('\n', stdout) == EOF) {
            result = EXIT_FAILURE;
            break;
        }

        if (offset > SIZE_MAX - end) {
            result = EXIT_FAILURE;
            break;
        }

        cursor += end;
        offset += end;
    }

    if (status != 0 && status != REG_NOMATCH) {
        report_regex_error(status, &regex, "regexec");
        result = EXIT_FAILURE;
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *text =
        "C uses printf(), while C++ uses std::cout. Price: $10.";
    const char *literals[] = {
        "printf()",
        "C++",
        "$10"
    };

    return find_literal_strings(
        text,
        literals,
        sizeof(literals) / sizeof(literals[0])
    );
}