#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

char* convertSnakeToCamel(char* string){
    static char buffer[256];
    memset(buffer, 0, sizeof(buffer));
    bool upper_case_next = false;
    for(int i = 0, j = 0; string[i]; i++) {
        if (string[i] == '_') {
            upper_case_next = true;
        } else {
            if (upper_case_next == true) {
                buffer[j++] = toupper(string[i]);
                upper_case_next = false;
            } else {
                buffer[j++] = string[i];
            }
        }
    }
    return buffer;
}

void testConvertSnakeToCamel(){
    char snake_case[256] = "this_is_a_snake_case_string";
    char* camel_case = convertSnakeToCamel(snake_case);
    printf("Camel Case: %s\n", camel_case);
} 

int main() {
    testConvertSnakeToCamel();
    return 0;
}