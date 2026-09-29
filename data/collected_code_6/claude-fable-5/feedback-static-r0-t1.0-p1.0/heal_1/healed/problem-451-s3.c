#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 256

int remove_whitespace(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_pos = 0;
    size_t input_len;
    const char *cursor;
    char errbuf[ERRBUF_SIZE];

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        return -1;
    }

    cursor = input;

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        memset(errbuf, 0, sizeof(errbuf));
        regerror(ret, &regex, errbuf, sizeof(errbuf) - 1);
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strnlen(cursor, input_len - (size_t)(cursor - input));
            if (remaining >= output_size || out_pos >= output_size - remaining) {
                regfree(&regex);
                return -1;
            }
            memcpy(output + out_pos, cursor, remaining);
            out_pos += remaining;
            break;
        } else if (ret != 0) {
            memset(errbuf, 0, sizeof(errbuf));
            regerror(ret, &regex, errbuf, sizeof(errbuf) - 1);
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            regfree(&regex);
            return -1;
        }

        if ((size_t)match.rm_so >= output_size ||
            out_pos >= output_size - (size_t)match.rm_so) {
            regfree(&regex);
            return -1;
        }
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
    size_t input_len;
    size_t buf_size;
    char *output;

    input_len = strnlen(input, MAX_INPUT_LEN);
    if (input_len >= MAX_INPUT_LEN) {
        fprintf(stderr, "input too long\n");
        return EXIT_FAILURE;
    }

    buf_size = input_len + 1;
    output = calloc(1, buf_size);
    if (output == NULL) {
        fprintf(stderr, "calloc failed\n");
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