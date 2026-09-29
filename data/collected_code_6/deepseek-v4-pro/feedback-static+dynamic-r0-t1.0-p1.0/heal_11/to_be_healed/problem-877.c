#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    return (*(const unsigned char *)a - *(const unsigned char *)b);
}

char *sort_string(char *str, size_t size) {
    size_t len = strnlen(str, size);
    if (len > 0 && len < size) {
        qsort(str, len, sizeof(char), compare_chars);
    }
    return str;
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[129];

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    str[strcspn(str, "\n")] = '\0';

    sort_string(str, sizeof(str));

    printf("Sorted string: %s\n", str);

    return 0;
}