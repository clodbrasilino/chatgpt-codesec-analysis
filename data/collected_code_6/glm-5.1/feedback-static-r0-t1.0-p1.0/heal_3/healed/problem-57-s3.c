#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return (*(const char *)b - *(const char *)a);
}

char* find_largest_number(const int *digits, int count) {
    if (digits == NULL || count <= 0) {
        return NULL;
    }

    char *str = (char *)malloc((count + 1) * sizeof(char));
    if (str == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        if (digits[i] < 0 || digits[i] > 9) {
            free(str);
            return NULL;
        }
        str[i] = digits[i] + '0';
    }
    str[count] = '\0';

    qsort(str, count, sizeof(char), compare);

    return str;
}

int main() {
    int digits[] = {8, 9, 2, 1, 4};
    int count = sizeof(digits) / sizeof(digits[0]);

    char *largest = find_largest_number(digits, count);
    if (largest == NULL) {
        fprintf(stderr, "Invalid input or memory allocation failed\n");
        return 1;
    }

    printf("%s\n", largest);

    free(largest);

    int empty_digits[1];
    const char *empty_largest = find_largest_number(empty_digits, 0);
    if (empty_largest == NULL) {
        printf("Handled empty array correctly\n");
    }

    int temp_null_digits[5] = {0};
    const int *null_digits = NULL;
    const char *null_largest = find_largest_number(NULL, 5);
    if (null_largest == NULL) {
        printf("Handled NULL array correctly\n");
    }

    const int invalid_digits[] = {5, 12, 3};
    const char *invalid_largest = find_largest_number(invalid_digits, 3);
    if (invalid_largest == NULL) {
        printf("Handled invalid digits correctly\n");
    }

    return 0;
}