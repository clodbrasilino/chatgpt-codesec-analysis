#include <stdio.h>

int getLucid(int n) {
    int lucid = 2;
    int count = 1;
    while (lucid <= n) {
        count++;
        lucid = count + 2;
        if (count % 3 != 0) {
            lucid = count;
        }
    }
    return lucid;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The largest lucid number less than or equal to %d is %d\n", n, getLucid(n));
    return 0;
}