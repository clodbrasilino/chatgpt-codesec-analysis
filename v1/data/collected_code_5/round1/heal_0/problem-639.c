#include <stdio.h>
#include <string.h>
#include <ctype.h>

int sumLengthOfNames(char *names[], int count) {
    int sum = 0;
    for (int i = 0; i < count; i++) {
        if(names[i] == NULL) continue;
        else if(isupper(names[i][0])) sum += strlen(names[i]);
    }
    return sum;
}

int main() {
    char *names[]={"John", "isaac", "Helen", "romi"};
    int count = sizeof(names)/sizeof(names[0]);
    int sum = sumLengthOfNames(names, count);
    printf("Sum of the length of the names: %d\n", sum);
    return 0;
}