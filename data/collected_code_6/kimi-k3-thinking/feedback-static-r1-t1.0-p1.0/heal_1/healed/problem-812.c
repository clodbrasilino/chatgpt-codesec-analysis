#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_INPUT_LENGTH 65536

static size_t bounded_strlen(const char *s, size_t max_len)
{
    const char *end = memchr(s, '\0', max_len);
    if (end == NULL) {
        return max_len;
    }
    return (size_t)(end - s);
}

char *abbreviate_road(const char *input)
{
    static const char word[] = "road";
    static const char replacement[] = "rd.";
    const size_t word_len = sizeof(word) - 1;
    const size_t rep_len = sizeof(replacement) - 1;
    const char *p;
    const char *src;
    char *dst;
    char *result;
    size_t count = 0;
    size_t len;
    size_t new_size;
    size_t capacity;
    size_t tail_len;

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
    dst = result;
    capacity = new_size;

    while ((p = strstr(src, word)) != NULL) {
        size_t prefix_len = (size_t)(p - src);

        if (prefix_len >= capacity) {
            free(result);
            return NULL;
        }
        memcpy(dst, src, prefix_len);
        dst += prefix_len;
        capacity -= prefix_len;

        if (rep_len >= capacity) {
            free(result);
            return NULL;
        }
        memcpy(dst, replacement, rep_len);
        dst += rep_len;
        capacity -= rep_len;

        src = p + word_len;
    }

    tail_len = bounded_strlen(src, capacity);
    if (tail_len >= capacity) {
        free(result);
        return NULL;
    }
    memcpy(dst, src, tail_len + 1);

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