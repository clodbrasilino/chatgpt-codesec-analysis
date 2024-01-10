#include <stdio.h>

int countHexNumbers(int start, int end) {
    int count = 0;
    for (int i = start; i <= end; i++) {
        if (i >= 0 && i <= 15) {
            count++;
        }
        else if (i > 15 && i <= 255) {
            int temp = i;
            while (temp != 0) {
                int rem = temp % 16;
                if (rem >= 10 && rem <= 15) {
                    count++;
                }
                temp /= 16;
            }
        }
    }
    return count;
}

int main() {
    int start, end;
    
    printf("Enter the starting number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'start' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &start);
    
    printf("Enter the ending number: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'end' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &end);
    
    int hexCount = countHexNumbers(start, end);
    
    printf("Number of hexadecimal numbers in the given range: %d\n", hexCount);
    
    return 0;
}