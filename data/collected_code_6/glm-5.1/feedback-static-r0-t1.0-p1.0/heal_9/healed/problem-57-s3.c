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

void handle_result(char *result) {
    if (result == NULL) {
        printf("Handled invalid or empty input correctly\n");
    } else {
        printf("%s\n", result);
        free(result);
    }
}

int main() {
    int digits[] = {8, 9, 2, 1, 4};
    int count = sizeof(digits) / sizeof(digits[0]);
    char *largest = find_largest_number(digits, count);
    handle_result(largest);

    const int empty_digits[1] = {0};
    char *empty_largest = find_largest_number(empty_digits, 0);
    handle_result(empty_largest);

    char *null_largest = find_largest_number(NULL, 0);
    handle_result(null_largest);

    const int invalid_digits[] = {5, 12, 3};
    char *invalid_largest = find_largest_number(invalid_digits, 3);
    handle_result(invalid_largest);

    return 0;
}