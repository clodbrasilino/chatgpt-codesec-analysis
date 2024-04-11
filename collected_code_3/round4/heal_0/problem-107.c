#include <stdio.h>

int count_hexadecimal_numbers(int start, int end) {
    int count = 0;
    for(int i = start; i <= end; i++) {
        count++;
    }
    return count;
}

int main() {
    int start, end;
    printf("Enter the start of the range: ");
    scanf("%d", &start);
    printf("Enter the end of the range: ");
    scanf("%d", &end);
    int count = count_hexadecimal_numbers(start, end);
    printf("The count of hexadecimal numbers in the given range is: %d\n", count);
    return 0;
}