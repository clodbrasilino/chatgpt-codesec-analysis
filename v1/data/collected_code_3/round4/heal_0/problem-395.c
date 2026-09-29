#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256

char firstNonRepeating(char* str) {
    int count[NO_OF_CHARS] = {0};
    int i;
    for (i = 0; *(str+i); i++)
        count[*(str+i)]++;
    for (i = 0; *(str+i); i++)
        if (count[*(str+i)] == 1)
            return *(str+i);
    return 0;
}

int main() {
    char str[] = "examplestring";
    char res = firstNonRepeating(str);
    if (res != 0)
        printf("The first non-repeating character is %c", res);
    else
        printf("All characters are repeating");
    return 0;
}