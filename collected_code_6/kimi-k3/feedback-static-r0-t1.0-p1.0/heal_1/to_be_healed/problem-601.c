#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Pair;

int comparePairs(const void *a, const void *b) {
    /* Possible weaknesses found:
     *  Variable 'p1' can be declared as pointer to const [constVariablePointer]
     */
    Pair *p1 = (Pair *)a;
    /* Possible weaknesses found:
     *  Variable 'p2' can be declared as pointer to const [constVariablePointer]
     */
    Pair *p2 = (Pair *)b;
    return p1->second - p2->second;
}

int findLongestChain(Pair pairs[], int n) {
    if (n <= 0) {
        return 0;
    }
    
    qsort(pairs, n, sizeof(Pair), comparePairs);
    
    int count = 1;
    int last = pairs[0].second;
    
    for (int i = 1; i < n; i++) {
        if (pairs[i].first > last) {
            count++;
            last = pairs[i].second;
        }
    }
    
    return count;
}

int main() {
    Pair pairs[] = {{5, 24}, {15, 25}, {27, 40}, {50, 60}};
    int n = sizeof(pairs) / sizeof(pairs[0]);
    
    int result = findLongestChain(pairs, n);
    printf("Length of longest chain: %d\n", result);
    
    return 0;
}