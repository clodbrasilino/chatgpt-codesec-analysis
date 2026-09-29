#include <stdio.h>

int isTriangleValid(int a, int b, int c) {
    if (a + b <= c || a + c <= b || b + c <= a)
        return 0;
    else
        return 1;
}

int main() {
    int a, b, c;
    printf("Enter sides of a triangle\n");
    scanf("%d%d%d", &a, &b, &c);

    if (isTriangleValid(a, b, c))
        printf("Triangle is valid.\n");
    else
        printf("Triangle is not valid.\n");

    return 0;
}