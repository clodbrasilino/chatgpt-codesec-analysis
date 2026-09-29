#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int findMaxSegments(int n, int a, int b, int c) {
    if(n==0)
        return 0;
    if(n<a && n<b && n<c)
        return -1;
    int res = -1;

    res = max(findMaxSegments(n-a, a, b, c), findMaxSegments(n-b, a, b, c));
    res = max(res, findMaxSegments(n-c, a, b, c));
    
    if(res==-1)
        return -1;

    return res+1;
}

void test() {
    int n = 23, a = 1, b = 2, c = 3;
    int result = findMaxSegments(n, a, b, c);
    if(result == -1)
        printf("Not possible to form segments.\n");
    else
        printf("Maximum segments that can be formed from %d is %d\n", n, result);
}

int main() {
    test();
    return 0;
}