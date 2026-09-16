#include <stdio.h>

int find_perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    return side * 4;
}

int main() {
    int side = 5;
    
    if (side < 0) {
        return 1;
    }

    int perimeter = find_perimeter(side);

    printf("%d\n", perimeter);
    return 0;
}