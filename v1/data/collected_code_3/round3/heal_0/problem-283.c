#include <stdio.h>
#include <string.h>

int checkFrequency(char* num) {
    int freq[10] = {0};
    int i, digit;

    for(i = 0; num[i] != '\0'; i++) {
        digit = num[i] - '0';
        freq[digit]++;
        if(freq[digit] > digit) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char num[100];
    printf("Enter a number: ");
    scanf("%s", num);

    if(checkFrequency(num)) {
        printf("The frequency of each digit is less than or equal to the digit itself.\n");
    } else {
        printf("The frequency of each digit is not less than or equal to the digit itself.\n");
    }

    return 0;
}