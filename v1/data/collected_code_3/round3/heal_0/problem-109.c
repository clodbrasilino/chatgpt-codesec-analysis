#include <stdio.h>
#include <string.h>

int countRotations(char* binStr) {
    int len = strlen(binStr);
    char rotatedStr[len+1];
    int count = 0;

    for (int i = 0; i < len; i++) {
        int j = 0;
        while (j < len) {
            rotatedStr[j] = binStr[(i + j) % len];
            j++;
        }
        rotatedStr[j] = '\0';

        int decimalValue = 0;
        for (int k = 0; k < len; k++) {
            if (rotatedStr[k] == '1') {
                decimalValue += 1 << (len - k - 1);
            }
        }

        if (decimalValue % 2 != 0) {
            count++;
        }
    }

    return count;
}

int main() {
    char binStr[] = "1011";
    printf("Count of rotations with odd value: %d\n", countRotations(binStr));
    return 0;
}