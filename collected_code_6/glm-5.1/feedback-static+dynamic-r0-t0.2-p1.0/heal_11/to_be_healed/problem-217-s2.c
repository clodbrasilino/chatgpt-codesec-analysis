#include <stdio.h>
#include <string.h>

char find_first_repeated(const char *str, size_t max_len) {
    if (str == NULL || max_len < 2) {
        return '\0';
    }

    size_t len = strnlen(str, max_len);
    if (len < 2) {
        return '\0';
    }

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    unsigned char char_set[256] = {0};

    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)str[i];
        if (char_set[c] == 1) {
            return (char)c;
        }
        char_set[c] = 1;
    }

    return '\0';
}

int main(void) {
    const char *test_str1 = "programming";
    const char *test_str2 = "abcdef";
    const char *test_str3 = "a";
    const char *test_str4 = NULL;

    char res1 = find_first_repeated(test_str1, sizeof("programming") - 1);
    char res2 = find_first_repeated(test_str2, sizeof("abcdef") - 1);
    char res3 = find_first_repeated(test_str3, sizeof("a") - 1);
    /* Possible weaknesses found:
     *  Variable 'res4' is assigned a value that is never used. [unreadVariable]
     *  Value stored to 'res4' during its initialization is never read [deadcode.DeadStores]
     */
    char res4 = find_first_repeated(test_str4, 2);

    if (res1 != '\0') {
        printf("First repeated character in '%s': %c\n", test_str1, res1);
    } else {
        printf("No repeated character found in '%s'\n", test_str1);
    }

    if (res2 != '\0') {
        printf("First repeated character in '%s': %c\n", test_str2, res2);
    } else {
        printf("No repeated character found in '%s'\n", test_str2);
    }

    if (res3 != '\0') {
        printf("First repeated character in '%s': %c\n", test_str3, res3);
    } else {
        printf("No repeated character found in '%s'\n", test_str3);
    }

    printf("No repeated character found in 'NULL'\n");

    return 0;
}