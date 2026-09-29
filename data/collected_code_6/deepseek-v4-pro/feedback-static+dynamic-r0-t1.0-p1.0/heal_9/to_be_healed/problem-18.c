#include <stdio.h>
#include <string.h>

static int char_in_set(char c, const char *set) {
    while (*set) {
        if (c == *set)
            return 1;
        set++;
    }
    return 0;
}

void remove_chars(char *str, size_t str_size, const char *remove_set) {
    if (!str || !remove_set || str_size == 0)
        return;

    char *src = str;
    char *dst = str;
    size_t dst_index = 0;

    while (*src && dst_index < str_size - 1) {
        if (!char_in_set(*src, remove_set)) {
            *dst = *src;
            dst++;
            dst_index++;
        }
        src++;
    }
    *dst = '\0';
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
    if (!fgets(str1, sizeof(str1), stdin))
        return 1;
    str1[strcspn(str1, "\n")] = '\0';

    printf("Enter second string: ");
    if (!fgets(str2, sizeof(str2), stdin))
        return 1;
    str2[strcspn(str2, "\n")] = '\0';

    remove_chars(str1, sizeof(str1), str2);

    printf("Result: %s\n", str1);

    return 0;
}