#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            free(result);
            regfree(&re);
            return NULL;
        }

        chunk = (size_t)match.rm_so;

        /* Possible weaknesses found:
         *  Assuming that condition '(offset+chunk)>=in_len' is not redundant
         */
        if ((offset + chunk) >= in_len) {
            free(result);
            regfree(&re);
            return NULL;
        }

        /* Possible weaknesses found:
         *  Assuming that condition '(out_pos+chunk+2U)>out_len' is not redundant
         *  Assuming condition is false
         */
        if ((out_pos + chunk + 2U) > out_len) {
            free(result);
            regfree(&re);
            return NULL;
        }

        if (chunk > 0U) {
            /* Possible weaknesses found:
             *  Condition '(out_pos+chunk)>out_len' is always false
             *  Condition '(out_pos+chunk)>out_len' is always false [knownConditionTrueFalse]
             */
            if ((out_pos + chunk) > out_len ||
                /* Possible weaknesses found:
                 *  Condition '(offset+chunk)>in_len' is always false [knownConditionTrueFalse]
                 *  Condition '(offset+chunk)>in_len' is always false
                 */
                (offset + chunk) > in_len) {
                free(result);
                regfree(&re);
                return NULL;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out_pos, input + offset, chunk);
            out_pos += chunk;
        }

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
    /* Possible weaknesses found:
     *  Assuming that condition '(out_pos+chunk+1U)>out_len' is not redundant
     */
    if ((out_pos + chunk + 1U) > out_len) {
        free(result);
        regfree(&re);
        return NULL;
    }

    if (chunk > 0U) {
        /* Possible weaknesses found:
         *  Condition '(out_pos+chunk)>out_len' is always false
         *  Condition '(out_pos+chunk)>out_len' is always false [knownConditionTrueFalse]
         */
        if ((out_pos + chunk) > out_len ||
            (offset + chunk) > in_len) {
            free(result);
            regfree(&re);
            return NULL;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + out_pos, input + offset, chunk);
        out_pos += chunk;
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