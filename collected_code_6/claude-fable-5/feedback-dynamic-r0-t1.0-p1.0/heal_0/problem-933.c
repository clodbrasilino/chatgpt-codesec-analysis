#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <regex.h>

char *camel_to_snake(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *output;
    size_t in_len;
    size_t out_pos;
    size_t offset;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    in_len = strlen(input);
    output = malloc((in_len * 2U) + 1U);
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
        memcpy(output + out_pos, input + offset, (size_t)match.rm_so);
        out_pos += (size_t)match.rm_so;
        if ((offset + (size_t)match.rm_so) > 0U) {
            output[out_pos] = '_';
            out_pos++;
        }
        output[out_pos] = (char)tolower((unsigned char)input[offset + (size_t)match.rm_so]);
        out_pos++;
        offset += (size_t)match.rm_eo;
    }

    memcpy(output + out_pos, input + offset, in_len - offset);
    out_pos += in_len - offset;
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