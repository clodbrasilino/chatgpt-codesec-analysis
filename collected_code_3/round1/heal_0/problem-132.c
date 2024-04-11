#include <stdio.h>
#include <stdlib.h>

char* tupleToString(int a, int b) {
    char* str = (char*)malloc(50 * sizeof(char));
    sprintf(str, "(%d, %d)", a, b);
    return str;
}

int main() {
    int a = 5, b = 10;
    char* str = tupleToString(a, b);
    printf("%s\n", str);
    free(str);
    return 0;
}