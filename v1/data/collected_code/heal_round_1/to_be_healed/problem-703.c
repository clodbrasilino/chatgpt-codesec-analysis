#include <stdio.h>

#define SIZE 10

int dictionary[SIZE] = {25, 35, 15, 60, 45, 10, 30, 50, 20, 40};

int isKeyPresent(int key) {
    for (int i = 0; i < SIZE; i++) {
        if (dictionary[i] == key) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int key;
    printf("Enter a key: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'key' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &key);

    if (isKeyPresent(key)) {
        printf("Key is present in the dictionary.\n");
    } else {
        printf("Key is not present in the dictionary.\n");
    }

    return 0;
}