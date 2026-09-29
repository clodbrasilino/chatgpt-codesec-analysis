#include <stdio.h>
#include <stdbool.h>

bool checkRoots(int a, int b, int c) {
    if (a == 0) {
        return false;
    }
    
    long long lhs = 2LL * b * b;
    long long rhs = 9LL * a * c;
    
    return lhs == rhs;
}

int main(void) {
    int a, b, c;
    
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (checkRoots(a, b, c)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}