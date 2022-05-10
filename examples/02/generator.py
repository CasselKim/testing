import sys
import os
import subprocess
import re
from random import randint

# read args
if len(sys.argv) != 3 or '.c' not in sys.argv[1] or '.txt' not in sys.argv[2] : 
    print("[Invaild Input] Please follow the form : python3 generator.py <unitfunc.c> <testcase.txt>")

# read test_cases
with open(sys.argv[2],"r") as f :
    data = f.read().split('\n')

# split with prototype and samples
prototype = data[0]
prototype_flag=False
samples = data[1:]

# split with function name and parameters
i,j = prototype.find('('),prototype.find(')')
params = prototype[i+1:j]
if i==-1 : 
    func_name = prototype.split(' ')[-1]
    prototype_flag = False
else : 
    func_name = prototype[:i].split(' ')[-1]
    prototype_flag = True

# define test case templates
def test_case(func_name,case_num,params,expected) :
    return  '''\
    if( {}({}) == {})  printf("test case {}: pass\\n");
    else printf("test case {}: Fail\\n");\
    '''.format(func_name,','.join(params),expected,case_num,case_num)

# add cases
cases = []
for s in samples : 
    sample = [x for x in s.split(' ') if x]
    if sample : 
        cases.append(test_case(func_name,sample[0],sample[1:-1],sample[-1]))

# ready to implement cases
d = dict()
if prototype_flag : # if first line of test cases is prototype form
    if prototype.replace(' ','')[-1]!=';' : 
        prototype+=';'
    d['prototype']=prototype
else :  # if first line of test cases is name of function form
    with open(sys.argv[1],"r") as f : 
        unit_func = f.read()

    # find prototype from unit function
    ani = re.search(r"\n*.*{}\s*\(.*\)\s*\{{".format(func_name), unit_func).group()[:-1]
    d['prototype']=ani+';'

d['test_cases']='\n'.join(cases)

# make codes
c_codes = """#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

{prototype}

int main(){{
{test_cases}
    return 0;
}}""".format(**d)


# generate codes with name test_driver.c
with open("test_driver.c","w") as f : 
    f.write(c_codes)

# make command
commands = '''\
gcc -o a.out {} test_driver.c
./a.out\
'''.format(sys.argv[1])

# generate codes with name of run_test.sh
with open("run_test.sh","w") as f : 
    f.write(commands)

# // stub function part //
# for all of unexpected(undeclared) functions,
while True : 
    try : 
        # check if it is executable
        subprocess.check_output("gcc -o a.out {} test_driver.c".format(sys.argv[1]).split(" "), stderr=subprocess.STDOUT, encoding='utf-8')
        
        # if there is no error, break
        break

    except subprocess.CalledProcessError as e:
        if "undefined reference to" in e.output : 

            #find unexpected function
            res = re.search(r"undefined reference to `[a-zA-Z0-9]*\'",e.output)
            
            if res : 
                # extract the name of unexpected function
                stub_name = re.search(r"`[a-zA-Z0-9]*\'",res.group()).group()[1:-1]
                with open(sys.argv[1],"r") as f : 
                    unit_func = f.read()

                # find uses of unexpected function to notice form of the function
                prototype = re.search(r"{}\s*\(.*\)".format(stub_name), unit_func).group()
    
                # calculate parameter's number and temporarily set as integer
                params_num = len([x for x in re.search(r"\(.*\)", prototype).group()[1:-1].split(',') if x])
                params = str(["int "+chr(i+97) for i in range(params_num)])[1:-1].replace('\'','')

                # generate stub code
                stub_code = "\n int {} ({}) {{return {};}}".format(stub_name,params,randint(1,5))
                
                # append with test_driver.c
                with open("test_driver.c","a") as f : 
                    f.writelines(stub_code)

        else : 
            print("unexpected error...")
            exit()