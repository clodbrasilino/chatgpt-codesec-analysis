#include <stdio.h>
#include <math.h>

int isSmartNumber(int num) {
    int val = (int)sqrt(num);
    return (val*val == num);
}

int nthSmartNumber(int n) {
    int count = 0;
    for (int i = 1; ; i++) {
        if (isSmartNumber(i))
            count++;
        if (count == n)
            return i;
    }
}

int main() {
    int n = 5;
    printf("%d", nthSmartNumber(n));
    return 0;
}