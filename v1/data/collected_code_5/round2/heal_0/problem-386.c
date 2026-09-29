#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int min_swaps_for_balancing(char *expr) {
    int len = strlen(expr);
    int i, j;
  
    if (len % 2) return -1;
  
    int left_brackets = 0;
    int swaps = 0;
    int imbalance = 0;

    for (i = 0; i < len; i++) {
        if (expr[i] == '{') {
            left_brackets++;
            imbalance++;
        } else if (expr[i] == '}') {
            if (left_brackets == 0) {
                left_brackets++;
                imbalance++;
            } else {
                left_brackets--;
            }
        }
    }
    
    swaps = imbalance / 2;
  
    return swaps;
}

int main() {
    char expr[] = "{{{{{}}}";
    int min_swaps = min_swaps_for_balancing(expr);
  
    if (min_swaps != -1)
        printf("Minimum no of swaps required for bracket balancing in the given string is %d", min_swaps);
    else
        printf("The expression is unbalanced");

    return 0;
}