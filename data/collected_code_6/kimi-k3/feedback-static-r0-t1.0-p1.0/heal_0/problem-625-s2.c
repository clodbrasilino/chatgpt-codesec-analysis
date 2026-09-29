#include <stdio.h>
#include <stdlib.h>

void interchange_first_last(int *list, size_t size)
{
    int temp;
    
    if (list == NULL || size == 0) {
        return;
    }
    
    temp = list[0];
    list[0] = list[size - 1];
    list[size - 1] = temp;
}

int main(void)
{
    int list[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(list) / sizeof(list[0]);
    size_t i;
    
    printf("Original list: ");
    for (i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    
    interchange_first_last(list, size);
    
    printf("Modified list: ");
    for (i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    
    return 0;
}