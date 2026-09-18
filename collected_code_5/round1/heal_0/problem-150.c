#include <stdio.h>
#include <stdbool.h>

bool isPresentInSequence(int num) {
    int sequence_num = 0;
    while(1) {
        if(sequence_num == num) {
            return true;
        } else if(sequence_num > num) {
            return false;
        }
        sequence_num++;
    }
}

int main() {
    int num;
    printf("Enter a number: ");
    scanf("%d", &num);
    if(isPresentInSequence(num)) {
        printf("Number is present in the sequence.\n");
    } else {
        printf("Number is not present in the sequence.\n");
    }
    return 0;
}