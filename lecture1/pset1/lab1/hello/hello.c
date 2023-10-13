#include <stdio.h>  //I guess these ones are like libriares
#include <cs50.h>   //so i have to use cs50.h to get some specific more commands

int main(void) // this is a function which is apparently used as a place to code inside 
{
    string name = get_string("what's your name? "); //the get_string is like a prompt and i created a string variable called name
    
    printf("hello, %s\n", name); //this displays whatever u want. here i used a "%s" as a placeholder for a string, and then concatenated the variable name just like js does
}
