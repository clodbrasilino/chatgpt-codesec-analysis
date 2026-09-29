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
    const char *cursor = str;

    if (!str) {
        return;
    }

    ret = regcomp(&regex, pattern, REG_EXTENDED);
    if (ret) {
        fprintf(stderr, "Could not compile regex\n");
        return;
    }

    while (regexec(&regex, cursor, 1, match, 0) == 0) {
        int start = match[0].rm_so;
        int end = match[0].rm_eo;

        if (start < 0 || end < 0 || end <= start) {
            cursor++;
            continue;
        }

        size_t remaining = strlen(cursor);
        if ((size_t)start >= remaining || (size_t)end > remaining) {
            cursor++;
            continue;
        }

        int match_len = end - start;
        if (match_len <= 0) {
            cursor++;
            continue;
        }

        size_t len = (size_t)match_len;

        if (len > SIZE_MAX - 1) {
            cursor++;
            continue;
        }

        char *seq = (char *)malloc(len + 1);
        if (!seq) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }

        size_t copy_start = (size_t)start;
        size_t copy_len = len;
        if (copy_start + copy_len > remaining) {
            free(seq);
            cursor++;
            continue;
        }

        memcpy(seq, cursor + copy_start, copy_len);
        seq[copy_len] = '\0';
        printf("%s\n", seq);
        free(seq);
        cursor += end;
    }

    regfree(&regex);
}

int main(void) {
    const char *text = "Hello World This Is A Test String with Some Uppercase Letters";
    find_sequences(text);
    return 0;
}