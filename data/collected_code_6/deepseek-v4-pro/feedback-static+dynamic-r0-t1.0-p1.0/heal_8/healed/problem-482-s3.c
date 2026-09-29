#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

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
        
        if (start < 0 || end <= start) {
            break;
        }
        
        size_t len = (size_t)(end - start);
        const char *null_pos = memchr(cursor, '\0', (size_t)end);
        
        if (!null_pos) {
            size_t remaining = (size_t)end;
            if (len > remaining || (size_t)start > remaining - len) {
                break;
            }
        } else {
            size_t actual_len = (size_t)(null_pos - cursor);
            if (len > actual_len || (size_t)start > actual_len - len) {
                break;
            }
        }
        
        char *seq = (char *)malloc(len + 1);
        if (!seq) {
            fprintf(stderr, "Memory allocation failed\n");
            regfree(&regex);
            return;
        }
        
        if (len > 0) {
            memcpy(seq, cursor + start, len);
        }
        seq[len] = '\0';
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