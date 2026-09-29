#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} dict;

dict *filter_dict(dict *input_dict, int length, int filter_value, int *new_length) {
    *new_length = 0;

    for (int i = 0; i < length; i++) {
        if (input_dict[i].value == filter_value) {
            (*new_length)++;
        }
    }

    dict *filtered_dict = (*new_length > 0) ? malloc(*new_length * sizeof(dict)) : NULL;

    if (filtered_dict) {
        int j = 0;
        for (int i = 0; i < length; i++) {
            if (input_dict[i].value == filter_value) {
                filtered_dict[j] = input_dict[i];
                j++;
            }
        }
    }

    return filtered_dict;
}

int main() {
    dict input_dict[] = {{"key1", 1}, {"key2", 2}, {"key3", 3}, {"key4", 2}, {"key5", 1}};
    int length = sizeof(input_dict) / sizeof(dict);
    int new_length;
    int filter_value = 2;
    dict *filtered_dict = filter_dict(input_dict, length, filter_value, &new_length);
    if (filtered_dict) {
        for (int i = 0; i < new_length; i++) {
            printf("Key: %s, Value: %d\n", filtered_dict[i].key, filtered_dict[i].value);
        }
    
        free(filtered_dict);
    }
    return 0;
}