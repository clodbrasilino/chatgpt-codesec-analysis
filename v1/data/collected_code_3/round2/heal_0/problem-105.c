#include <stdio.h>
#include <stdbool.h>

int countTrueBooleans(bool* list, int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(list[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    bool list[] = {true, false, true, true, false, true};
    int size = sizeof(list)/sizeof(list[0]);
    int count = countTrueBooleans(list, size);
    printf("Number of true booleans: %d\n", count);
    return 0;
}