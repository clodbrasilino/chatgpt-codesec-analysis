#include <stdio.h>
#include <stdbool.h>

bool all_unique(const int *arr, size_t len) {
    for (size_t i = 0; i < len; i++) {
        for (size_t j = i + 1; j < len; j++) {
            if (arr[i] == arr[j]) {
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 2, 5};

    printf("%s\n", all_unique(a, sizeof(a) / sizeof(a[0])) ? "true" : "false");
    printf("%s\n", all_unique(b, sizeof(b) / sizeof(b[0])) ? "true" : "false");

    return 0;
}