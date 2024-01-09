#include <stdio.h>
#include <string.h>

void abbreviateRoad(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len - 3; i++) {
        if (str[i] == 'r' && str[i+1] == 'o' && str[i+2] == 'a' && str[i+3] == 'd') {
            str[i+2] = 'd';
            str[i+3] = '.';
        }
    }
}

int main() {
    char str[100];
    printf("Enter a string: ");
    scanf("%[^\n]s", str);
    abbreviateRoad(str);
    printf("Abbreviated string: %s\n", str);
    
    return 0;
}
