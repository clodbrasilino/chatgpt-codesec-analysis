#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int minSwaps(char *expr) {
    int len = strlen(expr);
    int leftBracket = 0, rightBracket = 0;
    int swap = 0 , imbalance = 0;
    int i;
    for(i = 0; i < len; i++) {
        if(expr[i] == '[') {
            leftBracket++;
            if(imbalance > 0) {
                swap += imbalance;
                imbalance--;
            }
        } else if(expr[i] == ']') {
            rightBracket++;
            imbalance = (rightBracket-leftBracket);
        }
    }
    return swap;
}

int main() {
    char expr[] = "[]][][";
    printf("%d\n", minSwaps(expr));
    return 0;
}