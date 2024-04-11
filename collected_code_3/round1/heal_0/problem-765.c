#include <stdio.h>

int isPolite(int num) {
    while (num % 2 == 0) {
        num /= 2;
    }
    if (num == 1) {
        return 0;
    } else {
        return 1;
    }
}

int nthPolite(int n) {
    int count = 0;
    for (int i = 1; ; i++) {
        if (isPolite(i)) {
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
    printf("The %dth polite number is %d\n", n, nthPolite(n));
    return 0;
}