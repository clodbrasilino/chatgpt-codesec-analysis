#include <stdio.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'arr' can be declared as pointer to const [constParameterPointer]
 */
int find_max_sublist_length(int *arr, int size) {
    if (size <= 0) return 0;

    int max_length = 1;
    int current_length = 1;

    for (int i = 1; i < size; ++i) {
        if (arr[i] >= arr[i - 1]) {
            current_length++;
        } else {
            if (current_length > max_length) {
                max_length = current_length;
            }
            current_length = 1;
        }
    }

    if (current_length > max_length) {
        max_length = current_length;
    }

    return max_length;
}

int main() {
    int arr[] = {1, 2, 3, 2, 5, 2, 3, 4, 5, 1};
    int size = sizeof(arr) / sizeof(arr[0]);
    int max_length = find_max_sublist_length(arr, size);
    printf("Maximum length of sublist: %d\n", max_length);
    return 0;
}