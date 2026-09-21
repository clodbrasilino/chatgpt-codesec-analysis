#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alphanumeric(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    const char *cursor;
    size_t out_len = 0;
    size_t input_len;
    size_t remaining;
    int ret;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, 4096);
    if (input_len >= 4096) {
        return -1;
    }

    ret = regcomp(&regex, "[^a-zA-Z0-9]", REG_EXTENDED);
    if (ret != 0) {
        return -1;
    }

    cursor = input;
    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            remaining = strnlen(cursor, 4096 - (cursor - input));
            /* Possible weaknesses found:
             *  Assuming that condition 'out_len+remaining>=output_size' is not redundant
             */
            if (out_len + remaining >= output_size) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             *  Condition 'out_len+remaining<=output_size' is always true [knownConditionTrueFalse]
             *  Condition 'out_len+remaining<=output_size' is always true
             */
            if (remaining > 0 && out_len + remaining <= output_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + out_len, cursor, remaining);
                out_len += remaining;
            }
            break;
        } else if (ret != 0) {
            regfree(&regex);
            return -1;
        }

        /* Possible weaknesses found:
         *  Assuming that condition 'match.rm_so>0' is not redundant
         */
        if (match.rm_so > 0) {
            /* Possible weaknesses found:
             *  Assuming condition is false
             *  Assuming that condition 'out_len+(unsigned long)match.rm_so>=output_size' is not redundant
             */
            if (out_len + (size_t)match.rm_so >= output_size) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             *  Condition '(unsigned long)match.rm_so>0' is always true
             *  Condition 'out_len+(unsigned long)match.rm_so<=output_size' is always true
             *  Condition 'out_len+(unsigned long)match.rm_so<=output_size' is always true [knownConditionTrueFalse]
             *  Condition '(unsigned long)match.rm_so>0' is always true [knownConditionTrueFalse]
             */
            if ((size_t)match.rm_so > 0 && out_len + (size_t)match.rm_so <= output_size) {
                /* Possible weaknesses found:
                 * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
                 */
                memcpy(output + out_len, cursor, (size_t)match.rm_so);
                out_len += (size_t)match.rm_so;
            }
        }
        cursor += match.rm_eo;
    }

    output[out_len] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$";
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char output[256];

    memset(output, 0, sizeof(output));

    if (remove_non_alphanumeric(input, output, sizeof(output)) == 0) {
        printf("%s\n", output);
    } else {
        fprintf(stderr, "Error processing string\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}