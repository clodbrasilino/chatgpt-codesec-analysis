#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

void removeChars(char *str1, const char *str2) {
    size_t str2_len = strnlen(str2, BUFFER_SIZE - 1);
    size_t str1_len = strnlen(str1, BUFFER_SIZE - 1);
    size_t count = 0;

    for (size_t i = 0; i < str1_len; i++) {
        int flag = 0;

        for (size_t j = 0; j < str2_len; j++) {
            if (str1[i] == str2[j]) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            str1[count++] = str1[i];
        }
    }
    if(count < BUFFER_SIZE)
        str1[count] = '\0';
    else
        str1[BUFFER_SIZE - 1] = '\0';
}

int main() {
    char str1[BUFFER_SIZE], str2[BUFFER_SIZE];
    
    printf("Enter the first string: ");
    if(fgets(str1, BUFFER_SIZE, stdin))
        str1[strcspn(str1, "\n")] = 0;

    printf("Enter the second string: ");
    if(fgets(str2, BUFFER_SIZE, stdin))
        str2[strcspn(str2, "\n")] = 0;
    
    removeChars(str1, str2);
    printf("Modified string: %s\n", str1);
    
    return 0;
}