#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_smallest(int *list, size_t size) {
    if (list == NULL || size == 0) {
        fprintf(stderr, "Error: Invalid input\n");
        exit(EXIT_FAILURE);
    }
    
    int smallest = INT_MAX;
    for (size_t i = 0; i < size; i++) {
        if (list[i] < smallest) {
            smallest = list[i];
        }
    }
    return smallest;
}

int main(void) {
    int test_list[] = {42, 17, 89, 3, 56, 23};
    size_t test_size = sizeof(test_list) / sizeof(test_list[0]);
    
    int result = find_smallest(test_list, test_size);
    printf("Smallest number: %d\n", result);
    
    return 0;
}