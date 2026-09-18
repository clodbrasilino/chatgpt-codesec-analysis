#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* abbreviate_road(char *str){
    if (!str) return NULL;

    int road_count = 0;
    char *temp = str;
    while((temp = strstr(temp, "road")) != NULL) {
        road_count++;
        temp += 4;
    }

    if (road_count == 0) return str;

    size_t new_length = strlen(str) + 1 + 2 * road_count;
    char *new_str = (char *)malloc(new_length * sizeof(char));
    if (!new_str) return NULL;

    char *old = str, *new = new_str;
    while(*old){
        if(strstr(old, "road") == old){
            memcpy(new, "rd.", 3);
            new += 3;
            old += 4;
        }
        else{
            *new++ = *old++;
        }
    }
    *new = '\0';

    free(str);

    return new_str;
}

int main(){
    char *str = (char *)malloc(100 * sizeof(char));
    if (!str) return 1;

    printf("Enter a string: \n");
    gets(str);

    char* new_str = abbreviate_road(str);

    if(new_str){
        printf("Abbreviated string: %s\n", new_str);
        free(new_str);
    }else{
        printf("Failed to allocate memory for new string.\n");
        free(str);
        return 1;
    }

    return 0;
}