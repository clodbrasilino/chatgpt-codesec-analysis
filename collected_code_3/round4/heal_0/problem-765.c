#include <stdio.h>

int nthPolite(int n) {
    int count = 0;
    for (int i = 1; ; i++) {
        if ((i & (i - 1)) != 0) {
            count++;
            if (count == n) {
                return i;
            }
        }
    }
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    printf("%dth polite number is %d\n", n, nthPolite(n));
    return 0;
}