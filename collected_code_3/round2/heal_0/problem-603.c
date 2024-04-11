#include <stdio.h>

int getLucidNumber(int n) {
    int lucid = 2;
    int i, j;
    int lucidArray[1000] = {0};

    for(i = 1; i < n; i++) {
        lucidArray[i] = i;
    }

    for(i = 1; i < n; i++) {
        if(lucidArray[i] != -1) {
            lucid = lucidArray[i];
            for(j = lucid; j <= n; j += lucid+1) {
                lucidArray[j] = -1;
            }
        }
    }

    while(lucidArray[lucid] == -1) {
        lucid--;
    }

    return lucid;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("The largest lucid number less than or equal to %d is %d\n", n, getLucidNumber(n));
    return 0;
}