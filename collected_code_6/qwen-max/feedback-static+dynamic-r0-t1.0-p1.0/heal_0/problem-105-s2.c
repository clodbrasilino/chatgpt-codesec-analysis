#include <stdio.h>
#include <stdbool.h>

int count_true_booleans(const bool *arr, size_t len) {
    if (arr == NULL || len == 0) {
        return 0;
    }
    int count = 0;
    for (size_t i = 0; i < len; ++i) {
        if (arr[i]) {
            ++count;
        }
    }
    return count;
}

int main() {
    bool arr[] = {true, false, true, true, false};
    size_t len = sizeof(arr) / sizeof(arr[0]);
    int true_count = count_true_booleans(arr, len);
    printf("Number of true booleans: %d\n", true_count);
    return 0;
}