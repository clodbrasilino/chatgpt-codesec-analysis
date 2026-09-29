#include <stdio.h>
#include <ctype.h>

void toggleCase(char* str) {
    if(str == NULL) {
        return;
    }

    for(int i = 0; str[i] != '\0'; i++) {
        if(isupper(str[i])) {
            str[i] = tolower(str[i]);
        }
        else if(islower(str[i])) {
            str[i] = toupper(str[i]);
        }
    }
}

int main() {
    char str[] = "Toggle This Case";
    toggleCase(str);
    printf("%s\n", str);

    return 0;
}