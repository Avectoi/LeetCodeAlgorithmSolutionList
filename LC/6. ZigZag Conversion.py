# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

 
s = "ABC"
a = convert(s, 2)
print(a)



#OMG, I find the format is wrong after WA several times. 
def convert2(s, numRows):
    tmp_n = numRows + 1 #4
    leng = len(s)
    col = len(s) / tmp_n
    row = len(s) % tmp_n
    zheng = (col+1) * tmp_n
    new_s = ""    
    tmp = 0
    sum = -tmp_n
    add = 0
    add2 = tmp_n - 1
    
    for i in range(len(s)):
        #if (i + 1) / tmp_n != 0:
        sum = sum + tmp_n
    
        if sum >= len(s):

            tmp += 1
            sum = tmp
            #print (sum,len(s))
            #print(tmp,2333)

         #+ tmp
        if tmp < tmp_n - 1:  
            new_s += s[sum] 
            #print (new_s)
        elif tmp == tmp_n - 1:
            #print (tmp_n - 1) / 2,col
            if row <= (tmp_n - 2) / 2:
                #print()
                add_to_sum = 1 + row * (col + 1) + ((tmp_n - 2) / 2 - row) * col;
                new_s = new_s[:add_to_sum + add] + s[add2] + new_s[add_to_sum + add:]
                
            elif row > (tmp_n - 2) / 2:
                add_to_sum = 1 + (tmp_n - 2) / 2 * (col + 1)
                new_s = new_s[:add_to_sum + add] + s[add2] + new_s[add_to_sum + add:]
                #print (new_s)
            #print()
            add += 2
            add2+= tmp_n
        #print(sum)

            
    return new_s
        
    """ for i in range(len(s)):   
        if (i + 1) / tmp_n == 0:
            s = s[:i] + s[i] + s[i + 1:]
    """     