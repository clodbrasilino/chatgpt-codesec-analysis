#include <stdio.h>
#include <string.h>

int lengthOfLastWord(const char *s, size_t max_len) {
    int len = 0;
    size_t i = max_len;

    if (i == 0) {
        return 0;
    }
    i--;

    while (i > 0 && s[i] == ' ') {
        i--;
    }

    while (i > 0 && s[i] != ' ') {
        len++;
        i--;
    }
    
    if (i == 0 && s[i] != ' ') {
        len++;
    }

    return len;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[1024];

    if (fgets(str, sizeof(str), stdin) != NULL) {
        size_t len = strnlen(str, sizeof(str));
        if (len > 0 && str[len - 1] == '\n') {
            str[len - 1] = '\0';
            len--;
        }
        printf("%d\n", lengthOfLastWord(str, len));
    }

    return 0;
}