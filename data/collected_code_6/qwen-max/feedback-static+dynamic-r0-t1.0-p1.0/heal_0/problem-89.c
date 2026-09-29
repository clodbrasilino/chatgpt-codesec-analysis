#include <stdio.h>
#include <limits.h>

int find_closest_smaller(int n) {
    if (n == INT_MIN) {
        return n;
    }
    return n - 1;
}

int main() {
    int number = 10;
    int result = find_closest_smaller(number);
    printf("The closest smaller number than %d is %d\n", number, result);
    return 0;
}