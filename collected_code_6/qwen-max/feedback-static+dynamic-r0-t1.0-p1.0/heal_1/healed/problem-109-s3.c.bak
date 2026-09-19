#include <stdio.h>
#include <string.h>

int count_odd_rotations(const char *binary_string, int length) {
    int count = 0;
    for (int i = 0; i < length; ++i) {
        int value = 0;
        for (int j = 0; j < length; ++j) {
            if (binary_string[(i + j) % length] == '1') {
                value = (value * 2 + 1) % 2;
            } else {
                value = (value * 2) % 2;
            }
        }
        if (value == 1) {
            count++;
        }
    }
    return count;
}

int main() {
    const char binary_string[] = "1101";
    int length = strlen(binary_string);
    int result = count_odd_rotations(binary_string, length);
    printf("Count of rotations with odd value: %d\n", result);
    return 0;
}