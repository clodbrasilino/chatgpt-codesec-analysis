#include <stdio.h>
#include <stdlib.h>

int calculateJumps(int distance, int jump_length) {
    int jumps = 0;
    if(jump_length == 0){
        printf("Jump length cannot be zero\n");
        exit(EXIT_FAILURE);
    }
    if(distance < 0 || jump_length < 0){
        printf("Distance or Jump length cannot be negative\n");
        exit(EXIT_FAILURE);
    }
    jumps = distance / jump_length;
    if(distance % jump_length != 0) jumps++;
    
    return jumps;
}

int main() {
    int distance, jump_length;
    printf("Enter the distance and jump length respectively: \n");
    scanf("%d %d", &distance, &jump_length);
    printf("The minimum number of jumps required is: %d\n", calculateJumps(distance, jump_length));
    return 0;
}