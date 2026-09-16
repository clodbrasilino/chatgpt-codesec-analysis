#include <stdio.h>
#include <stdlib.h>

void* nth_element(const void** array, size_t n, size_t element_size) {
    if (n >= 1 && array != NULL) {
        for (size_t i = 0; i < n - 1; ++i) {
            array = (const void**)((const char**)array + element_size);
        }
        return (void*)*array;
    }
    return NULL;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    const int* num_ptr = (const int*)nth_element((const void**)numbers, 3, sizeof(int));
    if (num_ptr) {
        printf("The third number is: %d\n", *num_ptr);
    } else {
        printf("Failed to retrieve the element.\n");
    }

    char letters[] = {'a', 'b', 'c', 'd', 'e'};
    const char* letter_ptr = (const char*)nth_element((const void**)letters, 4, sizeof(char));
    if (letter_ptr) {
        printf("The fourth letter is: %c\n", *letter_ptr);
    } else {
        printf("Failed to retrieve the element.\n");
    }

    return 0;
}