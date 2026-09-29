#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool append_escaped_literal(char **pattern, size_t *length, size_t *capacity,
                                   const char *literal)
{
    static const char metacharacters[] = ".^$[](){}*+?|\\";
    const unsigned char *cursor = (const unsigned char *)literal;

    while (*cursor != '\0') {
        size_t required = *length + 1U;

        if (strchr(metacharacters, (int)*cursor) != NULL) {
            if (required == SIZE_MAX) {
                return false;
            }
            ++required;
        }

        if (required == SIZE_MAX) {
            return false;
        }
        ++required;

        if (required > *capacity) {
            size_t new_capacity = *capacity;
            char *resized;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2U) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2U;
            }

            resized = realloc(*pattern, new_capacity);
            if (resized == NULL) {
                return false;
            }

            *pattern = resized;
            *capacity = new_capacity;
        }

        if (strchr(metacharacters, (int)*cursor) != NULL) {
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
            if (length + 2U > capacity) {
                size_t new_capacity;
                char *resized;

                if (capacity > SIZE_MAX / 2U) {
                    free(pattern);
                    return NULL;
                }

                new_capacity = capacity * 2U;
                resized = realloc(pattern, new_capacity);
                if (resized == NULL) {
                    free(pattern);
                    return NULL;
                }

                pattern = resized;
                capacity = new_capacity;
            }

            pattern[length++] = '|';
            pattern[length] = '\0';
        }

        if (!append_escaped_literal(&pattern, &length, &capacity, literals[i])) {
            free(pattern);
            return NULL;
        }
    }

    return pattern;
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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[256];
        regerror(status, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "regcomp failed: %s\n", error_buffer);
        return EXIT_FAILURE;
    }

    cursor = text;

    while ((status = regexec(&regex, cursor, 1U, &match, 0)) == 0) {
        size_t start;
        size_t length;

        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            result = EXIT_FAILURE;
            break;
        }

        start = (size_t)match.rm_so;
        length = (size_t)(match.rm_eo - match.rm_so);

        if (length == 0U) {
            result = EXIT_FAILURE;
            break;
        }

        printf("Match at index %zu: %.*s\n",
               offset + start,
               (int)length,
               cursor + start);

        cursor += (size_t)match.rm_eo;
        offset += (size_t)match.rm_eo;
    }

    if (status != 0 && status != REG_NOMATCH) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char error_buffer[256];
        regerror(status, &regex, error_buffer, sizeof(error_buffer));
        fprintf(stderr, "regexec failed: %s\n", error_buffer);
        result = EXIT_FAILURE;
    }

    regfree(&regex);
    return result;
}

int main(void)
{
    const char *text = "C uses printf(), while C++ uses std::cout. Price: $10.";
    const char *literals[] = {"printf()", "C++", "$10"};

    return find_literal_strings(
        text,
        literals,
        sizeof(literals) / sizeof(literals[0])
    );
}