#include <stdio.h>

int checkTuples(int n, int first[], int second[]) {
    for (int i = 0; i < n; i++) {
        /* Possible weaknesses found:
         *  Cannot determine that 'second[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         *  Cannot determine that 'first[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
         */
        if (second[i] >= i && first[i] >= second[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int first[] = {2, 3, 4};
    int second[] = {1, 2, 3};
    int n = sizeof(first) / sizeof(first[0]);

    if (checkTuples(n, first, second)) {
        printf("Each element of second tuple is smaller than its corresponding index in first tuple.\n");
    } else {
        printf("Not all elements of second tuple are smaller than their corresponding index in first tuple.\n");
    }
    
    return 0;
}