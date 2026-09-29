#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int check_even_indices_even(int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }
    for (size_t i = 0; i < size; i += 2) {
        if (list[i] % 2 != 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int list1[] = {2, 1, 4, 3, 6, 5};
    size_t size1 = sizeof(list1) / sizeof(list1[0]);
    int result1 = check_even_indices_even(list1, size1);
    printf("%d\n", result1);

    int list2[] = {2, 1, 3, 3, 6, 5};
    size_t size2 = sizeof(list2) / sizeof(list2[0]);
    int result2 = check_even_indices_even(list2, size2);
    printf("%d\n", result2);

    int *list3 = NULL;
    size_t size3 = 0;
    int result3 = check_even_indices_even(list3, size3);
    printf("%d\n", result3);

    return 0;
}