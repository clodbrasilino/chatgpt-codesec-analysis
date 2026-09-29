#include <stdio.h>
#include <string.h>

void extract_values(const char* string) {
    int i = 0;
    
    while (string[i] != '\0') {
        if (string[i] == '\"') {
            int j = i + 1;
            while (string[j] != '\"') {
                printf("%c", string[j]);
                j++;
            }
            printf("\n");
        }
        i++;
    }
}

int main() {
    const char* string = "This is a \"test\" string with \"multiple\" values.";
    
    extract_values(string);
    
    return 0;
}