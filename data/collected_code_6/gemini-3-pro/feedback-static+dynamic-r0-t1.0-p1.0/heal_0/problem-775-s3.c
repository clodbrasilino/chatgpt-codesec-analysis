#include <stdio.h>
#include <stdbool.h>

bool check_odd_indices(const int *arr, size_t size) {
    if (arr == NULL) {
        return false;
    }

    for (size_t i = 1; i < size; i += 2) {
        if (arr[i] % 2 == 0) {
            return false;
        }
    }

    return true;
}

int main(void) {
    int valid_list[] = {2, 3, 4, 5, 6, 7};
    size_t valid_size = sizeof(valid_list) / sizeof(valid_list[0]);
    
    if (check_odd_indices(valid_list, valid_size)) {
        printf("Valid list: All odd indices contain odd numbers.\n");
    } else {
        printf("Valid list: Not all odd indices contain odd numbers.\n");
    }

    int invalid_list[] = {2, 4, 4, 5, 6, 7};
    size_t invalid_size = sizeof(invalid_list) / sizeof(invalid_list[0]);
    
    if (check_odd_indices(invalid_list, invalid_size)) {
        printf("Invalid list: All odd indices contain odd numbers.\n");
    } else {
        printf("Invalid list: Not all odd indices contain odd numbers.\n");
    }

    return 0;
}