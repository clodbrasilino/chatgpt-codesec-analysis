#include <stdio.h>
#include <stdlib.h>

int find_element_count(const int *tuple, size_t size, int target) {
    for (size_t i = 0; i < size; i++) {
        if (tuple[i] == target) {
            return (int)i;
        }
    }
    return -1;
}

int main() {
    int tuple[] = {5, 3, 8, 2, 9};
    size_t size = sizeof(tuple) / sizeof(tuple[0]);
    int target = 8;
    int result = find_element_count(tuple, size, target);
    printf("%d\n", result);
    return 0;
}