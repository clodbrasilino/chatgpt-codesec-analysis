#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
size_t count_true(bool *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i]) {
            count++;
        }
    }
    return count;
}

int main(void) {
    bool arr[] = {true, false, true, true, false, true};
    size_t size = sizeof(arr) / sizeof(arr[0]);
    
    size_t result = count_true(arr, size);
    
    printf("%zu\n", result);
    
    return 0;
}