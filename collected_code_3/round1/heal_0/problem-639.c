#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sumLength(char* names[], int size) {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        if(isupper(names[i][0])) {
            sum += strlen(names[i]);
        }
    }
    return sum;
}

int main() {
    char* names[] = {"John", "peter", "Sam", "alex", "Robert"};
    int size = sizeof(names) / sizeof(names[0]);
    int sum = sumLength(names, size);
    printf("The sum of the lengths of the names that start with an uppercase letter is %d\n", sum);
    return 0;
}