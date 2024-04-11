#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *key;
    int value;
} dict;

dict *filter_dict(dict *input_dict, int length, int filter_value, int *new_length) {
    dict *filtered_dict = malloc(length * sizeof(dict));
    int j = 0;
    for (int i = 0; i < length; i++) {
        if (input_dict[i].value == filter_value) {
            filtered_dict[j] = input_dict[i];
            j++;
        }
    }
    *new_length = j;
    return filtered_dict;
}

int main() {
    int length = 5;
    dict input_dict[5] = {
        {"one", 1},
        {"two", 2},
        {"three", 3},
        {"four", 4},
        {"five", 5}
    };
    int new_length;
    dict *filtered_dict = filter_dict(input_dict, length, 2, &new_length);
    for (int i = 0; i < new_length; i++) {
        printf("%s: %d\n", filtered_dict[i].key, filtered_dict[i].value);
    }
    free(filtered_dict);
    return 0;
}