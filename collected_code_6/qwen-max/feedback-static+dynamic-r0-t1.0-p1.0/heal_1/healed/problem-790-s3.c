#include <stdio.h>
#include <stdbool.h>

bool is_even(int n) {
    return (n % 2 == 0);
}

bool check_even_indices(const int *arr, int size) {
    for (int i = 0; i < size; i += 2) {
        if (!is_even(arr[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    int arr[] = {2, 3, 4, 5, 6, 7};
    int size = sizeof(arr) / sizeof(arr[0]);

    if (check_even_indices(arr, size)) {
        printf("All even indices contain even numbers.\n");
    } else {
        printf("Not all even indices contain even numbers.\n");
    }

    return 0;
}