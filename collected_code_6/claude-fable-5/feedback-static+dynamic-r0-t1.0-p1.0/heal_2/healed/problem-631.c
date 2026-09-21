#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096
#define ERRBUF_SIZE 256

static void print_regex_error(int errcode, const regex_t *regex, const char *context)
{
    char errbuf[ERRBUF_SIZE];
    size_t needed;

    memset(errbuf, 0, sizeof(errbuf));
    needed = regerror(errcode, regex, errbuf, sizeof(errbuf) - 1);
    errbuf[sizeof(errbuf) - 1] = '\0';
    if (needed >= sizeof(errbuf)) {
        fprintf(stderr, "%s failed (message truncated): %s\n", context, errbuf);
    } else {
        fprintf(stderr, "%s failed: %s\n", context, errbuf);
    }
}

static int swap_spaces_underscores(char *str, size_t max_len)
{
    regex_t regex;
    regmatch_t match;
    int ret;
    size_t offset = 0;
    size_t len;

    if (str == NULL) {
        return -1;
    }

    len = strnlen(str, max_len);
    if (len >= max_len) {
        return -1;
    }

    ret = regcomp(&regex, "[ _]", REG_EXTENDED);
    if (ret != 0) {
        print_regex_error(ret, &regex, "regcomp");
        return -1;
    }

    while (offset < len && str[offset] != '\0') {
        ret = regexec(&regex, str + offset, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            break;
        }
        if (ret != 0) {
            print_regex_error(ret, &regex, "regexec");
            regfree(&regex);
            return -1;
        }
        if (match.rm_so < 0 || match.rm_eo <= match.rm_so) {
            break;
        }
        if (offset + (size_t)match.rm_so >= len) {
            break;
        }
        if (str[offset + (size_t)match.rm_so] == ' ') {
            str[offset + (size_t)match.rm_so] = '_';
        } else {
            str[offset + (size_t)match.rm_so] = ' ';
        }
        if ((size_t)match.rm_eo > len - offset) {
            break;
        }
        offset += (size_t)match.rm_eo;
    }

    regfree(&regex);
    return 0;
}

int main(void)
{
    const char *original = "hello world_this is_a test";
    size_t len;
    size_t buffer_size;
    char *buffer;

    len = strnlen(original, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        fprintf(stderr, "input string too long or not terminated\n");
        return EXIT_FAILURE;
    }

    buffer_size = len + 1;
    buffer = malloc(buffer_size);
    if (buffer == NULL) {
        fprintf(stderr, "malloc failed\n");
        return EXIT_FAILURE;
    }

    if (len >= buffer_size) {
        fprintf(stderr, "buffer size insufficient\n");
        free(buffer);
        return EXIT_FAILURE;
    }
    memcpy(buffer, original, len);
    buffer[len] = '\0';

    printf("Before: %s\n", buffer);

    if (swap_spaces_underscores(buffer, buffer_size) != 0) {
        fprintf(stderr, "swap_spaces_underscores failed\n");
        free(buffer);
        return EXIT_FAILURE;
    }

    printf("After:  %s\n", buffer);

    free(buffer);
    return EXIT_SUCCESS;
}