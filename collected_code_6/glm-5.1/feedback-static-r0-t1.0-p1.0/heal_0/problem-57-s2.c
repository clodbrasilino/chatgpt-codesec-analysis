#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return *(const char *)b - *(const char *)a;
}

char *find_largest_number(int *digits, int count) {
    if (digits == NULL || count <= 0) {
        return NULL;
    }

    char *buffer = (char *)malloc(count + 1);
    if (buffer == NULL) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        if (digits[i] < 0 || digits[i] > 9) {
            free(buffer);
            return NULL;
        }
        buffer[i] = digits[i] + '0';
    }
    buffer[count] = '\0';

    qsort(buffer, count, sizeof(char), compare);

    return buffer;
}

int main() {
    int digits[] = {8, 6, 0, 1, 4, 2, 9, 9};
    int count = sizeof(digits) / sizeof(digits[0]);

    char *largest = find_largest_number(digits, count);
    if (largest == NULL) {
        return 1;
    }

    printf("%s\n", largest);

    free(largest);
    largest = NULL;

    return 0;
}