#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(char *)b - *(char *)a);
}

void largest_number_from_digits(char *digits, char *result) {
    size_t len = strlen(digits);
    if (len == 0) {
        result[0] = '\0';
        return;
    }
    memcpy(result, digits, len + 1);
    qsort(result, len, sizeof(char), compare_desc);
}

int main(void) {
    char digits[] = "9371458260";
    char result[32];
    largest_number_from_digits(digits, result);
    printf("%s\n", result);
    return 0;
}