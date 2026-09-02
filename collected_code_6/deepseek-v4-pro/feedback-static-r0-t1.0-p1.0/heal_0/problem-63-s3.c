#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int available;
} Pair;

int max_pair_difference(Pair *pairs, int size) {
    int max_diff = -1;
    
    for (int i = 0; i < size - 1; i++) {
        if (!pairs[i].available) continue;
        
        for (int j = i + 1; j < size; j++) {
            if (!pairs[j].available) continue;
            
            int diff1 = abs(pairs[i].first - pairs[j].first);
            int diff2 = abs(pairs[i].second - pairs[j].second);
            int diff3 = abs(pairs[i].first - pairs[j].second);
            int diff4 = abs(pairs[i].second - pairs[j].first);
            
            int current_max = diff1;
            if (diff2 > current_max) current_max = diff2;
            if (diff3 > current_max) current_max = diff3;
            if (diff4 > current_max) current_max = diff4;
            
            if (current_max > max_diff) {
                max_diff = current_max;
            }
        }
    }
    
    return max_diff;
}

int main(void) {
    Pair pairs[] = {
        {1, 2, 1},
        {3, 5, 1},
        {7, 8, 0},
        {10, 12, 1},
        {4, 6, 1}
    };
    
    int size = sizeof(pairs) / sizeof(pairs[0]);
    int result = max_pair_difference(pairs, size);
    
    if (result == -1) {
        printf("No valid pairs found\n");
    } else {
        printf("Maximum difference: %d\n", result);
    }
    
    return 0;
}