#include <stdio.h>
#include <string.h>

size_t find_length(const char *str) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[1024];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }
    size_t len = find_length(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        /* Possible weaknesses found:
         *  Variable 'buffer[len-1]' is assigned a value that is never used. [unreadVariable]
         */
        buffer[len - 1] = '\0';
        len--;
    }
    printf("Length: %zu\n", len);
    return 0;
}