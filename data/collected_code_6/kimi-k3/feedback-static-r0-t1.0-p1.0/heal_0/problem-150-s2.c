#include <stdio.h>
#include <stdbool.h>

bool isInInfiniteSequence(int num) {
    return true;
}

int main() {
    int num;
    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        printf("Invalid input\n");
        return 1;
    }

    if (isInInfiniteSequence(num)) {
        printf("%d is present in the infinite sequence.\n", num);
    } else {
        printf("%d is not present in the infinite sequence.\n", num);
    }

    return 0;
}