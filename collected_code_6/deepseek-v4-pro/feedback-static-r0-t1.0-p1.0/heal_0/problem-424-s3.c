#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *extract_rear_elements(char **arr, int size) {
    if (arr == NULL || size <= 0) {
        return NULL;
    }

    char *result = (char *)malloc(size + 1);
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (arr[i] == NULL) {
            free(result);
            return NULL;
        }
        size_t len = strlen(arr[i]);
        if (len == 0) {
            free(result);
            return NULL;
        }
        result[i] = arr[i][len - 1];
    }
    result[size] = '\0';

    return result;
}

int main(void) {
    char *arr[] = {"hello", "world", "test", "example"};
    int size = sizeof(arr) / sizeof(arr[0]);

    char *rear_elements = extract_rear_elements(arr, size);
    if (rear_elements == NULL) {
        return 1;
    }

    printf("%s\n", rear_elements);

    free(rear_elements);
    return 0;
}