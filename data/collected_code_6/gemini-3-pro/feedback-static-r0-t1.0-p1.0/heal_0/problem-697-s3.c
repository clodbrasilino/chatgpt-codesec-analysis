#include <stdio.h>
#include <stdlib.h>

size_t count_even_elements(const int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }

    size_t count = 0;
    for (size_t i = 0; i < size; ++i) {
        if (list[i] % 2 == 0) {
            count++;
        }
    }

    return count;
}

int main(void) {
    size_t size = 5;
    int *list = (int *)malloc(size * sizeof(int));
    
    if (list == NULL) {
        return 1;
    }

    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    list[3] = 4;
    list[4] = 6;

    size_t even_count = count_even_elements(list, size);
    
    printf("%zu\n", even_count);

    free(list);
    list = NULL;

    return 0;
}