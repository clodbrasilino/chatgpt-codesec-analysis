#include <stdio.h>
#include <string.h>

void abbreviate_road(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t i = 0;
    size_t j = 0;
    
    while (str[i] != '\0') {
        if (strncmp(&str[i], "road", 4) == 0) {
            str[j++] = 'r';
            str[j++] = 'd';
            str[j++] = '.';
            i += 4;
        } else {
            str[j++] = str[i++];
        }
    }
    
    str[j] = '\0';
}

int main(void) {
    char str1[] = "I am walking down the road";
    char str2[] = "roadroad";
    char str3[] = "broad road";
    char str4[] = "r";
    
    abbreviate_road(str1);
    abbreviate_road(str2);
    abbreviate_road(str3);
    abbreviate_road(str4);
    abbreviate_road(NULL);
    
    printf("%s\n", str1);
    printf("%s\n", str2);
    printf("%s\n", str3);
    printf("%s\n", str4);
    
    return 0;
}