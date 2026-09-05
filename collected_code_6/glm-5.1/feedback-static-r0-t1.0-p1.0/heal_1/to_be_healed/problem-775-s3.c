#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int check_odd_indices(int *list, size_t size) {
    if (list == NULL) {
        return 0;
    }
    for (size_t i = 1; i < size; i += 2) {
        if (list[i] % 2 == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    int list1[] = {2, 3, 4, 7, 6, 9};
    int list2[] = {1, 2, 3, 5, 5, 11};
    int list3[] = {0};

    int result1 = check_odd_indices(list1, sizeof(list1) / sizeof(list1[0]));
    int result2 = check_odd_indices(list2, sizeof(list2) / sizeof(list2[0]));
    int result3 = check_odd_indices(list3, sizeof(list3) / sizeof(list3[0]));
    int result4 = check_odd_indices(NULL, 0);

    printf("Result 1: %d\n", result1);
    printf("Result 2: %d\n", result2);
    printf("Result 3: %d\n", result3);
    printf("Result 4: %d\n", result4);

    return 0;
}