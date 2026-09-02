#include <stdio.h>
#include <stdlib.h>

int count_digits(long num) {
    int count = 0;
    if (num == 0) return 1;
    while (num) {
        num /= 10;
        count++;
    }
    return count;
}

int have_same_number_of_digits(long a, long b) {
    return count_digits(a) == count_digits(b);
}

int main() {
    long a, b;
    scanf("%ld %ld", &a, &b);
    if (have_same_number_of_digits(a, b)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    return 0;
}