#include <stdio.h>
#include <string.h>

int countFlips(char *binary) {
    int flips = 0;
    for(int i=0; i<strlen(binary)-1; i++) {
        if(binary[i] == binary[i+1]) {
            flips++;
        }
    }
    return flips;
}

int main() {
    char binary[] = "1010101";
    printf("Number of flips required : %d\n", countFlips(binary));
    return 0;
}