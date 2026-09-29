#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
void print_negative_numbers(int *list, size_t size) {
    if (list == NULL) {
        return;
    }
    for (size_t i = 0; i < size; i++) {
        if (list[i] < 0) {
            printf("%d\n", list[i]);
        }
    }
}

int main(void) {
    int list[] = {3, -1, 4, -1, 5, -9, 2, -6, 5, 3, 0};
    size_t size = sizeof(list) / sizeof(list[0]);
    print_negative_numbers(list, size);
    return 0;
}