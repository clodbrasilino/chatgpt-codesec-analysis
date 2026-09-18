#include <stdbool.h>
#include <stdio.h>
#include <string.h>

bool is_binary_string(const char* str) {
    size_t length = strlen(str);

    for (size_t i = 0; i < length; ++i) {
        if (str[i] != '0' && str[i] != '1') {
            return false;
        }
    }
    return true;
}

int main() {
    const char* str1 = "101010101101110";
    const char* str2 = "10205090930Abc";

    if(is_binary_string(str1)) {
        printf("str1 is a binary string.\n");
    } else {
        printf("str1 is not a binary string.\n");
    }

    if(is_binary_string(str2)) {
        printf("str2 is a binary string.\n");
    } else {
        printf("str2 is not a binary string.\n");
    }

    return 0;
}