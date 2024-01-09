void moveNumbersToString(char *string) {
    int index = 0;
    int numIndex = 0;
    char numbers[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
  
    while (string[index] != '\0') {
        if (isdigit(string[index])) {
            string[numIndex] = string[index];
            numIndex++;
        }
        index++;
    }
  
    string[numIndex] = '\0';
}