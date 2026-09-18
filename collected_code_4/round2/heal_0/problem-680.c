#include <stdio.h>
#include <stdbool.h>

bool check_increasing(int sequence[], int size) {

    for(int i = 0; i < size - 1; ++i) {
        if(sequence[i] >= sequence[i + 1]) {
            return false;
        }
    }
    
    return true;
}

int main(void) {

    int sequence[] = {1, 2, 3, 4, 5};
    int size = sizeof(sequence) / sizeof(sequence[0]);

    bool result = check_increasing(sequence, size);
  
    if(result)
        printf("The sequence is increasing.\n");
    else
        printf("The sequence is not increasing.\n");

    return 0;
}