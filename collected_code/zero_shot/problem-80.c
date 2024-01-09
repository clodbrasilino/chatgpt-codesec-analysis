#include <stdio.h>

int findTetrahedralNumber(int n) {
    return (n * (n + 1) * (n + 2)) / 6;
}

int main() {
    int n = 5;
    int tetrahedralNumber = findTetrahedralNumber(n);
    printf("The %dth tetrahedral number is %d", n, tetrahedralNumber);
    
    return 0;
}