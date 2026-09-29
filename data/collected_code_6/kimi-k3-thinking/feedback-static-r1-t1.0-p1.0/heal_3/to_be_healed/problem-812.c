#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_INPUT_LENGTH 65536

static size_t bounded_strlen(const char *s, size_t max_len)
{
    const char *end = memchr(s, '\0', max_len);
    if (end == NULL) {
        return max_len;
    }
    return (size_t)(end - s);
}

static bool checked_copy(char *dst, size_t dst_capacity, size_t dst_offset,
                         const char *src, size_t copy_len)
{
    if (dst == NULL || src == NULL) {
        return false;
    }
    if (dst_offset > dst_capacity) {
        return false;
    }
    if (copy_len > dst_capacity - dst_offset) {
        return false;
    }
    if (copy_len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst + dst_offset, src, copy_len);
    }
    return true;
}

char *abbreviate_road(const char *input)
{
    static const char word[] = "road";
    static const char replacement[] = "rd.";
    const size_t word_len = sizeof(word) - 1;
    const size_t rep_len = sizeof(replacement) - 1;
    const char *p;
    const char *src;
    char *result;
    size_t count = 0;
    size_t len;
    size_t new_size;
    size_t offset = 0;
    /* Possible weaknesses found:
     *  The scope of the variable 'prefix_len' can be reduced. [variableScope]
     */
    size_t prefix_len;
    size_t tail_len;
    size_t remaining;

    if (input == NULL) {
        return NULL;
    }

    len = bounded_strlen(input, MAX_INPUT_LENGTH);
    if (len == MAX_INPUT_LENGTH) {
        return NULL;
    }

    p = input;
    while ((p = strstr(p, word)) != NULL) {
        count++;
        p += word_len;
    }

    if (rep_len > word_len) {
        if (count > (SIZE_MAX - len - 1) / (rep_len - word_len)) {
            return NULL;
        }
        new_size = len + count * (rep_len - word_len) + 1;
    } else {
        new_size = len - count * (word_len - rep_len) + 1;
    }

    result = malloc(new_size);
    if (result == NULL) {
        return NULL;
    }

    src = input;

    while ((p = strstr(src, word)) != NULL) {
        prefix_len = (size_t)(p - src);

        if (!checked_copy(result, new_size, offset, src, prefix_len)) {
            free(result);
            return NULL;
        }
        offset += prefix_len;

        if (!checked_copy(result, new_size, offset, replacement, rep_len)) {
            free(result);
            return NULL;
        }
        offset += rep_len;

        src = p + word_len;
    }

    remaining = new_size - offset;

    tail_len = bounded_strlen(src, remaining);
    if (tail_len >= remaining) {
        free(result);
        return NULL;
    }

    if (!checked_copy(result, new_size, offset, src, tail_len + 1)) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    const char *input = "Take the road and follow the road to the end of the road.";
    char *output = abbreviate_road(input);

    if (output == NULL) {
        fprintf(stderr, "Error: abbreviation failed\n");
        return EXIT_FAILURE;
    }

    printf("Original:    %s\n", input);
    printf("Abbreviated: %s\n", output);

    free(output);
    output = NULL;

    return EXIT_SUCCESS;
}