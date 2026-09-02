#include <stdio.h>
#include <ctype.h>

int max_uppercase_run(const char *str) {
    if (str == NULL) {
        return 0;
    }
    
    int max_run = 0;
    int current_run = 0;
    
    for (const char *p = str; *p != '\0'; p++) {
        if (isupper((unsigned char)*p)) {
            current_run++;
            if (current_run > max_run) {
                max_run = current_run;
            }
        } else {
            current_run = 0;
        }
    }
    
    return max_run;
}

int main(void) {
    const char *test_strings[] = {
        "Hello WORLD Example",
        "ABCdefGHIJK",
        "no uppercase here",
        "UPPERlowerUPPER",
        "",
        "ALLUPPERCASE",
        "aBcDeFgH"
    };
    
    for (int i = 0; i < (int)(sizeof(test_strings) / sizeof(test_strings[0])); i++) {
        printf("String: \"%s\" -> Max uppercase run: %d\n", 
               test_strings[i], 
               max_uppercase_run(test_strings[i]));
    }
    
    return 0;
}