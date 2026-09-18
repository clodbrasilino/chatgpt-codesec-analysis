#include <stdio.h>
#include <ctype.h>
#include <string.h>

int max_run_of_uppercase(const char* str) {
    int max_length = 0, temp_length = 0;
    if(str != NULL) {
        for(int i=0; str[i] != '\0'; i++) {
            if(isupper(str[i])) {
                temp_length++;
                if(temp_length > max_length) {
                    max_length = temp_length;
                }            
            } else {
                temp_length = 0;
            }
        }
    }
    return max_length;
}

int main() {
    char str[] = "Hello WOrLD";
    int max_length = max_run_of_uppercase(str);
    printf("Max run of uppercase characters is: %d\n", max_length);
    return 0;
}