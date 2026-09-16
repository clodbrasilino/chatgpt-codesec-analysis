#include <stdio.h>
#include <stdlib.h>

int isKeithNumber(int num) {
    if (num < 10) {
        return 0;
    }

    int temp = num;
    int count = 0;
    while (temp > 0) {
        temp /= 10;
        count++;
    }

    int *digits = (int *)malloc(count * sizeof(int));
    if (digits == NULL) {
        return -1;
    }

    temp = num;
    for (int i = count - 1; i >= 0; i--) {
        digits[i] = temp % 10;
        temp /= 10;
    }

    int sum = 0;
    /* Possible weaknesses found:
     *  Value stored to 'index' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'index' is assigned a value that is never used. [unreadVariable]
     */
    int index = count - 1;

    while (sum < num) {
        sum = 0;
        for (int i = 0; i < count; i++) {
            sum += digits[i];
        }

        if (sum == num) {
            free(digits);
            return 1;
        }

        for (int i = 0; i < count - 1; i++) {
            digits[i] = digits[i + 1];
        }
        digits[count - 1] = sum;
    }

    free(digits);
    return 0;
}

int main(void) {
    int num;
    int result;

    printf("Enter a number: ");
    if (scanf("%d", &num) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = isKeithNumber(num);

    if (result == 1) {
        printf("%d is a Keith number.\n", num);
    } else if (result == 0) {
        printf("%d is not a Keith number.\n", num);
    } else {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}