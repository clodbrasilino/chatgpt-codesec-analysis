#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool ensure_capacity(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *resized;

    if (buffer == NULL || *buffer == NULL || capacity == NULL) {
        return false;
    }

    if (required <= *capacity) {
        return true;
    }

    new_capacity = *capacity;

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

    if (pattern == NULL || *pattern == NULL || length == NULL ||
        capacity == NULL || literal == NULL) {
        return false;
    }

    cursor = (const unsigned char *)literal;

    while (*cursor != '\0') {
        bool escaped = strchr(metacharacters, (int)*cursor) != NULL;
        size_t bytes_to_add = escaped ? 2U : 1U;
        size_t required;

        if (*length > SIZE_MAX - bytes_to_add - 1U) {
            return false;
        }

        required = *length + bytes_to_add + 1U;

        if (!ensure_capacity(pattern, capacity, required)) {
            return false;
        }

        if (escaped) {
            (*pattern)[(*length)++] = '\\';
        }

        (*pattern)[(*length)++] = (char)*cursor++;
        (*pattern)[*length] = '\0';
    }

    return true;
}

static char *build_pattern(const char *const literals[], size_t count)
{
    size_t capacity = 64U;
    size_t length = 0U;
    char *pattern;
    size_t i;

    if (literals == NULL || count == 0U) {
        return NULL;
    }

    pattern = malloc(capacity);
    if (pattern == NULL) {
        return NULL;
    }

    pattern[0] = '\0';

    for (i = 0U; i < count; ++i) {
        if (literals[i] == NULL || literals[i][0] == '\0') {
            free(pattern);
            return NULL;
        }

        if (i != 0U) {
            size_t required;

            if (length > SIZE_MAX - 2U) {
                free(pattern);
                return NULL;
            }

            required = length + 2U;

            if (!ensure_capacity(&pattern, &capacity, required)) {
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

static void print_regex_error(const char *operation, int status,
                              const regex_t *regex)
{
    size_t required;
    char *message;

    required = regerror(status, regex, NULL, 0U);
    if (required == 0U) {
        fprintf(stderr, "%s failed\n", operation);
        return;
    }

    message = malloc(required);
    if (message == NULL) {
        fprintf(stderr, "%s failed with status %d\n", operation, status);
        return;
    }

    regerror(status, regex, message, required);
    fprintf(stderr, "%s failed: %s\n", operation, message);
    free(message);
}

static bool print_match(size_t index, const char *match, size_t length)
{
    size_t written = 0U;

    if (printf("Match at index %zu: ", index) < 0) {
        return false;
    }

    while (written < length) {
        size_t remaining = length - written;
        size_t chunk = remaining > (size_t)INT_MAX
                           ? (size_t)INT_MAX
                           : remaining;

        if (printf("%.*s", (int)chunk, match + written) < 0) {
            return false;
        }

        written += chunk;
    }

    return putchar('\n') != EOF;
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
        print_regex_error("regcomp", status, &regex);
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

        if (!print_match(offset + start, cursor + start, length)) {
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
        print_regex_error("regexec", status, &regex);
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