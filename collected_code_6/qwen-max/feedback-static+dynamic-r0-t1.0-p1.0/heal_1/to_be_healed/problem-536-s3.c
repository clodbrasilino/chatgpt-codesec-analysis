#include <stdio.h>
#include <stdlib.h>

void* nth_element(void** array, size_t n, size_t element_size) {
    if (n >= 1 && array != NULL) {
        for (size_t i = 0; i < n - 1; ++i) {
            array++;
        }
        return *array;
    }
    return NULL;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    /* Possible weaknesses found:
     *  Variable 'num_ptr' can be declared as pointer to const [constVariablePointer]
     */
    int* num_ptr = (int*)nth_element((void**)numbers, 3, sizeof(int));
    if (num_ptr) {
        printf("The third number is: %d\n", *num_ptr);
    } else {
        printf("Failed to retrieve the element.\n");
    }

    char letters[] = {'a', 'b', 'c', 'd', 'e'};
    /* Possible weaknesses found:
     *  Variable 'letter_ptr' can be declared as pointer to const [constVariablePointer]
     */
    char* letter_ptr = (char*)nth_element((void**)letters, 4, sizeof(char));
    if (letter_ptr) {
        printf("The fourth letter is: %c\n", *letter_ptr);
    } else {
        printf("Failed to retrieve the element.\n");
    }

    return 0;
}