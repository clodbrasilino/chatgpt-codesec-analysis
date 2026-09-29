#include <stdio.h>
#include <stdbool.h>

bool isOneRootTwiceTheOther(int a, int b, int c) {
    if (a == 0) {
        return false;
    }
    
    long long expected_c = 2LL * (long long)b * (long long)b;
    long long actual_c = 9LL * (long long)a * (long long)c;
    
    return expected_c == actual_c;
}

int main(void) {
    int a = 0;
    int b = 0;
    int c = 0;
    
    if (scanf("%d %d %d", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    
    if (isOneRootTwiceTheOther(a, b, c)) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
    
    return 0;
}