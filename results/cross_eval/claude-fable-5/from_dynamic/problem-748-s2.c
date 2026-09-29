#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *space_capitals(const char *input)
{
    regex_t re;
    regmatch_t match;
    char *result;
    size_t in_len;
    size_t out_pos;
    size_t offset;
    int rc;

    if (input == NULL) {
        return NULL;
    }

    rc = regcomp(&re, "[A-Z]", REG_EXTENDED);
    if (rc != 0) {
        return NULL;
    }

    in_len = strlen(input);
    result = malloc((in_len * 2U) + 1U);
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
        memcpy(result + out_pos, input + offset, (size_t)match.rm_so);
        out_pos += (size_t)match.rm_so;
        if ((offset + (size_t)match.rm_so) > 0U) {
            result[out_pos] = ' ';
            out_pos++;
        }
        result[out_pos] = input[offset + (size_t)match.rm_so];
        out_pos++;
        offset += (size_t)match.rm_eo;
    }

    memcpy(result + out_pos, input + offset, in_len - offset);
    out_pos += in_len - offset;
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