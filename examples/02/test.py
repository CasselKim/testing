with open("triangle_test_cases.txt","r") as f :
    data = f.read().split('\n')
print(data)
prototype = data[0]
samples = data[1:]

i,j = prototype.find('('),prototype.find(')')
print(prototype[i+1:j])


def test_case(func_name,expected,*params) :
    return  '''\
        if( {}({}) == {})  printf("test case 1: pass\n");
        else printf("test case 1 : Fail\n");\
    '''.format(func_name,str((params)),expected)

d = dict()
d['prototype']=prototype

c_codes = """#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

{prototype}

int main(){{
    printf("Hello World!");
    return 0;
}}""".format(**d)

print(c_codes)

#with open("can.c","w") as f : 
#    f.write(c_codes)

