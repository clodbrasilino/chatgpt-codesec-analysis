#include <stdio.h>
#include <string.h>

int minSwaps(char *binary1, char *binary2, int length) {
    int count = 0;
    int i = 0;
    int j = 0;

    while (i < length) {
        if (binary1[i] != binary2[j]) {
            j = i;

            while (binary1[j] != binary2[i]) {
                j++;
            }

            while (j > i) {
                char temp = binary1[j];
                binary1[j] = binary1[j - 1];
                binary1[j - 1] = temp;
                j--;
                count++;
            }
        }

        i++;
    }

    return count;
}

int main() {
    char binary1[] = "11001";
    char binary2[] = "01110";
    int length = strlen(binary1);

    printf("Minimum number of swaps required = %d\n", minSwaps(binary1, binary2, length));

    return 0;
}