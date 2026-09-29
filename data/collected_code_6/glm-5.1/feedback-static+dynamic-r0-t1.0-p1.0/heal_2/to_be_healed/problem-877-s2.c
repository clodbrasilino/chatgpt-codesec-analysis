#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_string(char *str, size_t max_len) {
    if (str == NULL) {
        return;
    }
    size_t len = strnlen(str, max_len);
    if (len < 2) {
        return;
    }
    for (size_t i = 0; i < len - 1; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (str[i] > str[j]) {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return EXIT_FAILURE;
    }
    buffer[strcspn(buffer, "\n")] = '\0';
    sort_string(buffer, sizeof(buffer));
    printf("%s\n", buffer);
    return EXIT_SUCCESS;
}