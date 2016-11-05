# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
def longestPalindrome(s):
    """
    :type s: str
    :rtype: str
    s <= 1000
    """
    length = len(s)
    tmp = 0
    s_new = ""
    max_len = 0;
    for i in range(length):
        
        tmp = 0
        #print(i)
        while i - tmp >= 0 and i + tmp + 1 < length and s[i - tmp] == s[i + tmp + 1]:
            tmp += 1
        if tmp >= max_len: 
            max_len = tmp;
            s_new = s[i - tmp + 1: i + tmp + 1]
            #print(s_new, i, tmp)
            
        tmp = 1
        while i - tmp >= 0 and i + tmp < length and s[i - tmp] == s[i + tmp]:
            tmp += 1
        if tmp > max_len: 
            max_len = tmp;
            s_new = s[i - tmp + 1 : i + tmp]
            #print(s_new, i, tmp)
    
    return s_new
            
s = "abb"
a = longestPalindrome(s)
print(a)