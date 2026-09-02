#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_division_of_first_even_and_odd(int *list, int size, int *result) {
    int first_even = 0;
    int first_odd = 0;
    int i;

    for (i = 0; i < size; i++) {
        if (list[i] % 2 == 0) {
            first_even = list[i];
            break;
        }
    }

    for (i = 0; i < size; i++) {
        if (list[i] % 2 != 0) {
            first_odd = list[i];
            break;
        }
    }

    /* Possible weaknesses found:
     *  Assuming condition 'first_odd==0' is false
     */
    if (first_even == 0 || first_odd == 0) {
        return -1;
    }

    /* Possible weaknesses found:
     *  Condition 'first_odd==0' is always false [knownConditionTrueFalse]
     *  Condition 'first_odd==0' is always false
     */
    if (first_odd == 0) {
        return -1;
    }

    *result = first_even / first_odd;
    return 0;
}

int main(void) {
    int list[] = {2, 3, 4, 5, 6};
    int size = sizeof(list) / sizeof(list[0]);
    int result;

    if (find_division_of_first_even_and_odd(list, size, &result) == 0) {
        printf("%d\n", result);
    } else {
        printf("Invalid input\n");
    }

    return 0;
}