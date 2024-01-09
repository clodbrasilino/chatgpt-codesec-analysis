#include <stdio.h>

int count_flips(char *binary_string) {
    int flips = 0;
    int i = 0;
    
    while(binary_string[i] != '\0') {
        if(binary_string[i] == binary_string[i+1]) {
            flips++;
        }
        
        i++;
    }
    
    return flips;
}

int main() {
    char binary_string[] = "11010101";
    int flips = count_flips(binary_string);
    
    printf("Number of flips required: %d\n", flips);
    
    return 0;
}