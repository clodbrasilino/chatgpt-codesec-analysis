#include <ctype.h>
#include <string.h>

void moveNumbersToString(char *string, size_t size) {
    int index = 0;
    int numIndex = 0;

    while (string[index] != '\0' && index < size) {
        if (isdigit((unsigned char)string[index])) {
            string[numIndex] = string[index];
            numIndex++;
        }
        index++;
    }

    string[numIndex] = '\0';
}

int main() {
    char str[] = "2ab3ef5gh7ij9";
    moveNumbersToString(str, sizeof str);
    
    return 0;
}