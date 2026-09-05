#include <stdio.h>
#include <stdlib.h>

int count_negatives(int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    int count = 0;
    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            count++;
        }
    }

    return count;
}

int main(void) {
    int list[] = {1, -2, 3, -4, 5, -6, 0};
    size_t size = sizeof(list) / sizeof(list[0]);
    
    int result = count_negatives(list, size);
    
    printf("%d\n", result);
    
    return EXIT_SUCCESS;
}