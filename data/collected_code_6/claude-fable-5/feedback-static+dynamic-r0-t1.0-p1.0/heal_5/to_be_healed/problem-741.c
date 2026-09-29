#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_STR_LEN 4096

bool all_chars_same(const char *str, size_t max_len)
{
    size_t i;
    size_t len;

    if (str == NULL) {
        return false;
    }

    len = strnlen(str, max_len);
    if (len == 0) {
        return false;
    }

    for (i = 1; i < len; i++) {
        if (str[i] != str[0]) {
            return false;
        }
    }

    return true;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_STR_LEN + 2];

    memset(buffer, 0, sizeof(buffer));

    if (fgets(buffer, (int)sizeof(buffer), stdin) == NULL) {
        printf("False\n");
        fflush(stdout);
        return 0;
    }

    buffer[sizeof(buffer) - 1] = '\0';
    buffer[strcspn(buffer, "\r\n")] = '\0';

    if (all_chars_same(buffer, sizeof(buffer))) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    fflush(stdout);
    return 0;
}