#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_non_alnum(const char *input, char **output)
{
    regex_t regex;
    regmatch_t pmatch[1];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[256];
    char *result;
    size_t input_len;
    size_t pos;
    size_t out_pos;
    int ret;

    if (input == NULL || output == NULL) {
        return -1;
    }

    *output = NULL;

    ret = regcomp(&regex, "[^[:alnum:]]", REG_EXTENDED);
    if (ret != 0) {
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    input_len = strlen(input);

    result = malloc(input_len + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        regfree(&regex);
        return -1;
    }

    pos = 0;
    out_pos = 0;

    while (pos < input_len) {
        ret = regexec(&regex, input + pos, 1, pmatch, 0);
        if (ret == REG_NOMATCH) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + out_pos, input + pos, input_len - pos);
            out_pos += input_len - pos;
            break;
        }
        if (ret != 0) {
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            free(result);
            regfree(&regex);
            return -1;
        }
        if (pmatch[0].rm_so < 0 || pmatch[0].rm_eo <= pmatch[0].rm_so ||
            (size_t)pmatch[0].rm_eo > input_len - pos) {
            fprintf(stderr, "Invalid regex match offsets.\n");
            free(result);
            regfree(&regex);
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + out_pos, input + pos, (size_t)pmatch[0].rm_so);
        out_pos += (size_t)pmatch[0].rm_so;
        pos += (size_t)pmatch[0].rm_eo;
    }

    result[out_pos] = '\0';
    *output = result;

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "Hello, World! 123 @#$%^&* C_Prog-2024";
    char *cleaned = NULL;

    if (remove_non_alnum(input, &cleaned) != 0) {
        fprintf(stderr, "Failed to remove non-alphanumeric characters.\n");
        return EXIT_FAILURE;
    }

    if (cleaned == NULL) {
        fprintf(stderr, "Unexpected NULL result.\n");
        return EXIT_FAILURE;
    }

    printf("Original: %s\n", input);
    printf("Cleaned:  %s\n", cleaned);

    free(cleaned);
    cleaned = NULL;

    return EXIT_SUCCESS;
}