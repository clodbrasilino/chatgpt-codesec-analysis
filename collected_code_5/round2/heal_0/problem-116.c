#include <stdio.h>
#include <stdlib.h>

int tuple_to_int(char *tuple){
    char *end;
    long result;
    result = strtol(tuple, &end, 10);
    if(end == tuple || *end != '\0' || result < 0 || result > INT_MAX){
        fprintf(stderr, "Failed to convert tuple into integer.\n");
        exit(EXIT_FAILURE);
    }
    return (int)result;
}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Usage: %s <tuple>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int value = tuple_to_int(argv[1]);
    printf("%d\n", value);
    return EXIT_SUCCESS;
}