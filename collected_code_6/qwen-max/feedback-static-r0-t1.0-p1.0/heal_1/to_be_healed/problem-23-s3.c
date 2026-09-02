#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
int find_max_sum(int *list, int size) {
    /* Possible weaknesses found:
     *  The scope of the variable 'sum' can be reduced. [variableScope]
     */
    int max = INT_MIN, sum;
    for (int i = 0; i < size; ++i) {
        sum = 0;
        for (int j = 0; j < list[i]; ++j) {
            sum += list[i + 1 + j];
        }
        if (sum > max) max = sum;
        i += list[i];
    }
    return max;
}

int main() {
    int data[] = {3, 1, 2, 3, 4, 4, -1, 5, 2, 6, 7};
    int n_lists = 2;
    int result = find_max_sum(data, n_lists);
    printf("%d\n", result);
    return 0;
}