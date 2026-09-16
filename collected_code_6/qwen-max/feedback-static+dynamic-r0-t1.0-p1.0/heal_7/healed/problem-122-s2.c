#include <stdio.h>
#include <stdbool.h>

bool is_smart_number(int n) {
    int count = 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n) {
                count += 2;
            } else {
                count++;
            }
        }
    }
    if (n > 1 && count == 0) count = 1;
    return (count & (count - 1)) == 0 && count > 0;
}

int find_nth_smart_number(int n) {
    int count = 1;
    int number = 4;
    while (true) {
        if (is_smart_number(number)) {
            if (count == n) break;
            count++;
        }
        number++;
    }
    return number;
}

int main() {
    int n;
    printf("Enter the value of n: ");
    scanf("%d", &n);
    int nth_smart_number = find_nth_smart_number(n);
    printf("The %dth smart number is: %d\n", n, nth_smart_number);
    return 0;
}