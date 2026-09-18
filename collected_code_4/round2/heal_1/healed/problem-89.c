#include <stdio.h>

int find_closest_smaller(int n) {
    if (n <= 0) {
        return 0;
    } else {
        return n - 1;
    }
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    
    int closest_smaller = find_closest_smaller(n);
    
    printf("The closest smaller number than %d is %d\n", n, closest_smaller);
    
    return 0;
}