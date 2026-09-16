#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(char *)b - *(char *)a);
}

void find_largest_number(char *digits, char *result) {
    int len = strlen(digits);
    if (len == 0) {
        result[0] = '\0';
        return;
    }

    strcpy(result, digits);
    qsort(result, len, sizeof(char), compare_desc);
}

int main(void) {
    char digits[] = "312549";
    char result[50];

    find_largest_number(digits, result);
    printf("Largest number: %s\n", result);

    return 0;
}