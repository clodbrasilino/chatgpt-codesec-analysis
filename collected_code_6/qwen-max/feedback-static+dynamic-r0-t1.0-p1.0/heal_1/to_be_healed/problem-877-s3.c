#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int compare_chars(const void *a, const void *b) {
    return (*(char*)a - *(char*)b);
}

void sort_string(char *str) {
    if (str == NULL) return;
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    qsort(str, strlen(str), sizeof(char), compare_chars);
}

int main() {
    char str[] = "dcba";
    sort_string(str);
    printf("%s\n", str);
    return 0;
}