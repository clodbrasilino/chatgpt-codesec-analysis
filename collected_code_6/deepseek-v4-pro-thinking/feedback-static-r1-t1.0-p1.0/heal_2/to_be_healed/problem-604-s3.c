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

char *reverse_words(char *str, size_t size) {
    if (str == NULL || size == 0) {
        return NULL;
    }

    size_t len = strnlen(str, size);
    if (len == size) {
        str[size - 1] = '\0';
        len = size - 1;
    }

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];

    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        buffer[strcspn(buffer, "\r\n")] = '\0';
        reverse_words(buffer, sizeof(buffer));
        puts(buffer);
    }

    return 0;
}