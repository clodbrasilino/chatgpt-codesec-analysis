#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

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

        if (match.rm_so < 0 || match.rm_eo < 0) {
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

        memcpy(result + out_pos, input + offset, chunk);
        out_pos += chunk;

        if ((offset + chunk) > 0U) {
            result[out_pos] = ' ';
            out_pos++;
        }

        result[out_pos] = input[offset + chunk];
        out_pos++;
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

    memcpy(result + out_pos, input + offset, chunk);
    out_pos += chunk;
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