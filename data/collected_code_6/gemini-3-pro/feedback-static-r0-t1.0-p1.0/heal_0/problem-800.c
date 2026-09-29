#include <stdio.h>
#include <ctype.h>

void remove_whitespaces(char *str) {
    int read_index = 0;
    int write_index = 0;

    if (str == NULL) {
        return;
    }

    while (str[read_index] != '\0') {
        if (!isspace((unsigned char)str[read_index])) {
            str[write_index] = str[read_index];
            write_index++;
        }
        read_index++;
    }
    str[write_index] = '\0';
}

int main(void) {
    char test_string[] = " C p r o g r a m \t m i ng \n!";
    
    remove_whitespaces(test_string);
    
    printf("%s\n", test_string);
    
    return 0;
}