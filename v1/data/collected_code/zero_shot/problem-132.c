#include <stdio.h>
#include <string.h>

void tupleToString(char *str, int tuple) {
    sprintf(str, "(%d, %d, %d)", tuple >> 16, (tuple >> 8) & 0xFF, tuple & 0xFF);
}

int main() {
    int tuple = 0x123456;
    char str[32];
    
    tupleToString(str, tuple);
    
    printf("%s\n", str);
    
    return 0;
}