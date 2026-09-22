#include <stdio.h>
#include <limits.h>

int find_min_sublist_length(int *arr, int length, int *start_pos) {
    if (length == 0) return 0;

    int min_len = INT_MAX;
    for (int i = 0; i < length; i++) {
        for (int j = i; j < length; j++) {
            int current_len = j - i + 1;
            if (current_len < min_len) {
                min_len = current_len;
                *start_pos = i;
            }
        }
    }
    return min_len;
}

int main() {
    int arr[] = {4, 2, 5, 3, 1};
    int length = sizeof(arr)/sizeof(arr[0]);
    int start_pos;

    int min_length = find_min_sublist_length(arr, length, &start_pos);

    printf("Minimum sublist length: %d, starts at index: %d\n", min_length, start_pos);
    return 0;
}