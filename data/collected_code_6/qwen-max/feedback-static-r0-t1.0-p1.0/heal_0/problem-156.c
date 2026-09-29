#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* strings_to_ints(char** str_values, int n, int* out_size) {
    *out_size = 0;
    if (str_values == NULL || n <= 0) {
        return NULL;
    }
    int* int_values = (int*)malloc(n * sizeof(int));
    if (int_values == NULL) {
        return NULL;
    }
    for (int i = 0; i < n; ++i) {
        char* endptr;
        long converted_value = strtol(str_values[i], &endptr, 10);
        if (endptr == str_values[i] || *endptr != '\0') {
            free(int_values);
            return NULL;
        }
        int_values[i] = (int)converted_value;
    }
    *out_size = n;
    return int_values;
}

int main() {
    char* values[] = {"123", "456", "789"};
    int n = 3;
    int out_size;
    int* int_values = strings_to_ints(values, n, &out_size);
    if (int_values == NULL) {
        printf("Conversion failed\n");
        return 1;
    }
    for (int i = 0; i < out_size; ++i) {
        printf("%d ", int_values[i]);
    }
    printf("\n");
    free(int_values);
    return 0;
}