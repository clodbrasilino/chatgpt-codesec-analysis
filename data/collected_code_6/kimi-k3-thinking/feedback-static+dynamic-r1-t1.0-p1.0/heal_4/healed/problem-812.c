#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static size_t bounded_strlen(const char *s, size_t max)
{
    size_t n = 0u;

    while (n < max && s[n] != '\0') {
        n++;
    }
    return n;
}

static int bounded_copy(char **dst, size_t *remaining, const char *src, size_t len)
{
    size_t i;

    if (dst == NULL || *dst == NULL || remaining == NULL || src == NULL) {
        return -1;
    }
    if (len == 0u) {
        return 0;
    }
    if (len >= *remaining) {
        return -1;
    }
    for (i = 0u; i < len; i++) {
        (*dst)[i] = src[i];
    }
    *dst += len;
    *remaining -= len;
    return 0;
}

char *abbreviate_road(const char *input, size_t input_max)
{
    const char word[] = "road";
    const char replacement[] = "rd.";
    const size_t word_len = sizeof(word) - 1u;
    const size_t rep_len = sizeof(replacement) - 1u;
    const char *p;
    const char *src;
    char *dst;
    char *result;
    size_t count = 0u;
    size_t len;
    size_t new_size;
    size_t remaining;

    if (input == NULL || input_max == 0u) {
        return NULL;
    }

    len = bounded_strlen(input, input_max);
    if (len == input_max) {
        return NULL;
    }

    p = input;
    while ((p = strstr(p, word)) != NULL) {
        count++;
        p += word_len;
    }

    if (rep_len > word_len) {
        size_t growth = rep_len - word_len;

        if (count > (SIZE_MAX - 1u - len) / growth) {
            return NULL;
        }
        new_size = len + count * growth + 1u;
    } else if (rep_len < word_len) {
        size_t shrink = word_len - rep_len;

        if (count > len / shrink) {
            return NULL;
        }
        new_size = len - count * shrink + 1u;
    } else {
        new_size = len + 1u;
    }

    result = malloc(new_size);
    if (result == NULL) {
        return NULL;
    }

    src = input;
    dst = result;
    remaining = new_size;

    while ((p = strstr(src, word)) != NULL) {
        size_t prefix_len = (size_t)(p - src);

        if (bounded_copy(&dst, &remaining, src, prefix_len) != 0) {
            free(result);
            return NULL;
        }
        if (bounded_copy(&dst, &remaining, replacement, rep_len) != 0) {
            free(result);
            return NULL;
        }

        src = p + word_len;
    }

    {
        size_t tail_len = len - (size_t)(src - input);

        if (bounded_copy(&dst, &remaining, src, tail_len) != 0) {
            free(result);
            return NULL;
        }
        if (remaining == 0u) {
            free(result);
            return NULL;
        }
        *dst = '\0';
    }

    return result;
}

int main(void)
{
    const char input[] = "Take the road and follow the road to the end of the road.";
    char *output = abbreviate_road(input, sizeof(input));

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