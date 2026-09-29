#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ERR_BUF_SIZE 512
#define MAX_WORD_LEN 1024

void find_words(const char *text) {
    regex_t regex;
    regmatch_t match;
    const char *p = text;
    int ret;
    size_t text_len;

    if (text == NULL) {
        fprintf(stderr, "Input text is NULL\n");
        return;
    }

    text_len = strnlen(text, MAX_WORD_LEN * 1024);

    ret = regcomp(&regex, "\\b[A-Za-z]{4,}\\b", REG_EXTENDED);
    if (ret) {
        char errbuf[ERR_BUF_SIZE];
        regerror(ret, &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compilation failed: %s\n", errbuf);
        return;
    }

    while (regexec(&regex, p, 1, &match, 0) == 0) {
        if (match.rm_so < 0 || match.rm_eo < 0) {
            break;
        }

        if (match.rm_eo < match.rm_so) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        size_t offset = (size_t)(p - text);
        if (offset >= text_len) break;

        size_t remaining = text_len - offset;

        if ((size_t)match.rm_so > remaining) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        size_t len = (size_t)(match.rm_eo - match.rm_so);
        if (len == 0) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        if (len > MAX_WORD_LEN) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        size_t src_offset = (size_t)(p - text) + (size_t)match.rm_so;
        if (src_offset >= text_len) {
            p++;
            if ((size_t)(p - text) >= text_len) break;
            continue;
        }

        size_t src_remaining = text_len - src_offset;
        if (len > src_remaining) {
            len = src_remaining;
        }

        if (len > MAX_WORD_LEN) {
            len = MAX_WORD_LEN;
        }

        char *result = (char *)malloc(len + 1);
        if (!result) {
            regfree(&regex);
            return;
        }

        if (len > 0) {
            const char *src = text + src_offset;
            if (src + len <= text + text_len) {
                memcpy(result, src, len);
            }
        }
        result[len] = '\0';
        printf("%s\n", result);
        free(result);

        p += match.rm_eo;
        if ((size_t)(p - text) >= text_len) break;
    }

    regfree(&regex);
}

int main(int argc, const char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    find_words(argv[1]);
    return EXIT_SUCCESS;
}