#include <stdio.h>
#include <string.h>

int match(char *input_str) {
    int state = 0;
    int i = 0;
    while(i < strlen(input_str)) {
        switch(state) {
            case 0:
                if (input_str[i] == 'a') {
                    state = 1;
                } else {
                    return 0;
                }
                break;
            case 1:
                if (input_str[i] != 'b') {
                    return 0;
                }        
                break;
        }
        i++;
    }
    if (state == 1) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    char test_str[100];
    printf("Enter a test string: \n");
    scanf("%s", test_str);
    int result = match(test_str);
    if(result) {
        printf("The string matches the condition.\n");    
    } else {
        printf("The string does not match the condition.\n");
    }
    return 0;
}