#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096u

char *insert_spaces(const char *input)
{
    regex_t re;
    regmatch_t match;
    char *output;
    size_t len;
    size_t out_cap;
    size_t out_pos;
    size_t offset;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    out_cap = (len * 2u) + 1u;
    output = (char *)malloc(out_cap);
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
        size_t so;
        size_t start;

        if (match.rm_so < 0) {
            regfree(&re);
            free(output);
            return NULL;
        }

        so = (size_t)match.rm_so;
        start = offset + so;

        if ((start >= len) ||
            (so > (len - offset)) ||
            (out_pos > out_cap) ||
            (so > (out_cap - out_pos)) ||
            ((out_pos + so + 2u) > out_cap)) {
            regfree(&re);
            free(output);
            return NULL;
        }

        memcpy(output + out_pos, input + offset, so);
        out_pos += so;

        if ((start > 0u) && (input[start - 1u] != ' ')) {
            if (out_pos >= out_cap) {
                regfree(&re);
                free(output);
                return NULL;
            }
            output[out_pos] = ' ';
            out_pos++;
        }

        if (out_pos >= out_cap) {
            regfree(&re);
            free(output);
            return NULL;
        }
        output[out_pos] = input[start];
        out_pos++;
        offset = start + 1u;
    }

    if ((offset > len) ||
        (out_pos > out_cap) ||
        ((len - offset) > (out_cap - out_pos)) ||
        ((out_pos + (len - offset) + 1u) > out_cap)) {
        regfree(&re);
        free(output);
        return NULL;
    }

    memcpy(output + out_pos, input + offset, len - offset);
    out_pos += (len - offset);

    if (out_pos >= out_cap) {
        regfree(&re);
        free(output);
        return NULL;
    }
    output[out_pos] = '\0';

    regfree(&re);
    return output;
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