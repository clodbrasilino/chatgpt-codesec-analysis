#include <stdio.h>

typedef struct {
    int key;
    int value;
} dict;

int sum_dict_values(dict *dictionary, int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += dictionary[i].value;
    }
    return sum;
}

int main() {
    dict dictionary[] = {
        {1, 10},
        {2, 20},
        {3, 30},
        {4, 40},
        {5, 50}
    };

    int size = sizeof(dictionary) / sizeof(dictionary[0]);
    int sum = sum_dict_values(dictionary, size);
    printf("Sum of all items in the dictionary: %d\n", sum);

    return 0;
}