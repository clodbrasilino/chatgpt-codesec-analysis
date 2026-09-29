#include <stdio.h>

#define MAX_LEN 100

int maxSum(int tri[][MAX_LEN], int m) {
    for (int i=m-1; i>=0; i--) {
        for (int j=0; j<=i; j++) {
            if (tri[j][i+1] > tri[j+1][i+1]) {
                tri[j][i] += tri[j][i+1];
            } else {
                tri[j][i] += tri[j+1][i+1];
            }
        }
    }
    return tri[0][0];
}

int main () {
    int triangle[MAX_LEN][MAX_LEN] = {
        {3, 0, 0, 0},
        {7, 4, 0, 0},
        {2, 4, 6, 0},
        {8, 5, 9, 3}
    };
    printf("Max Sum: %d\n", maxSum(triangle, 4));
    return 0;
}