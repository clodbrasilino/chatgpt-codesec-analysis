#include <stdio.h>
#include <limits.h>

int find_largest_negative(const int *list, size_t size) {
    int largest_negative = INT_MIN;
    int found = 0;

    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            if (!found || list[i] > largest_negative) {
                largest_negative = list[i];
                found = 1;
            }
        }
    }

    if (!found) {
        return 0;
    }

    return largest_negative;
}

int main(void) {
    int list[] = {3, -1, -4, 1, -5, 9, -2, 6, 5, 0};
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = find_largest_negative(list, size);
    
    printf("%d\n", result);

    return 0;
}