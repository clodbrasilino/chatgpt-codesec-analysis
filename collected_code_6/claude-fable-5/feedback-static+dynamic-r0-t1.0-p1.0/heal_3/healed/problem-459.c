#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define MAX_INPUT_LEN 4096

char *remove_uppercase(const char *input)
{
    regex_t regex;
    regmatch_t match;
    char *result;
    size_t len;
    size_t pos;
    size_t out;
    size_t chunk;
    int ret;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len >= MAX_INPUT_LEN) {
        return NULL;
    }

    ret = regcomp(&regex, "[A-Z]+", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    result = malloc(len + 1);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    pos = 0;
    out = 0;
    while (pos <= len) {
        ret = regexec(&regex, input + pos, 1, &match, 0);
        if (ret == REG_NOMATCH) {
            chunk = len - pos;
            if (chunk > len || out > len - chunk) {
                free(result);
                regfree(&regex);
                return NULL;
            }
            memcpy(result + out, input + pos, chunk);
            out += chunk;
            break;
        }
        if (ret != 0) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        if (match.rm_so < 0 || match.rm_eo < match.rm_so) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        chunk = (size_t)match.rm_so;
        if (chunk > len || out > len - chunk || pos > len - chunk) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        memcpy(result + out, input + pos, chunk);
        out += chunk;
        if ((size_t)match.rm_eo > len - pos) {
            free(result);
            regfree(&regex);
            return NULL;
        }
        pos += (size_t)match.rm_eo;
        if (match.rm_eo == match.rm_so) {
            break;
        }
    }

    if (out > len) {
        free(result);
        regfree(&regex);
        return NULL;
    }
    result[out] = '\0';
    regfree(&regex);
    return result;
}

int main(void)
{
    char buffer[MAX_INPUT_LEN];
    char *cleaned;
    size_t len;

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        fprintf(stderr, "Failed to read input\n");
        return EXIT_FAILURE;
    }

    buffer[sizeof(buffer) - 1] = '\0';

    len = strnlen(buffer, sizeof(buffer));
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }

    cleaned = remove_uppercase(buffer);
    if (cleaned == NULL) {
        fprintf(stderr, "Failed to process string\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", cleaned) < 0) {
        free(cleaned);
        return EXIT_FAILURE;
    }

    free(cleaned);
    return EXIT_SUCCESS;
}