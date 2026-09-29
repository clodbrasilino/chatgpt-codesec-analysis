#include <stdio.h>
#include <stdlib.h>

void* select_nth_item(void** list, size_t n, size_t element_size) {
    if (n >= ((size_t)(-1) / element_size)) {
        return NULL;
    }
    return (char*)list + n * element_size;
}

int main() {
    int a[] = {10, 20, 30, 40, 50};
    int* list = a;
    size_t n = 2;

    /* Possible weaknesses found:
     *  Assignment 'nth_item=(int*)select_nth_item((void**)list,n,sizeof(int))', assigned value is 0
     *  Calling function 'select_nth_item' returns 0
     *  Variable 'nth_item' can be declared as pointer to const [constVariablePointer]
     */
    int* nth_item = (int*)select_nth_item((void**)list, n, sizeof(int));
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