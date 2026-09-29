#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE_OF_LIST 50

int convertToInt(char* input[], int size) {
    int i, number = 0;
    for(i=0; i<size; i++) {
        if(atoi(input[i]) == 0 && strcmp(input[i], "0") != 0) {
            printf("Error: Non-integer value found, exiting now.");
            exit(EXIT_FAILURE);
        } else {
            number = number * 10 + atoi(input[i]);
        }
    }
    return number;
}

int main(int argc, char* argv[]) {
    char* list[SIZE_OF_LIST] = {"1", "2", "3", "4", "5"};
    int result = convertToInt(list, 5);
    printf("The result is: %d\n", result);
    return 0;
}