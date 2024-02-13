#include<stdio.h>

int main(){

char *a = "India";
char b[] = "India";

a = a+1;//line 5
b = b+1;//line 6
} 
// ======================================================================
/* 
Line 6 will show an error: 

Line 5: a = a + 1; is valid because a is a pointer to a character string. Adding 1 to a makes it point to the second character of the string, which is allowed.

Line 6: b = b + 1; is invalid because b is an array name, not a pointer variable. Array names cannot be modified to point to a different memory location. They are fixed addresses. Attempting to change the address of b results in the error.
*/