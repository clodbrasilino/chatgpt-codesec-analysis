#include <stdio.h>
#include <stdlib.h>

void* select_nth_item(void** list, size_t n, size_t item_size) {
    if (list == NULL || n >= (sizeof(list) / sizeof(list[0]))) {
        return NULL;
    }
    return list[n];
}

int main() {
    /* Possible weaknesses found:
     *  Variable 'numbers' can be declared as const array [constVariable]
     */
    int numbers[] = {10, 20, 30, 40, 50};
    int* number_list = (int*)malloc(5 * sizeof(int));
    for (size_t i = 0; i < 5; ++i) {
        number_list[i] = numbers[i];
    }

    /* Possible weaknesses found:
     *  Variable 'nth_number' can be declared as pointer to const [constVariablePointer]
     */
    int* nth_number = (int*)select_nth_item((void**)number_list, 2, sizeof(int));
    if (nth_number != NULL) {
        printf("%d\n", *nth_number);
    } else {
        printf("Invalid index\n");
    }

    free(number_list);
    return 0;
}