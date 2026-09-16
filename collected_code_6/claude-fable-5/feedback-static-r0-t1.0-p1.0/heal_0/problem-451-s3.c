#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int remove_whitespace(const char *input, char *output, size_t output_size)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t out_pos = 0;
    const char *cursor = input;

    if (input == NULL || output == NULL || output_size == 0) {
        return -1;
    }

    ret = regcomp(&regex, "[[:space:]]+", REG_EXTENDED);
    if (ret != 0) {
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    while (*cursor != '\0') {
        ret = regexec(&regex, cursor, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            size_t remaining = strlen(cursor);
            if (out_pos + remaining >= output_size) {
                regfree(&regex);
                return -1;
            }
            memcpy(output + out_pos, cursor, remaining);
            out_pos += remaining;
            break;
        } else if (ret != 0) {
            char errbuf[256];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }

        if (out_pos + (size_t)match.rm_so >= output_size) {
            regfree(&regex);
            return -1;
        }
        memcpy(output + out_pos, cursor, (size_t)match.rm_so);
        out_pos += (size_t)match.rm_so;
        cursor += match.rm_eo;
    }

    output[out_pos] = '\0';
    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *input = "  Hello,   World!  This\tis a\ntest string.  ";
    size_t buf_size = strlen(input) + 1;
    char *output = malloc(buf_size);

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