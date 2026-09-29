#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 256

static int swap_spaces_underscores(char *str)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;

    if (str == NULL) {
        return -1;
    }

    ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char errbuf[ERRBUF_SIZE];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        errbuf[sizeof(errbuf) - 1] = '\0';
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    while (str[offset] != '\0') {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            /* Possible weaknesses found:
             * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
             */
            char errbuf[ERRBUF_SIZE];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            errbuf[sizeof(errbuf) - 1] = '\0';
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }
        if (str[offset + (size_t)match.rm_so] == ' ') {
            str[offset + (size_t)match.rm_so] = '_';
        } else {
            str[offset + (size_t)match.rm_so] = ' ';
        }
        offset += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *original = "hello world_this is_a test";
    size_t len = strnlen(original, MAX_INPUT_LEN);
    char *buffer;

    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    buffer = malloc(len + 1);
    if (buffer == NULL) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(buffer, original, len);
    buffer[len] = '\0';

    printf("Before: %s\n", buffer);

    if (swap_spaces_underscores(buffer) != 0) {
        fprintf(stderr, "swap_spaces_underscores failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("After:  %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}