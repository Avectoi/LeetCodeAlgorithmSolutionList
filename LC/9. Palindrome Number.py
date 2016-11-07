class Solution(object):
    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """
        s = str(x)
        s_len = len(s)
        flag = 1
        if s_len % 2 == 0:
            i = s_len / 2
            while i >= 1:
                if s[i - 1] != s[s_len - i]:
                    flag = 0
                i -= 1
        else:
            i = s_len / 2 + 1
            while i >= 2:
                if s[i - 1 - 1] != s[s_len - i + 1]:
                    flag = 0
                i -= 1
        
        if flag == 0:
            return False
        else:
            return True
        