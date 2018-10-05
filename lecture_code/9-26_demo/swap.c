#include <stdio.h>
//This is an example of a pointer fail. to swap the references of s and t you need to swap the orignal referenes 
//You could use a double pointer (my preference) but you could use string functions with this program to copy contents inside 
//and swap those around.
void swap(char* p, char* q);

int main(int argc, char** argv){
    char s[5] = "abc";
    char t[5] = "xyz";

    printf("%s\t%s\n", s, t);
    swap(s, t);
    printf("%s\t%s\n", s, t);
    
}

void swap(char* p, char* q){
    char* temp; 
    temp = p;
    p = q; 
    q = temp;
}
