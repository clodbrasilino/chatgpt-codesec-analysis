#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_desc(const void *a, const void *b) {
    return (*(const char *)b - *(const char *)a);
}

void find_largest_number(const char *digits, char *result, size_t result_size) {
    if (digits == NULL || result == NULL || result_size == 0) {
        return;
    }

    size_t len = strnlen(digits, result_size - 1);
    
    if (len == 0) {
        result[0] = '\0';
        return;
    }

    if (len >= result_size) {
        len = result_size - 1;
    }

    memcpy(result, digits, len);
    result[len] = '\0';

    qsort(result, len, sizeof(char), compare_desc);
}

int main(void) {
    const char digits[] = "312549";
    char result[10] = {0};

    find_largest_number(digits, result, sizeof(result));
    printf("Largest number: %s\n", result);

    return 0;
}