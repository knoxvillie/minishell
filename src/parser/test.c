//
// Created by fvalli-v on 01-05-2023.
//
#include <stdio.h>
#include <string.h>

int main (void)
{
    char s_in [50] = "Today is a      great day for programming";
    char del [20] = " ";
    char* in_Ptr = s_in;
    char* o_Ptr;

    while  ((o_Ptr=strsep( &in_Ptr, del)) != NULL){
//        o_Ptr=strsep( &in_Ptr, del);
        printf("rest of string: %s\n", in_Ptr);
        printf("%s\n\n", o_Ptr);}
    printf("rest of string: %s\n", in_Ptr);
    return (0);
}