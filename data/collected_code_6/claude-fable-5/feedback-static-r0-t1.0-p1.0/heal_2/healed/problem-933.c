#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096U

static int append_bytes(char *dst, size_t dst_cap, size_t *dst_pos,
                        const char *src, size_t count)
{
    size_t i;

    if ((dst == NULL) || (dst_pos == NULL) || (src == NULL)) {
        return -1;
    }
    if ((*dst_pos > dst_cap) || (count > (dst_cap - *dst_pos))) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        dst[*dst_pos] = src[i];
        (*dst_pos)++;
    }

    return 0;
}

char *camel_to_snake(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    size_t in_len;
    size_t out_cap;
    size_t out_pos;
    size_t offset;
    size_t chunk;
    char lowered;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    in_len = strnlen(input, MAX_INPUT_LEN);
    if (in_len >= MAX_INPUT_LEN) {
        return NULL;
    }

    out_cap = (in_len * 2U) + 1U;
    output = malloc(out_cap);
    if (output == NULL) {
        return NULL;
    }

    rc = regcomp(&regex, "[A-Z]", REG_EXTENDED);
    if (rc != 0) {
        free(output);
        return NULL;
    }

    out_pos = 0U;
    offset = 0U;

    while (offset < in_len) {
        rc = regexec(&regex, input + offset, 1U, &match, 0);
        if (rc == REG_NOMATCH) {
            break;
        }
        if (rc != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        chunk = (size_t)match.rm_so;
        if ((out_pos + chunk + 2U) > out_cap) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if (append_bytes(output, out_cap, &out_pos, input + offset, chunk) != 0) {
            regfree(&regex);
            free(output);
            return NULL;
        }

        if ((offset + chunk) > 0U) {
            output[out_pos] = '_';
            out_pos++;
        }

        lowered = (char)tolower((unsigned char)input[offset + chunk]);
        output[out_pos] = lowered;
        out_pos++;
        offset += (size_t)match.rm_eo;
    }

    chunk = in_len - offset;
    if ((out_pos + chunk + 1U) > out_cap) {
        regfree(&regex);
        free(output);
        return NULL;
    }

    if (append_bytes(output, out_cap, &out_pos, input + offset, chunk) != 0) {
        regfree(&regex);
        free(output);
        return NULL;
    }

    output[out_pos] = '\0';

    regfree(&regex);
    return output;
}

int main(void)
{
    const char *tests[] = {
        "camelCaseString",
        "helloWorldExample",
        "alreadysnake",
        "MixedUPCase"
    };
    size_t i;
    size_t count = sizeof(tests) / sizeof(tests[0]);

    for (i = 0U; i < count; i++) {
        char *result = camel_to_snake(tests[i]);
        if (result == NULL) {
            (void)fprintf(stderr, "Conversion failed for input: %s\n", tests[i]);
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[i], result) < 0) {
            free(result);
            return EXIT_FAILURE;
        }
        free(result);
    }

    return EXIT_SUCCESS;
}