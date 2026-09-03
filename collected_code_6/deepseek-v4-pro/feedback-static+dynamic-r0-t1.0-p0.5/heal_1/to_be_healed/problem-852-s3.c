#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int *remove_negative(int *list, int size, int *new_size) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] >= 0) {
            count++;
        }
    }
    
    int *result = (int *)malloc(count * sizeof(int));
    if (result == NULL && count > 0) {
        *new_size = 0;
        return NULL;
    }
    
    int index = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] >= 0) {
            result[index++] = list[i];
        }
    }
    
    *new_size = count;
    return result;
}

int main(void) {
    int list[] = {5, -3, 8, -1, 0, 7, -6, 4};
    int size = sizeof(list) / sizeof(list[0]);
    int new_size = 0;
    
    int *filtered = remove_negative(list, size, &new_size);
    if (filtered == NULL && new_size > 0) {
        return 1;
    }
    
    for (int i = 0; i < new_size; i++) {
        printf("%d ", filtered[i]);
    }
    printf("\n");
    
    free(filtered);
    return 0;
}