#include <stdio.h>
#include <string.h>

void remove_even_characters(char *str, size_t str_len) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char temp[51] = {0};
    int j = 0;

    for (int i = 0; i < str_len && i < 50; i++) {
        if ((i + 1) % 2 != 0) {
            temp[j++] = str[i];
        }
    }

    temp[j] = '\0';
    memmove(str, temp, j + 1);
}

int main() {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[51] = {0};
    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) != NULL) {
        str[strcspn(str, "\n")] = '\0';

        size_t str_len = strnlen(str, 51);
        remove_even_characters(str, str_len);
        printf("String after removing even characters: %s\n", str);
    }

    return 0;
}