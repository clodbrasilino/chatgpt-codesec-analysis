#include <stdio.h>
#include <stdlib.h>

int* find_even_numbers(const int* list, size_t size, size_t* even_count) {
    int* evens = NULL;
    size_t count = 0;
    
    if (list == NULL || even_count == NULL) {
        return NULL;
    }
    
    evens = (int*)malloc(size * sizeof(int));
    if (evens == NULL) {
        *even_count = 0;
        return NULL;
    }
    
    for (size_t i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            evens[count] = list[i];
            count++;
        }
    }
    
    if (count == 0) {
        free(evens);
        *even_count = 0;
        return NULL;
    }
    
    int* resized = (int*)realloc(evens, count * sizeof(int));
    if (resized == NULL) {
        free(evens);
        *even_count = 0;
        return NULL;
    }
    
    *even_count = count;
    return resized;
}

int main(void) {
    int mixed_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t list_size = sizeof(mixed_list) / sizeof(mixed_list[0]);
    size_t even_count = 0;
    
    int* evens = find_even_numbers(mixed_list, list_size, &even_count);
    
    if (evens != NULL) {
        printf("Even numbers: ");
        for (size_t i = 0; i < even_count; i++) {
            printf("%d ", evens[i]);
        }
        printf("\n");
        free(evens);
    } else {
        printf("No even numbers found or error occurred.\n");
    }
    
    return 0;
}