#include <stdio.h>
#include <string.h>

int checkFrequency(char* str) {
    int freq[10] = {0};
    int i, len = strlen(str);

    for(i = 0; i < len; i++) {
        if(str[i] >= '0' && str[i] <= '9') {
            freq[str[i] - '0']++;
        }
    }

    for(i = 0; i < 10; i++) {
        if(freq[i] > i) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%s", str);

    if(checkFrequency(str)) {
        printf("The frequency of each digit is less than or equal to the digit itself.\n");
    } else {
        printf("The frequency of each digit is not less than or equal to the digit itself.\n");
    }

    return 0;
}