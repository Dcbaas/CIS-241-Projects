#include <string.h>
#include <stdio.h>

void reverse(char charray[]);

int main(int argc, char** argv){
    char string[10];

    printf("\nEnter a string of less than 10 characters\n");
    scanf("%s", &string);

    reverse(string);
    printf("%s\n", string);

    return 0;
} 




void reverse(char charray[]){ 
    char temp[10];
    //Set a variable to the length of the string so that the function 
    //is only needed once. I suspect a for loop is used to count the
    //length.
    int length = strlen(charray);
    strcpy(temp, charray);

    for(int index = length-1; index >= 0; --index){
        charray[length - index - 1] = temp[index];
    }
    charray[length] = '\0';
}
