#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char *space_out_capitals(const char *str) {
    if (str == NULL) {
        return NULL;
    }

    regex_t regex;
    int ret = regcomp(&regex, "([A-Z][a-z0-9]+)", REG_EXTENDED);
    if (ret != 0) {
        return NULL;
    }

    size_t str_len = strlen(str);

    size_t max_len = str_len * 2 + 1;
    char *result = malloc(max_len);
    if (result == NULL) {
        regfree(&regex);
        return NULL;
    }

    const char *p = str;
    char *out = result;
    const char *end = result + max_len - 1;

    regmatch_t match[2];
    while (1) {
        ret = regexec(&regex, p, 2, match, 0);
        if (ret != 0) {
            break;
        }

        if (match[1].rm_so == -1) {
            break;
        }

        size_t prefix_len = match[1].rm_so;
        if (prefix_len > 0) {
            if (out + prefix_len > end) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(out, p, prefix_len);
            out += prefix_len;
            if (out < end) {
                *out++ = ' ';
            }
            p += match[1].rm_so;
        } else {
            if (p != str) {
                if (out < end) {
                    *out++ = ' ';
                }
            }
        }

        size_t word_len = match[1].rm_eo - match[1].rm_so;
        if (word_len > 0) {
            if (out + word_len > end) {
                regfree(&regex);
                free(result);
                return NULL;
            }
            memcpy(out, p, word_len);
            out += word_len;
            p += word_len;
        } else {
            if (out < end) {
                *out++ = *p;
            }
            p++;
        }
    }

    size_t remaining_len = strlen(p);

    if (out + remaining_len > end) {
        regfree(&regex);
        free(result);
        return NULL;
    }
    memcpy(out, p, remaining_len);
    out += remaining_len;
    *out = '\0';

    regfree(&regex);

    size_t final_len = strlen(result) + 1;

    char *shrunk = realloc(result, final_len);
    if (shrunk != NULL) {
        return shrunk;
    }
    return result;
}

int main(void) {
    char *res1 = space_out_capitals("HelloWorldExample");
    if (res1 != NULL) {
        printf("%s\n", res1);
        free(res1);
    }

    char *res2 = space_out_capitals("ThisIsATest");
    if (res2 != NULL) {
        printf("%s\n", res2);
        free(res2);
    }

    char *res3 = space_out_capitals("Already Spaced");
    if (res3 != NULL) {
        printf("%s\n", res3);
        free(res3);
    }

    char *null_test = space_out_capitals(NULL);
    if (null_test == NULL) {
        printf("NULL handled\n");
    }

    return 0;
}