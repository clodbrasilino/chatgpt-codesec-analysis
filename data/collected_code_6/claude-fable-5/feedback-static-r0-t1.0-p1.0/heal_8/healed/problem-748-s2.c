#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

static int safe_append(char *dst, size_t dst_len, size_t *dst_pos,
                       const char *src, size_t count)
{
    if (dst == NULL || dst_pos == NULL || src == NULL) {
        return -1;
    }
    if (*dst_pos > dst_len) {
        return -1;
    }
    if (count > (dst_len - *dst_pos)) {
        return -1;
    }
    if (count > 0U) {
        size_t i;
        for (i = 0U; i < count; i++) {
            dst[*dst_pos + i] = src[i];
        }
        *dst_pos += count;
    }
    return 0;
}

char *space_capitals(const char *input)
{
    regex_t re;
    regmatch_t match;
    char *result;
    size_t in_len;
    size_t out_len;
    size_t out_pos;
    size_t offset;
    size_t chunk;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    in_len = strnlen(input, MAX_INPUT_LEN);
    if (in_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    rc = regcomp(&re, "[A-Z]", REG_EXTENDED);
    if (rc != 0) {
        return NULL;
    }

    if (in_len > ((SIZE_MAX - 1U) / 2U)) {
        regfree(&re);
        return NULL;
    }

    out_len = (in_len * 2U) + 1U;
    result = malloc(out_len);
    if (result == NULL) {
        regfree(&re);
        return NULL;
    }

    out_pos = 0U;
    offset = 0U;

    while (offset < in_len) {
        rc = regexec(&re, input + offset, 1, &match, 0);
        if (rc != 0) {
            break;
        }

        if (match.rm_so < 0 || match.rm_eo < 0 || match.rm_eo <= match.rm_so) {
            break;
        }

        chunk = (size_t)match.rm_so;
        if ((offset + chunk) >= in_len) {
            break;
        }

        if (out_pos > out_len || chunk > (out_len - out_pos) ||
            (out_len - out_pos - chunk) < 2U) {
            free(result);
            regfree(&re);
            return NULL;
        }

        if (safe_append(result, out_len, &out_pos, input + offset, chunk) != 0) {
            free(result);
            regfree(&re);
            return NULL;
        }

        if ((offset + chunk) > 0U) {
            if (out_pos >= out_len) {
                free(result);
                regfree(&re);
                return NULL;
            }
            result[out_pos] = ' ';
            out_pos++;
        }

        if (out_pos >= out_len) {
            free(result);
            regfree(&re);
            return NULL;
        }
        result[out_pos] = input[offset + chunk];
        out_pos++;

        if ((size_t)match.rm_eo > (in_len - offset)) {
            free(result);
            regfree(&re);
            return NULL;
        }
        offset += (size_t)match.rm_eo;
    }

    if (offset > in_len) {
        free(result);
        regfree(&re);
        return NULL;
    }

    chunk = in_len - offset;
    if (out_pos > out_len || chunk > (out_len - out_pos) ||
        (out_len - out_pos - chunk) < 1U) {
        free(result);
        regfree(&re);
        return NULL;
    }

    if (safe_append(result, out_len, &out_pos, input + offset, chunk) != 0) {
        free(result);
        regfree(&re);
        return NULL;
    }

    if (out_pos >= out_len) {
        free(result);
        regfree(&re);
        return NULL;
    }
    result[out_pos] = '\0';

    regfree(&re);
    return result;
}

int main(void)
{
    const char *test = "HelloWorldThisIsATest";
    char *spaced;

    spaced = space_capitals(test);
    if (spaced == NULL) {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    printf("Input:  %s\n", test);
    printf("Output: %s\n", spaced);

    free(spaced);
    return EXIT_SUCCESS;
}