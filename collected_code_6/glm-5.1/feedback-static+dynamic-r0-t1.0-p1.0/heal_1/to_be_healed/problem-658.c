#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_max_occurrence(int *list, size_t size) {
    if (list == NULL || size == 0) {
        return INT_MIN;
    }

    size_t max_count = 0;
    int max_item = list[0];

    for (size_t i = 0; i < size; i++) {
        size_t current_count = 0;

        for (size_t j = 0; j < size; j++) {
            if (list[i] == list[j]) {
                current_count++;
            }
        }

        if (current_count > max_count) {
            max_count = current_count;
            max_item = list[i];
        }
    }

    return max_item;
}

int main(void) {
    int list[] = {1, 3, 2, 3, 4, 3, 2, 2, 2};
    size_t size = sizeof(list) / sizeof(list[0]);

    int result = find_max_occurrence(list, size);

    printf("%d\n", result);

    return 0;
}