#include <stdio.h>
#include <string.h>

void find_substring(char* main_string, char* sub_string) {
    int main_len = strlen(main_string);
    int sub_len = strlen(sub_string);
    int i, j, found;

    for(i = 0; i <= main_len - sub_len; i++) {
        found = 1;
        for(j = 0; j < sub_len; j++) {
            if(main_string[i + j] != sub_string[j]) {
                found = 0;
                break;
            }
        }
        if(found == 1) {
            printf("Substring found at position: %d\n", i);
        }
    }
}

int main() {
    char main_string[100], sub_string[50];

    printf("Enter the main string: ");
    fgets(main_string, sizeof(main_string), stdin);

    printf("Enter the substring to be searched: ");
    fgets(sub_string, sizeof(sub_string), stdin);

    // Removing the newline character from both strings
    main_string[strlen(main_string) - 1] = '\0';
    sub_string[strlen(sub_string) - 1] = '\0';

    find_substring(main_string, sub_string);

    return 0;
}