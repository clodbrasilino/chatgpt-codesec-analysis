#include <stdio.h>
#include <string.h>

int checkFrequency(char* num) {
    int freq[10] = {0};
    int i, n;

    for(i = 0; num[i] != '\0'; i++) {
        n = num[i] - '0';
        freq[n]++;
    }

    for(i = 0; i < 10; i++) {
        if(freq[i] > i) {
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