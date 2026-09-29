#include <stdio.h>

int findMaxDifference(int tupleList[], int n) {
    int maxDiff = -1;
    
    for(int i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            /* Possible weaknesses found:
             *  Cannot determine that 'tupleList[i]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             *  Cannot determine that 'tupleList[j]' is initialized (since function parameter is not 'const' it is assumed it points at uninitialized data) [premium-bughuntingUninitNonConstArg]
             */
            int diff = tupleList[j] - tupleList[i];
            if(diff > maxDiff)
                maxDiff = diff;
        }
    }
    
    return maxDiff;
}

int main() {
    int tupleList[] = {1, 4, 7, 2, 10};
    int n = sizeof(tupleList)/sizeof(tupleList[0]);

    int maxDiff = findMaxDifference(tupleList, n);
    
    printf("Maximum difference between available pairs: %d\n", maxDiff);
    
    return 0;
}