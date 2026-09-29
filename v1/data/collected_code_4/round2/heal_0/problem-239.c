#include <stdio.h>

#define MAX 50
 
void num_of_seq (int n, int m, int &count) {
    if (n == 0) {
        count++;
        return;
    }

    int prev;
    if (m == 1) {
        prev = 1;
    } else {
        prev = m/2;
    }

    for (int i=prev; i>0; i--) {
        num_of_seq(n-1, i, count);
    }
}

int get_num_of_seq (int n, int m) {
    int count=0;
    num_of_seq(n, m, count);
    
    return count;
}

int main() {
    int n, m;
    printf("Enter sequence length: ");
    scanf("%d", &n);
    while (n <= 0) {
        printf("Sequence length should be greater than 0, please enter again: ");
        scanf("%d", &n);
    }
    printf("Enter maximum element value: ");
    scanf("%d", &m);
    while (m <= 0) {
        printf("Maximum element value should be greater than 0, please enter again: ");
        scanf("%d", &m);
    }
    printf("Number of possible sequences: %d\n", get_num_of_seq(n, m));

    return 0;
}