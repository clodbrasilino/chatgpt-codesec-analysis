#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

int swap_spaces_underscores(char *str)
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
        char errbuf[256];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "regcomp failed: %s\n", errbuf);
        return -1;
    }

    while (str[offset] != '\0') {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            char errbuf[256];
            regerror(ret, &regex, errbuf, sizeof(errbuf));
            fprintf(stderr, "regexec failed: %s\n", errbuf);
            regfree(&regex);
            return -1;
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
    size_t len = strlen(original);
    char *buffer = malloc(len + 1);

    if (buffer == NULL) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }

    memcpy(buffer, original, len + 1);

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