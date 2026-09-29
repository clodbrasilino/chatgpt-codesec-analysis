#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'array' can be declared as pointer to const [constParameterPointer]
 */
int check_last_element(int *array, size_t size, int p) {
    if (array == NULL || size == 0) {
        exit(EXIT_FAILURE);
    }
    if (p < 0) {
        exit(EXIT_FAILURE);
    }
    long long last = array[size - 1];
    long long result = last + p;
    if (result % 2 == 0) {
        return 1;
    }
    return 0;
}

int main(void) {
    int arr[] = {1, 2, 3, 4, 5};
    size_t n = sizeof(arr) / sizeof(arr[0]);
    int p = 4;
    int is_even = check_last_element(arr, n, p);
    printf("%d\n", is_even);
    return 0;
}