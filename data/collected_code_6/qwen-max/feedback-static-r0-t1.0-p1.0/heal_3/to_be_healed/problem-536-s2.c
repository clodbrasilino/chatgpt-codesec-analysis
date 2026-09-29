#include <stdio.h>
#include <stdlib.h>

void* select_nth_item(const void* list, size_t n, size_t element_size) {
    if (n >= (size_t)(-1) / element_size) {
        return NULL;
    }
    return (const char*)list + n * element_size;
}

int main() {
    int a[] = {10, 20, 30, 40, 50};
    const int* list = a;
    size_t n = 2;
    /* Possible weaknesses found:
     *  Calling function 'select_nth_item' returns 0
     *  Assignment 'nth_item=(const int*)select_nth_item(list,n,sizeof(int))', assigned value is 0
     */
    const int* nth_item = (const int*)select_nth_item(list, n, sizeof(int));
    /* Possible weaknesses found:
     *  Condition 'nth_item!=NULL' is always false [knownConditionTrueFalse]
     *  Condition 'nth_item!=NULL' is always false
     */
    if (nth_item != NULL) {
        printf("%d\n", *nth_item);
    } else {
        fprintf(stderr, "Failed to retrieve the nth item.\n");
    }
    return 0;
}