#include <stdio.h>

int count_hex(int start, int end) {
    int count = 0;
    for(int i = start; i <= end; i++) {
        count++;
    }
    return count;
}

int main() {
    int start, end;
    printf("Enter start of range: ");
    scanf("%d", &start);
    printf("Enter end of range: ");
    scanf("%d", &end);
    int result = count_hex(start, end);
    printf("Count of hexadecimal numbers in given range: %d\n", result);
    return 0;
}