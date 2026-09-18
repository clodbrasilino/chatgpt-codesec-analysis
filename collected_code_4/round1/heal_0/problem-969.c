#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

char* join_tuple(char tuple1[], char tuple2[]) {
    size_t len1 = strlen(tuple1);
    for(size_t i = 0; i < len1; i++) {
        if(tuple1[i] == ',') {
            if(strncmp(tuple1, tuple2, i) != 0) {
                return NULL;
            } 
			
            char* joint_tuple = (char*)malloc(MAX_LEN * sizeof(char));
            if(joint_tuple == NULL) {
                return NULL;
            }

            strncpy(joint_tuple, tuple1, MAX_LEN-1);
            strncat(joint_tuple, tuple2+i, MAX_LEN-strlen(joint_tuple)-1);
            
			return joint_tuple;
        } 
    }

    return NULL;
}

int main() {
    char tuple1[MAX_LEN] = "abc,def,ghi";
    char tuple2[MAX_LEN] = "abc,jkl,mno";

    char* result = join_tuple(tuple1, tuple2);

    if(result == NULL) {
        printf("Tuples cannot be joined\n");
    } else {
        printf("The joined tuple is %s\n", result);
        free(result); 
        result = NULL;
    }

    return 0;
}