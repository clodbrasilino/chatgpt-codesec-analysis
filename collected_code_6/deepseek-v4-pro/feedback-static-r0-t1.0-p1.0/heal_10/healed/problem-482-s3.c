#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdint.h>

void find_sequences(const char *str) {
    regex_t regex;
    regmatch_t match[1];
    const char *pattern = "[A-Z][a-z]+";
    int ret;
    const char *cursor;
    size_t cursor_len;

    if (!str) {
        return;
    }

    cursor_len = strlen(str);
    if (cursor_len == 0) {
        return;
    }

    cursor = str;

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (cursor_len > 0 && regexec(&regex, cursor, 1, match, 0) == 0) {
        int start = match[0].rm_so;
        int end = match[0].rm_eo;

        if (start < 0 || end < 0 || end <= start) {
            if (cursor_len > 0) {
                cursor++;
                cursor_len--;
            }
            continue;
        }

        if ((size_t)start >= cursor_len || (size_t)end > cursor_len) {
            if (cursor_len > 0) {
                cursor++;
                cursor_len--;
            }
            continue;
        }

        int match_len = end - start;

        if (match_len <= 0) {
            if (cursor_len > 0) {
                cursor++;
                cursor_len--;
            }
            continue;
        }

        size_t len = (size_t)match_len;

        if (len > SIZE_MAX - 1) {
            if (cursor_len > 0) {
                cursor++;
                cursor_len--;
            }
            continue;
        }

        size_t copy_start = (size_t)start;

        char *seq = (char *)malloc(len + 1);
        if (!seq) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }

        if (copy_start + len <= cursor_len) {
            memcpy(seq, cursor + copy_start, len);
            seq[len] = '\0';
            printf("%s\n", seq);
        }

        free(seq);

        size_t advance = (size_t)end;
        if (advance <= cursor_len) {
            cursor += advance;
            cursor_len -= advance;
        } else {
            break;
        }
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Hello World This Is A Test String with Some Uppercase Letters";
    find_sequences(text);
    return 0;
}