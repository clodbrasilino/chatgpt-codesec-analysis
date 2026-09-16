#include <stdio.h>
#include <stdlib.h>

int find_last_removed_position(const int *original_array, size_t original_size, const int *current_array, size_t current_size) {
    if (original_array == NULL || current_array == NULL) {
        return -1;
    }
    
    if (original_size == 0 || current_size >= original_size || original_size - current_size != 1) {
        return -1;
    }

    size_t i = 0;
    while (i < current_size && original_array[i] == current_array[i]) {
        i++;
    }

    return (int)i;
}

int main() {
    int original[] = {10, 20, 30, 40, 50};
    int current[] = {10, 20, 40, 50};
    
    size_t original_size = sizeof(original) / sizeof(original[0]);
    size_t current_size = sizeof(current) / sizeof(current[0]);

    int pos = find_last_removed_position(original, original_size, current, current_size);

    if (pos != -1) {
        printf("%d\n", pos);
    } else {
        printf("-1\n");
    }

    return 0;
}