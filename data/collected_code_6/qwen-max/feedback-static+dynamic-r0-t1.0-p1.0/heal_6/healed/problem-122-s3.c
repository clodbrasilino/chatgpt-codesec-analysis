#include <stdio.h>
#include <stdbool.h>

bool is_smart_number(int number) {
    int count = 0;
    for (int i = 1; i * i <= number; ++i) {
        if (number % i == 0) {
            if (i * i == number)
                count += 1;
            else
                count += 2;
        }
    }
    return count > 2 && (count & (count - 1)) == 0;
}

int find_nth_smart_number(int n) {
    int found = 0;
    int candidate = 1;
    while (true) {
        if (is_smart_number(candidate)) {
            if (++found == n) {
                return candidate;
            }
        }
        ++candidate;
    }
}

int main() {
    int n;
    printf("Enter the n value: ");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Please enter a positive integer.\n");
        return 1;
    }
    printf("The %dth smart number is: %d\n", n, find_nth_smart_number(n));
    return 0;
}