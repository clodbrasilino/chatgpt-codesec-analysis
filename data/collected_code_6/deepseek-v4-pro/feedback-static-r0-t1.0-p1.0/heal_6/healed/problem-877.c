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
    char str[256];
    size_t len;

    printf("Enter a string: ");
    if (fgets(str, sizeof(str), stdin) == NULL) {
        return 1;
    }

    len = strnlen(str, sizeof(str));
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
        len--;
    }

    if (len > 0) {
        sort_string(str, len);
    }

    printf("Sorted string: %s\n", str);

    return 0;
}