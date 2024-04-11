#include <stdio.h>
#include <string.h>

#define SIZE 5

int check_items(char *list[], char *str, int size) {
    for(int i = 0; i < size; i++) {
        if(strcmp(list[i], str) != 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    char *list[SIZE] = {"hello", "hello", "hello", "hello", "hello"};
    char *str = "hello";

    if(check_items(list, str, SIZE)) {
        printf("All items are equal to the given string.\n");
    } else {
        printf("All items are not equal to the given string.\n");
    }

    return 0;
}