#include <stdio.h>
#include <stdbool.h>

void filterDictionary(int dictionary[], int size, int value) {
    for(int i = 0; i < size; i++) {
        if(dictionary[i] == value) {
            printf("%d\n", dictionary[i]);
        }
    }
}