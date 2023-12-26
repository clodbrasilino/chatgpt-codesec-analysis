#include <stdio.h>
#include <stdbool.h>

void tupleIntersection(int arr1[], int arr2[], int size1, int size2) {
    bool found;

    for (int i = 0; i < size1; i++) {
        found = false;

        for (int j = 0; j < size2; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr2[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr1[i] == arr2[j]) {
                found = true;
                break;
            }
        }

        if (found) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr1[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            printf("%d\n", arr1[i]);
        }
    }
}

int main() {
    int tuple1[] = {1, 2, 3, 4, 5};
    int tuple2[] = {4, 5, 6, 7};

    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    tupleIntersection(tuple1, tuple2, size1, size2);

    return 0;
}