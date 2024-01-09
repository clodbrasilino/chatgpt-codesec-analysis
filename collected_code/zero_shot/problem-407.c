#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void swap(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

int findNextBigger(char digits[], int n) {
    int i, j;

    // Find the first digit that is smaller than the digit next to it
    for (i = n - 1; i > 0; i--) {
        if (digits[i - 1] < digits[i])
            break;
    }

    // If no such digit is found, then all digits are in descending order,
    // so there is no next bigger number possible
    if (i == 0) {
        return -1;
    }

    int smallest_index = i;
    int x = digits[i - 1];

    // Find the smallest digit on right side of (i-1)th digit that is
    // greater than digits[i-1]
    for (j = i + 1; j < n; j++) {
        if (digits[j] > x && digits[j] < digits[smallest_index])
            smallest_index = j;
    }

    // Swap the smallest digit found in above loop with (i-1)th digit
    swap(&digits[i - 1], &digits[smallest_index]);

    // Sort the digits after (i-1)th position in ascending order
    qsort(&digits[i], n - i, sizeof(digits[0]), compare);

    // Convert the array of digits to the next bigger number
    int next_bigger = atoi(digits);

    return next_bigger;
}

int compare(const void *a, const void *b) {
    return (*(char *) a - *(char *) b);
}

int main() {
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    // Convert the number to string of digits
    char digits[20];
    sprintf(digits, "%d", number);

    int n = strlen(digits);

    // Find the next bigger number by rearranging the digits
    int next_bigger = findNextBigger(digits, n);

    if (next_bigger == -1) {
        printf("No next bigger number possible.\n");
    } else {
        printf("Next bigger number: %d\n", next_bigger);
    }

    return 0;
}