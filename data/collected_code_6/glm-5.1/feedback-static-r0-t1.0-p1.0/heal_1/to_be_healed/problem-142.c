#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'a' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'c' can be declared as pointer to const [constParameterPointer]
 *  Parameter 'b' can be declared as pointer to const [constParameterPointer]
 */
int count_same_pair(int *a, int *b, int *c, int na, int nb, int nc) {
    int count = 0;
    int i = 0, j = 0, k = 0;

    while (i < na && j < nb && k < nc) {
        if (a[i] == b[j] && b[j] == c[k]) {
            count++;
            i++;
            j++;
            k++;
        } else if (a[i] <= b[j] && a[i] <= c[k]) {
            i++;
        } else if (b[j] <= a[i] && b[j] <= c[k]) {
            j++;
        } else {
            k++;
        }
    }

    return count;
}

int main(void) {
    int a[] = {1, 5, 10, 20, 40, 80};
    int b[] = {6, 7, 20, 80, 100};
    int c[] = {3, 4, 15, 20, 30, 70, 80, 120};

    /* Possible weaknesses found:
     *  Assignment 'na=sizeof(a)/sizeof(a[0])', assigned value is 6
     */
    int na = sizeof(a) / sizeof(a[0]);
    /* Possible weaknesses found:
     *  Assignment 'nb=sizeof(b)/sizeof(b[0])', assigned value is 5
     */
    int nb = sizeof(b) / sizeof(b[0]);
    /* Possible weaknesses found:
     *  Assignment 'nc=sizeof(c)/sizeof(c[0])', assigned value is 8
     */
    int nc = sizeof(c) / sizeof(c[0]);

    /* Possible weaknesses found:
     *  Condition 'nc==0' is always false
     *  Condition 'nb==0' is always false
     *  Condition 'na==0' is always false [knownConditionTrueFalse]
     *  Condition 'nb==0' is always false [knownConditionTrueFalse]
     *  Condition 'nc==0' is always false [knownConditionTrueFalse]
     *  Condition 'na==0' is always false
     */
    if (na == 0 || nb == 0 || nc == 0) {
        return 1;
    }

    int result = count_same_pair(a, b, c, na, nb, nc);

    printf("%d\n", result);

    return 0;
}