#include <stdio.h>

int isDistinct(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'arr[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'arr[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            if (arr[i] == arr[j]) {
                return 0; // Not distinct
            }
        }
    }
    return 1; // Distinct
}

int main() {
    int tuple[] = {2, 4, 6, 8, 10};
    int tupleSize = sizeof(tuple) / sizeof(tuple[0]);

    int result = isDistinct(tuple, tupleSize);

    if (result == 1) {
        printf("Tuple is distinct.");
    } else {
        printf("Tuple is not distinct.");
    }

    return 0;
}