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

char *reverse_words(char *str) {
    if (str == NULL) {
        return NULL;
    }

    size_t len = strlen(str);
    if (len == 0) {
        return str;
    }

    reverse_range(str, str + len - 1);

    char *p = str;
    while (*p != '\0') {
        if (isspace((unsigned char)*p)) {
            ++p;
        } else {
            char *start = p;
            while (*p != '\0' && !isspace((unsigned char)*p)) {
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
        buffer[strcspn(buffer, "\r\n")] = '\0';
        reverse_words(buffer);
        puts(buffer);
    }

    return 0;
}