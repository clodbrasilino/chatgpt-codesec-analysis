#include <stdio.h>
#include <math.h>

long nextPerfectSquare(long num) {
    long root = sqrt(num);
    if(root * root == num) {
        root++;
    } else {
        while(root * root < num) {
            root++;
        }
    }
    return root * root;
}

int main() {
    long num;
    printf("Enter a number: ");
    scanf("%ld", &num);
    printf("Next perfect square is: %ld\n", nextPerfectSquare(num));
    return 0;
}