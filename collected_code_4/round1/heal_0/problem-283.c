#include <stdio.h>
#include <string.h>

#define MAX_DIGITS 10

int checkDigitFrequency(char *str) {
    int frequency[MAX_DIGITS] = {0};
    int i;
    for(i = 0; str[i] != '\0'; i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            frequency[str[i] - '0']++;
        }
    }
    for(i = 0; i < MAX_DIGITS; i++) {
        if(frequency[i] > i) {
            return 0;
        }
    }
    return 1;
}


int main() {
    char str[100];
    printf("Enter a number: ");
    scanf("%s", str);
    if(checkDigitFrequency(str)) {
        printf("Each digit's frequency is less than or equal to the digit itself\n");
    } else {
        printf("Each digit's frequency is not less than or equal to the digit itself\n");
    }
    return 0;
}