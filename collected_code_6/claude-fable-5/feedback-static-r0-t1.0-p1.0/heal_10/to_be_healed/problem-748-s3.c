#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096u

static int safe_copy(char *dst, size_t dst_size, size_t dst_pos,
                     const char *src, size_t src_len, size_t src_pos,
                     size_t count)
{
    if (dst == NULL || src == NULL) {
        return -1;
    }
    if (count == 0u) {
        return 0;
    }
    if (dst_pos >= dst_size) {
        return -1;
    }
    if (count > (dst_size - dst_pos)) {
        return -1;
    }
    if (src_pos > src_len) {
        return -1;
    }
    if (count > (src_len - src_pos)) {
        return -1;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(dst + dst_pos, src + src_pos, count);
    return 0;
}

static char *insert_spaces(const char *input)
{
    regex_t re;
    regmatch_t match;
    char *output;
    size_t len;
    size_t out_size;
    size_t out_pos;
    size_t offset;
    size_t tail;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    if (len > ((SIZE_MAX - 1u) / 2u)) {
        return NULL;
    }

    out_size = (len * 2u) + 1u;
    output = (char *)malloc(out_size);
    if (output == NULL) {
        return NULL;
    }

    rc = regcomp(&re, "[A-Z]", REG_EXTENDED);
    if (rc != 0) {
        free(output);
        return NULL;
    }

    out_pos = 0u;
    offset = 0u;

    while ((offset < len) &&
           (regexec(&re, input + offset, 1u, &match, 0) == 0)) {
        size_t start;
        size_t chunk;

        if (match.rm_so < 0) {
            goto fail;
        }

        start = offset + (size_t)match.rm_so;
        chunk = (size_t)match.rm_so;

        if (start >= len) {
            goto fail;
        }

        if (out_pos >= out_size) {
            goto fail;
        }

        if ((chunk + 2u) > (out_size - out_pos)) {
            goto fail;
        }

        if (chunk > 0u) {
            if (safe_copy(output, out_size, out_pos,
                          input, len, offset, chunk) != 0) {
                goto fail;
            }
            out_pos += chunk;
        }

        if ((start > 0u) && (input[start - 1u] != ' ')) {
            if (out_pos >= out_size) {
                goto fail;
            }
            output[out_pos] = ' ';
            out_pos++;
        }

        if (out_pos >= out_size) {
            goto fail;
        }
        output[out_pos] = input[start];
        out_pos++;
        offset = start + 1u;
    }

    if (offset > len) {
        goto fail;
    }

    tail = len - offset;

    if (out_pos >= out_size) {
        goto fail;
    }

    if ((tail + 1u) > (out_size - out_pos)) {
        goto fail;
    }

    if (tail > 0u) {
        if (safe_copy(output, out_size, out_pos,
                      input, len, offset, tail) != 0) {
            goto fail;
        }
        out_pos += tail;
    }

    if (out_pos >= out_size) {
        goto fail;
    }
    output[out_pos] = '\0';

    regfree(&re);
    return output;

fail:
    regfree(&re);
    free(output);
    return NULL;
}

int main(void)
{
    const char *text = "HelloWorldThisIsATestString";
    char *result;

    result = insert_spaces(text);
    if (result == NULL) {
        (void)fprintf(stderr, "Error: failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}