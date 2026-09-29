#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

static void reverse_range(char *s, size_t begin, size_t end) {
    while (begin < end) {
        char tmp = s[begin];
        s[begin] = s[end];
        s[end] = tmp;
        ++begin;
        --end;
    }
}

void reverse_words(char *s, size_t max_len) {
    if (s == NULL || max_len == 0) {
        return;
    }

    size_t len = strnlen(s, max_len);
    if (len == 0) {
        return;
    }

    reverse_range(s, 0, len - 1);

    size_t start = 0;
    while (start < len) {
        while (start < len && isspace((unsigned char)s[start])) {
            ++start;
        }

        size_t end = start;
        while (end < len && !isspace((unsigned char)s[end])) {
            ++end;
        }

        if (start < end) {
            reverse_range(s, start, end - 1);
            start = end;
        }
    }
}

int main(void) {
    char str[] = "  Hello   world from C  ";
    reverse_words(str, sizeof(str));
    printf("%s\n", str);
    return 0;
}