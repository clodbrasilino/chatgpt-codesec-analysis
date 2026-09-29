#include <stdio.h>
#include <stdbool.h>

bool isPresentInSequence(int num) {
    int i = 1;
    while (i <= num) {
        if (i == num) {
            return true;
        }
        i = i * 2;
    }
    return false;
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if (isPresentInSequence(num)) {
        printf("Number is present in the sequence.\n");
    } else {
        printf("Number is not present in the sequence.\n");
    }
    return 0;
}