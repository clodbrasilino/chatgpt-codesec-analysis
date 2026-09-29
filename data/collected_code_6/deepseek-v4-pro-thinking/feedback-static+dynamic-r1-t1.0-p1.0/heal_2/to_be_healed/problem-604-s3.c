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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        int complete = (strchr(buffer, '\n') != NULL);
        buffer[strcspn(buffer, "\r\n")] = '\0';
        /* Possible weaknesses found:
         * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
         */
        size_t len = strlen(buffer);
        if (len > 0) {
            reverse_words(buffer, len);
            puts(buffer);
        }
        if (!complete) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != '\n' && c != EOF);
        }
    }
    return 0;
}