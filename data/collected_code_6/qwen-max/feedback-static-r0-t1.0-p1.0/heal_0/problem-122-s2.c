#include <stdio.h>
#include <stdbool.h>

bool is_smart_number(int n) {
    int count = 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            if (i * i != n) count += 2;
            else count++;
        }
    }
    if (n > 1) count++;
    return count & (count - 1);
}

int find_nth_smart_number(int n) {
    int count = 0;
    int number = 1;
    while (true) {
        if (is_smart_number(number)) {
            count++;
            if (count == n) break;
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