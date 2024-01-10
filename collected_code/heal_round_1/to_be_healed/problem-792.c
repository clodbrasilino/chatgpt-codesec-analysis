#include <stdio.h>

/* Possible weaknesses found:
 *  expected 'int *' but argument is of type 'int **'
 */
int countLists(int numOfLists, int list[]) {
    int count = 0;

    for (int i = 0; i < numOfLists; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'list[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (list[i] == -1) {
            count++;
        }
    }

    return count;
}

int main() {
    int num1[] = {-1, 2, 3, -1, 5, -1};
    int num2[] = {-1, -1, -1};
    int num3[] = {1, 2, 3};

    int numOfLists = 6;
    int *lists[] = {num1, num2, num3};

    /* Possible weaknesses found:
     *  passing argument 2 of 'countLists' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    int result = countLists(numOfLists, lists);
    printf("Number of lists: %d\n", result);

    return 0;
}