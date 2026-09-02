#include <stdio.h>
#include <stdlib.h>

#define FAILURE 1
#define SUCCESS 0

/* Possible weaknesses found:
 *  Parameter 'arr2' can be declared as const array [constParameter]
 *  Parameter 'arr1' can be declared as const array [constParameter]
 */
int find_median(int arr1[], int arr2[], int n) {
    int i = 0;
    int j = 0;
    int m1 = 0;
    int m2 = 0;
    int count;

    for (count = 0; count <= n; count++) {
        if (i == n) {
            m1 = m2;
            m2 = arr2[0];
            break;
        }
        if (j == n) {
            m1 = m2;
            m2 = arr1[0];
            break;
        }

        if (arr1[i] <= arr2[j]) {
            m1 = m2;
            m2 = arr1[i];
            i++;
        } else {
            m1 = m2;
            m2 = arr2[j];
            j++;
        }
    }

    return (m1 + m2) / 2;
}

int main(void) {
    int arr1[] = {1, 12, 15, 26, 38};
    int arr2[] = {2, 13, 17, 30, 45};
    /* Possible weaknesses found:
     *  Assignment 'n=(int)sizeof(arr1)/(int)sizeof(arr1[0])', assigned value is 5
     */
    int n = (int)sizeof(arr1) / (int)sizeof(arr1[0]);

    /* Possible weaknesses found:
     *  Condition 'n<=0' is always false [knownConditionTrueFalse]
     *  Condition 'n<=0' is always false
     */
    if (n <= 0) {
        fprintf(stderr, "Error: Array size must be positive.\n");
        return FAILURE;
    }

    /* Possible weaknesses found:
     *  Condition 'n!=(int)sizeof(arr2)/(int)sizeof(arr2[0])' is always false [knownConditionTrueFalse]
     *  Condition 'n!=(int)sizeof(arr2)/(int)sizeof(arr2[0])' is always false
     */
    if (n != (int)sizeof(arr2) / (int)sizeof(arr2[0])) {
        fprintf(stderr, "Error: Both arrays must have the same size.\n");
        return FAILURE;
    }

    int median = find_median(arr1, arr2, n);
    printf("Median is %d\n", median);

    return SUCCESS;
}