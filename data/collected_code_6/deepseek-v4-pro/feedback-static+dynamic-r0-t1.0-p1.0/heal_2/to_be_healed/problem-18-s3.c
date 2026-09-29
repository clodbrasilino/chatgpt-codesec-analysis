#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *remove_chars(char *str1, size_t str1_size, const char *str2) {
    if (str1 == NULL || str2 == NULL) {
        return str1;
    }

    int table[256] = {0};
    size_t i, j = 0;
    size_t len2 = strnlen(str2, str1_size);

    for (i = 0; i < len2; i++) {
        table[(unsigned char)str2[i]] = 1;
    }

    for (i = 0; i < str1_size && str1[i] != '\0'; i++) {
        if (!table[(unsigned char)str1[i]]) {
            str1[j++] = str1[i];
        }
    }

    str1[j] = '\0';
    return str1;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str1[256];
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str2[256];

    printf("Enter first string: ");
    if (fgets(str1, sizeof(str1), stdin) == NULL) {
        return 1;
    }
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    if (fgets(str2, sizeof(str2), stdin) == NULL) {
        return 1;
    }
    str2[strcspn(str2, "\n")] = '\0';

    remove_chars(str1, sizeof(str1), str2);

    printf("Result: %s\n", str1);

    return 0;
}