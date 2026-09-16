#include <stdio.h>
#include <stdbool.h>

bool is_even(int n) {
    return (n & 1) == 0;
}

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int sum_array(int *arr, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum;
}

void add_min_to_make_even(int *arr, int size, int *min_addition) {
    int sum = sum_array(arr, size);
    if (!is_even(sum)) {
        *min_addition = 1;
    } else {
        *min_addition = 0;
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    int min_addition;

    add_min_to_make_even(arr, size, &min_addition);

    printf("Minimum number to add to make the sum even: %d\n", min_addition);
    return 0;
}