#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 256

static void report_regex_error(int code, const regex_t *regex, const char *prefix)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char errbuf[ERRBUF_SIZE];

    memset(errbuf, 0, sizeof(errbuf));
    regerror(code, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    fprintf(stderr, "%s: %s\n", prefix, errbuf);
}

static int remove_whitespace(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_pos = 0;
    const char *cursor = input;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    if (strnlen(input, MAX_INPUT_LEN + 1) > MAX_INPUT_LEN) {
        return -1;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        report_regex_error(ret, &regex, "regcomp failed");
        return -1;
    }

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, MAX_INPUT_LEN);

            if (remaining >= output_size || out_pos > output_size - 1 - remaining) {
                regfree(&regex);
                return -1;
            }
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(output + out_pos, cursor, remaining);
            out_pos += remaining;
            break;
        } else if (ret != 0) {
            report_regex_error(ret, &regex, "regexec failed");
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        if ((size_t)match.rm_so >= output_size ||
            out_pos > output_size - 1 - (size_t)match.rm_so) {
            regfree(&regex);
            return -1;
        }
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(output + out_pos, cursor, (size_t)match.rm_so);
        out_pos += (size_t)match.rm_so;
        cursor += match.rm_eo;
    }

    if (out_pos >= output_size) {
        regfree(&regex);
        return -1;
    }

    output[out_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    static const char input[] = "  Hello,   World!  This\tis a\ntest string.  ";
    size_t input_len = strnlen(input, sizeof(input));
    size_t buf_size;
    char *output;

    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "input too long\n");
        return EXIT_FAILURE;
    }

    buf_size = input_len + 1;
    output = calloc(1, buf_size);
    if (output == NULL) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }

    if (remove_whitespace(input, output, buf_size) != 0) {
        fprintf(stderr, "remove_whitespace failed\n");
        free(output);
        return EXIT_FAILURE;
    }

    if (printf("Original: \"%s\"\n", input) < 0 ||
        printf("Result:   \"%s\"\n", output) < 0) {
        free(output);
        return EXIT_FAILURE;
    }

    free(output);
    return EXIT_SUCCESS;
}