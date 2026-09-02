#include <stdio.h>
#include <stdlib.h>

void* select_nth_item(void** list, size_t n, size_t item_size) {
    if (list == NULL || n >= 1000) {
        return NULL;
    }
    return (char*)list + n * item_size;
}

int main() {
    int numbers[] = {10, 20, 30, 40, 50};
    /* Possible weaknesses found:
     *  Variable 'selected_number' can be declared as pointer to const [constVariablePointer]
     */
    int* selected_number = (int*)select_nth_item((void**)numbers, 2, sizeof(int));
    if (selected_number != NULL) {
        printf("%d\n", *selected_number);
    } else {
        printf("Invalid index or list is null.\n");
    }
    return 0;
}