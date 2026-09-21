#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    return (*(const unsigned char *)a - *(const unsigned char *)b);
}

void sort_string(char *str, size_t size) {
    size_t len = strnlen(str, size);
    if (len > 0 && len < size) {
        qsort(str, len, sizeof(char), compare_chars);
    }
}

int main(void) {
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