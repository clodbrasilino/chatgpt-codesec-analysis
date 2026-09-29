#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

static char *copy_range(const char *start, size_t length)
{
    char *copy;
    size_t i;

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }
    for (i = 0; i < length; i++) {
        copy[i] = start[i];
    }
    copy[length] = '\0';
    return copy;
}

void free_split_result(char **parts, size_t count)
{
    size_t i;
    if (parts == NULL) {
        return;
    }
    for (i = 0; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}

int split_at_uppercase(const char *input, char ***out_parts, size_t *out_count)
{
    regex_t regex;
    regmatch_t match;
    char **parts = NULL;
    size_t count = 0;
    size_t capacity = 0;
    const char *segment_start;
    const char *cursor;
    int finished = 0;

    if (input == NULL || out_parts == NULL || out_count == NULL) {
        return -1;
    }

    *out_parts = NULL;
    *out_count = 0;

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return -1;
    }

    segment_start = input;
    cursor = input;

    while (!finished) {
        const char *segment_end;
        int status = regexec(&regex, cursor, 1, &match, 0);

        if (status == 0) {
            const char *match_start = cursor + match.rm_so;
            if (match_start == segment_start) {
                cursor += match.rm_eo;
                continue;
            }
            segment_end = match_start;
            cursor += match.rm_eo;
        } else if (status == REG_NOMATCH) {
            segment_end = segment_start;
            while (*segment_end != '\0') {
                segment_end++;
            }
            finished = 1;
        } else {
            free_split_result(parts, count);
            regfree(&regex);
            return -1;
        }

        if (segment_end > segment_start) {
            if (count == capacity) {
                size_t new_capacity = (capacity == 0) ? 8u : capacity * 2u;
                char **grown;
                if (new_capacity < capacity) {
                    free_split_result(parts, count);
                    regfree(&regex);
                    return -1;
                }
                grown = realloc(parts, new_capacity * sizeof(*grown));
                if (grown == NULL) {
                    free_split_result(parts, count);
                    regfree(&regex);
                    return -1;
                }
                parts = grown;
                capacity = new_capacity;
            }

            parts[count] = copy_range(segment_start, (size_t)(segment_end - segment_start));
            if (parts[count] == NULL) {
                free_split_result(parts, count);
                regfree(&regex);
                return -1;
            }
            count++;
        }

        segment_start = segment_end;
    }

    regfree(&regex);
    *out_parts = parts;
    *out_count = count;
    return 0;
}

int main(void)
{
    const char *input = "HelloWorldThisIsATest";
    char **parts = NULL;
    size_t count = 0;
    size_t i;

    if (split_at_uppercase(input, &parts, &count) != 0) {
        fprintf(stderr, "Failed to split the input string.\n");
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; i++) {
        printf("Part %zu: %s\n", i + 1, parts[i]);
    }

    free_split_result(parts, count);
    return EXIT_SUCCESS;
}