#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int triangle(int a, int b, int c);

int main(){
    if( triangle(2,2,4) == 2)  printf("test case 1: pass\n");
    else printf("test case 1: Fail\n");    
    if( triangle(3,2,4) == 3)  printf("test case 2: pass\n");
    else printf("test case 2: Fail\n");    
    if( triangle(3,3,3) == 0)  printf("test case 3: pass\n");
    else printf("test case 3: Fail\n");    
    if( triangle(1,2,5) == 2)  printf("test case 4: pass\n");
    else printf("test case 4: Fail\n");    
    if( triangle(1,7,5) == 4)  printf("test case 5: pass\n");
    else printf("test case 5: Fail\n");    
    if( triangle(1,2,6) == 2)  printf("test case 6: pass\n");
    else printf("test case 6: Fail\n");    
    return 0;
}