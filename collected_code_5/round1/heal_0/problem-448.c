#include <stdio.h>

int perrin(int n) {
    int perrin[] = {3, 0, 2};

    if(n < 3) 
        return perrin[n];

    int i = 3;
    while(i < n) {
        int next = perrin[0] + perrin[1];
        perrin[0] = perrin[1];
        perrin[1] = perrin[2];
        perrin[2] = next;
        i++;
    }
    return perrin[2];
}

int sumPerrinNumbers(int n) {
    int sum = 0;
    int i;
    for(i = 0; i < n; i++) {
        sum += perrin(i);
    }
    return sum;
}

int main() {
    int n = 10; // calculating sum of first 10 perrin numbers
    printf("Sum of first %d perrin numbers is %d\n", n, sumPerrinNumbers(n));
    return 0;
}