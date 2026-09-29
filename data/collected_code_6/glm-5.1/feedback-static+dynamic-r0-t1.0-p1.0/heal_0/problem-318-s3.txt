#include <stdio.h>

int findMaxVolume(int s) {
    if (s <= 0) {
        return 0;
    }
    int side = s / 3;
    if (s % 3 == 0) {
        return side * side * side;
    }
    if (s % 3 == 1) {
        return side * side * (side + 1);
    }
    return side * (side + 1) * (side + 1);
}

int main(void) {
    int s1 = 6;
    int s2 = 7;
    int s3 = 8;
    int s4 = 0;
    int s5 = -5;

    printf("%d\n", findMaxVolume(s1));
    printf("%d\n", findMaxVolume(s2));
    printf("%d\n", findMaxVolume(s3));
    printf("%d\n", findMaxVolume(s4));
    printf("%d\n", findMaxVolume(s5));

    return 0;
}