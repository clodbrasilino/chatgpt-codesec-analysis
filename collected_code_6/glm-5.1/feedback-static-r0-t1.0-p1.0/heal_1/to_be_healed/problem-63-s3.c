#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'pairs' can be declared as pointer to const [constParameterPointer]
 */
int find_max_diff(int *pairs, int count) {
    if (pairs == NULL || count < 2) {
        return 0;
    }
    
    int min_val = pairs[0];
    int max_diff = pairs[1] - pairs[0];
    
    for (int i = 1; i < count; i++) {
        int diff = pairs[i] - min_val;
        if (diff > max_diff) {
            max_diff = diff;
        }
        if (pairs[i] < min_val) {
            min_val = pairs[i];
        }
    }
    
    return max_diff;
}

int main() {
    int tuples[] = {2, 3, 10, 6, 4, 8, 1};
    int count = sizeof(tuples) / sizeof(tuples[0]);
    
    int result = find_max_diff(tuples, count);
    printf("%d\n", result);
    
    return 0;
}