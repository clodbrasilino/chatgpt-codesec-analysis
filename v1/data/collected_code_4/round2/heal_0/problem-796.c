#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int value;
} KeyValuePair;

int dictionarySum(KeyValuePair* dict, int size) {
    int sum = 0;
    if (dict == NULL || size < 1) {
        printf("Error: Invalid dictionary or size.\n");
        return -1;
    }

    for (int i = 0; i < size; i++) {
        sum += dict[i].value;
    }

    return sum;
}

int main() {
    KeyValuePair dict[] = { {1, 10}, {2, 20}, {3, 30}, {4, 40} };

    int len = sizeof(dict) / sizeof(dict[0]);
    int result = dictionarySum(dict, len);

    if (result != -1) {
        printf("The sum of the dictionary items is: %d\n", result);
    }

    return 0;
}