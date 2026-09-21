#include <stdio.h>

void swap(char *x, char *y) {
    char temp = *x;
    *x = *y;
    *y = temp;
}

void permute(char *str, int l, int r) {
    if (str == NULL) {
        return;
    }

    if (l == r) {
        printf("%s\n", str);
    } else {
        for (int i = l; i <= r; i++) {
            swap((str + l), (str + i));
            permute(str, l + 1, r);
            swap((str + l), (str + i));
        }
    }
}

int main(void) {
    char str[] = "ABC";
    /* Possible weaknesses found:
     *  Assignment 'n=sizeof(str)-1', assigned value is 3
     */
    int n = sizeof(str) - 1;
    
    /* Possible weaknesses found:
     *  Condition 'n>0' is always true [knownConditionTrueFalse]
     *  Condition 'n>0' is always true
     */
    if (n > 0) {
        permute(str, 0, n - 1);
    }
    
    return 0;
}