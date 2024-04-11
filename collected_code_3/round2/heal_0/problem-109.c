#include <stdio.h>
#include <string.h>

int countRotations(char *binStr) {
    int len = strlen(binStr);
    char temp[2*len + 1];
    int count = 0;

    strcpy(temp, binStr);
    strcat(temp, binStr);

    for (int i = 0; i < len; i++) {
        int val = 0;
        for (int j = i; j < i + len; j++) {
            val = val * 2 + temp[j] - '0';
        }
        if (val % 2 != 0) {
            count++;
        }
    }
    return count;
}

int main() {
    char binStr[] = "101";
    printf("Count of rotations with odd value = %d\n", countRotations(binStr));
    return 0;
}