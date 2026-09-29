#include <stdio.h>

#define SIZE 5

typedef struct {
    int key;
    int value;
} dict;

int sumDictionaryValues(dict dictionary[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += dictionary[i].value;
    }
    return sum;
}

int main() {
    dict dictionary[SIZE] = {
        {1, 10},
        {2, 20},
        {3, 30},
        {4, 40},
        {5, 50}
    };

    int sum = sumDictionaryValues(dictionary, SIZE);
    printf("Sum of all values in the dictionary: %d\n", sum);

    return 0;
}