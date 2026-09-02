#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int *find_even_numbers(int *list, int size, int *even_count) {
    /* Possible weaknesses found:
     *  Assuming that condition 'even_count==NULL' is not redundant
     */
    if (list == NULL || size <= 0 || even_count == NULL) {
        /* Possible weaknesses found:
         *  Either the condition 'even_count==NULL' is redundant or there is possible null pointer dereference: even_count. [nullPointerRedundantCheck]
         *  Null pointer dereference
         */
        *even_count = 0;
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            count++;
        }
    }

    if (count == 0) {
        *even_count = 0;
        return NULL;
    }

    int *even_numbers = (int *)malloc(count * sizeof(int));
    if (even_numbers == NULL) {
        *even_count = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            even_numbers[index++] = list[i];
        }
    }

    *even_count = count;
    return even_numbers;
}

int main(void) {
    int mixed_list[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(mixed_list) / sizeof(mixed_list[0]);
    int even_count = 0;

    int *even_list = find_even_numbers(mixed_list, size, &even_count);
    
    if (even_list != NULL) {
        printf("Even numbers: ");
        for (int i = 0; i < even_count; i++) {
            printf("%d ", even_list[i]);
        }
        printf("\n");
        free(even_list);
    } else {
        printf("No even numbers found or invalid input.\n");
    }

    return 0;
}