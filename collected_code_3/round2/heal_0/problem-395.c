#include <stdio.h>
#define NO_OF_CHARS 256

char firstNonRepeating(char* str) {
    int count[NO_OF_CHARS] = {0};
    int index = 0;

    for (; *(str+index); index++)
        count[*(str+index)]++;

    for (index = 0; *(str+index); index++)
        if (count[*(str+index)] == 1)
            return *(str+index);

    return 0;
}

int main() {
    char str[] = "helloWorld";
    char result = firstNonRepeating(str);
    if (result)
        printf("The first non-repeating character is %c", result);
    else
        printf("All characters are repeating");
    return 0;
}