#include <stdio.h>
#include <stdlib.h>

void* nth_element(void* array, size_t n, size_t element_size) {
    if (n > 0 && array != NULL) {
        return (char*)array + (n - 1) * element_size;
    }
    return NULL;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    int* num_ptr = (int*)nth_element(numbers, 3, sizeof(int));
    if (num_ptr) {
        printf("The third number is: %d\n", *num_ptr);
    } else {
        printf("Failed to retrieve the element.\n");
    }

    char letters[] = {'a', 'b', 'c', 'd', 'e'};
    char* letter_ptr = (char*)nth_element(letters, 4, sizeof(char));
    if (letter_ptr) {
        printf("The fourth letter is: %c\n", *letter_ptr);
    } else {
        printf("Failed to retrieve the element.\n");
    }

    return 0;
}