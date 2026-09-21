#include <stdio.h>
#include <string.h>
#include <ctype.h>

static void reverse_range(char *begin, char *end) {
    while (begin < end) {
        char tmp = *begin;
        *begin = *end;
        *end = tmp;
        ++begin;
        --end;
    }
}

char *reverse_words(char *str, size_t len) {
    if (str == NULL || len == 0) {
        return str;
    }
    reverse_range(str, str + len - 1);
    char *p = str;
    char *end = str + len;
    while (p < end) {
        if (isspace((unsigned char)*p)) {
            ++p;
        } else {
            char *start = p;
            while (p < end && !isspace((unsigned char)*p)) {
                ++p;
            }
            reverse_range(start, p - 1);
        }
    }
    return str;
}

int main(void) {
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int complete = (strchr(buffer, '\n') != NULL);
        buffer[strcspn(buffer, "\r\n")] = '\0';
        size_t len = strlen(buffer);
        if (len > 0) {
            reverse_words(buffer, len);
            puts(buffer);
        }
        if (!complete) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    return 0;
}