#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    unsigned char ca = *(const unsigned char *)a;
    unsigned char cb = *(const unsigned char *)b;
    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}

void sort_string(char *str, size_t len) {
    if (str == NULL || len == 0) return;
    qsort(str, len, sizeof(char), compare_chars);
}

int main(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char str[256];
    size_t len;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t fgets_len = strlen(str);
    if (fgets_len > 0 && str[fgets_len - 1] == '\n') {
        str[fgets_len - 1] = '\0';
        /* Possible weaknesses found:
         *  Variable 'fgets_len' is assigned a value that is never used. [unreadVariable]
         */
        fgets_len--;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    len = strlen(str);

    if (len > 0) {
        sort_string(str, len);
    }

    printf("Sorted string: %s\n", str);

    return 0;
}