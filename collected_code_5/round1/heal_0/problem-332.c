#include <stdio.h>
#include <string.h>

#define SIZE 256

void characterFrequency(char *str) {
    int freq[SIZE] = {0};
    int i = 0;

    while (str[i] != '\0') {
        freq[(int)str[i]]++;
        i++;
    }

    for (i = 0; i < SIZE; i++) {
        if (freq[i] != 0){
            printf("%c: %d\n", (char)i, freq[i]);
        }
    }
}

int main() {
    char str[100];

    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin); 

    str[strcspn(str, "\n")] = 0;

    characterFrequency(str);

    return 0;
}