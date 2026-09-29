#include<stdio.h>

int isPolite(int num) {
    int n = 1;
    while (n * (n + 1) * (n + 2) / 6 <= num)
        n++;
    return n;
}

int findNthPoliteNumber(int n) {
    int num = 1;
    int count = 0;
    
    while (count < n) {
        int pol = isPolite(num);
        if (pol == n)
            count++;
        num++;
    }
    return num - 1;
}

int main() {
    int n = 5;
    int nthPoliteNum = findNthPoliteNumber(n);
    printf("The %dth polite number is %d\n", n, nthPoliteNum);
    
    return 0;
}