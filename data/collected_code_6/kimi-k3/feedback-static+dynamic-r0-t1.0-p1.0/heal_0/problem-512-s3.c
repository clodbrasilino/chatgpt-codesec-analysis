#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} IntArray;

int init_array(IntArray *arr, int initial_capacity) {
    if (arr == NULL || initial_capacity <= 0) {
        return -1;
    }
    arr->data = malloc(sizeof(int) * (size_t)initial_capacity);
    if (arr->data == NULL) {
        return -1;
    }
    arr->size = 0;
    arr->capacity = initial_capacity;
    return 0;
}

int add_element(IntArray *arr, int value) {
    if (arr == NULL) {
        return -1;
    }
    if (arr->size >= arr->capacity) {
        int new_capacity = arr->capacity * 2;
        int *temp = realloc(arr->data, sizeof(int) * (size_t)new_capacity);
        if (temp == NULL) {
            return -1;
        }
        arr->data = temp;
        arr->capacity = new_capacity;
    }
    arr->data[arr->size] = value;
    arr->size++;
    return 0;
}

void free_array(IntArray *arr) {
    if (arr != NULL && arr->data != NULL) {
        free(arr->data);
        arr->data = NULL;
        arr->size = 0;
        arr->capacity = 0;
    }
}

int parse_nested_tuple(const char *str, IntArray *arr) {
    if (str == NULL || arr == NULL) {
        return -1;
    }
    
    int i = 0;
    int len = (int)strlen(str);
    
    while (i < len) {
        if (str[i] == '(' || str[i] == ')' || str[i] == ',' || str[i] == ' ') {
            i++;
            continue;
        }
        
        if (str[i] == '-' || (str[i] >= '0' && str[i] <= '9')) {
            int num = 0;
            int sign = 1;
            
            if (str[i] == '-') {
                sign = -1;
                i++;
            }
            
            if (i >= len || str[i] < '0' || str[i] > '9') {
                return -1;
            }
            
            while (i < len && str[i] >= '0' && str[i] <= '9') {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            
            if (add_element(arr, num * sign) != 0) {
                return -1;
            }
        } else {
            return -1;
        }
    }
    
    return 0;
}

int count_frequency(const IntArray *arr, int target) {
    if (arr == NULL) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < arr->size; i++) {
        if (arr->data[i] == target) {
            count++;
        }
    }
    return count;
}

int main(void) {
    const char *tuple_str = "(1, (2, 3), (1, (2, (1, 4))), 5, (2, 3))";
    IntArray elements;
    
    if (init_array(&elements, 10) != 0) {
        fprintf(stderr, "Failed to initialize array\n");
        return EXIT_FAILURE;
    }
    
    if (parse_nested_tuple(tuple_str, &elements) != 0) {
        fprintf(stderr, "Failed to parse tuple\n");
        free_array(&elements);
        return EXIT_FAILURE;
    }
    
    printf("Elements in nested tuple: ");
    for (int i = 0; i < elements.size; i++) {
        printf("%d ", elements.data[i]);
    }
    printf("\n");
    
    int targets[] = {1, 2, 3, 4, 5};
    int num_targets = sizeof(targets) / sizeof(targets[0]);
    
    for (int i = 0; i < num_targets; i++) {
        int freq = count_frequency(&elements, targets[i]);
        printf("Frequency of %d: %d\n", targets[i], freq);
    }
    
    free_array(&elements);
    return EXIT_SUCCESS;
}