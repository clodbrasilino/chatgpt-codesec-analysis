#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int countOddRotations(char *bin) {
    int len = strlen(bin);
    char *temp = (char *)malloc(sizeof(char)*(len*2 + 1));

    if (temp == NULL){
        return -1;
    }

    int count = 0;
    temp[0] = '\0';
   
    strcat(temp, bin);
    strcat(temp, bin);

    for (int i = 0; i < len; i++) {
        int num = 0;
        for (int j = 0; j < len; j++) {
            num = num * 2 + (temp[i + j] - '0');
        }
        if (num & 1) {
            count++;
        }
    }
    free(temp);
    return count;
}

int main() {
    char bin[] = "101";
    int count = countOddRotations(bin);
   
    if (count != -1) {
        printf("Count of rotations with odd decimal value = %d\n", count);
    } else {
        printf("Memory allocation failed.\n");
    }
   
    return 0;
}