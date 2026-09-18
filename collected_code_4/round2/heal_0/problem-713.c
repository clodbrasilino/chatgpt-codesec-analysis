#include <stdbool.h>
#include <stdio.h>

#define MAX_TUPLE_SIZE 100

bool check_tuple(int* tuple, int size) {
    if(tuple == NULL || size <= 0 || size > MAX_TUPLE_SIZE) {
        return false;
    }
    for(int i=0; i<size; i++) {
        if(tuple[i] < 0) {
            return false;
        }
    }
    return true;
}

int main() {
    int tuple[MAX_TUPLE_SIZE];
    int size;
    printf("Enter the size of the tuple: ");
    scanf("%d", &size);

    if(size <= 0 || size > MAX_TUPLE_SIZE) {
        printf("Invalid size entered\n");
        return 1;
    }

    printf("Enter the elements of the tuple: ");
    for(int i=0; i<size; i++) {
        scanf("%d", &tuple[i]);
    }

    if(check_tuple(tuple, size)) {
        printf("The tuple is valid\n");
    } else {
        printf("The tuple is invalid\n");
    }
    return 0;
}