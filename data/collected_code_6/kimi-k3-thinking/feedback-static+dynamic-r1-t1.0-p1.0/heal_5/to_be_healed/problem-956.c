#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH ((size_t)1048576u)

static size_t bounded_string_length(const char *s, size_t max_length)
{
    size_t length = 0u;

    if (s == NULL) {
        return 0u;
    }

    while (length < max_length && s[length] != '\0') {
        length++;
    }

    return length;
}

static char *copy_range(const char *start, size_t length)
{
    char *copy;
    size_t buffer_size;

    if (start == NULL || length == SIZE_MAX) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  buffer_size is assigned 'length+1u' here.
     */
    buffer_size = length + 1u;

    copy = malloc(buffer_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'length>=buffer_size' is always false [knownConditionTrueFalse]
     *  Condition 'length>=buffer_size' is always false
     */
    if (length >= buffer_size) {
        free(copy);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, start, length);
    copy[length] = '\0';

    return copy;
}

void free_split_result(char **parts, size_t count)
{
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0u; i < count; i++) {
        free(parts[i]);
    }
    free(parts);
}

int split_at_uppercase(const char *input, char ***out_parts, size_t *out_count)
{
    regex_t regex;
    regmatch_t match;
    char **parts = NULL;
    size_t count = 0u;
    size_t capacity = 0u;
    char *work = NULL;
    size_t input_length;
    size_t work_size;
    const char *segment_start;
    const char *cursor;
    const char *input_end;
    int finished = 0;

    if (input == NULL || out_parts == NULL || out_count == NULL) {
        return -1;
    }

    *out_parts = NULL;
    *out_count = 0u;

    if (regcomp(&regex, "[A-Z]", REG_EXTENDED) != 0) {
        return -1;
    }

    input_length = bounded_string_length(input, MAX_INPUT_LENGTH);
    /* Possible weaknesses found:
     *  work_size is assigned 'input_length+1u' here.
     */
    work_size = input_length + 1u;

    work = malloc(work_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (work == NULL) {
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition 'input_length>=work_size' is always false [knownConditionTrueFalse]
     *  Condition 'input_length>=work_size' is always false
     */
    if (input_length >= work_size) {
        free(work);
        regfree(&regex);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(work, input, input_length);
    work[input_length] = '\0';

    input_end = work + input_length;
    segment_start = work;
    cursor = work;

    while (!finished) {
        const char *segment_end;
        int status = regexec(&regex, cursor, 1u, &match, 0);

        if (status == 0) {
            const char *match_start = cursor + match.rm_so;
            if (match_start == segment_start) {
                cursor += match.rm_eo;
                continue;
            }
            segment_end = match_start;
            cursor += match.rm_eo;
        } else if (status == REG_NOMATCH) {
            segment_end = input_end;
            finished = 1;
        } else {
            free(work);
            free_split_result(parts, count);
            regfree(&regex);
            return -1;
        }

        if (segment_end > segment_start) {
            if (count == capacity) {
                size_t new_capacity;
                char **grown;

                if (capacity == 0u) {
                    new_capacity = 8u;
                } else {
                    if (capacity > SIZE_MAX / 2u) {
                        free(work);
                        free_split_result(parts, count);
                        regfree(&regex);
                        return -1;
                    }
                    new_capacity = capacity * 2u;
                }

                if (new_capacity > SIZE_MAX / sizeof(*grown)) {
                    free(work);
                    free_split_result(parts, count);
                    regfree(&regex);
                    return -1;
                }

                grown = realloc(parts, new_capacity * sizeof(*grown));
                if (grown == NULL) {
                    free(work);
                    free_split_result(parts, count);
                    regfree(&regex);
                    return -1;
                }
                parts = grown;
                capacity = new_capacity;
            }

            parts[count] = copy_range(segment_start, (size_t)(segment_end - segment_start));
            if (parts[count] == NULL) {
                free(work);
                free_split_result(parts, count);
                regfree(&regex);
                return -1;
            }
            count++;
        }

        segment_start = segment_end;
    }

    regfree(&regex);
    free(work);
    *out_parts = parts;
    *out_count = count;
    return 0;
}

int main(void)
{
    const char *input = "HelloWorldThisIsATest";
    char **parts = NULL;
    size_t count = 0u;
    size_t i;

    if (split_at_uppercase(input, &parts, &count) != 0) {
        fprintf(stderr, "Failed to split the input string.\n");
        return EXIT_FAILURE;
    }

    for (i = 0u; i < count; i++) {
        printf("Part %zu: %s\n", i + 1u, parts[i]);
    }

    free_split_result(parts, count);
    return EXIT_SUCCESS;
}