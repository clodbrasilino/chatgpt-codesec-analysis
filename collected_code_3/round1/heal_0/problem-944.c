#include <stdio.h>
#include <ctype.h>

void separateNumbers(char *str) {
    int i = 0;
    while(str[i] != '\0') {
        if(isdigit(str[i])) {
            printf("Number: %c at Position: %d\n", str[i], i);
        }
        i++;
    }
}

int main() {
    char str[] = "Hello123World456";
    separateNumbers(str);
    return 0;
}