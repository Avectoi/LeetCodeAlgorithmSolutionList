class Solution(object):
    def reverse(self,x):
        if x > 2147483648 or x < -2147483648:
            return 0
        flag = 0
        if x < 0 :
            x = -x
            flag = 1
        
        s = str(x)
        news = ""
        for i in range(len(s)):
            news += s[len(s) - i - 1]
        
        newx = int(news)
        #print(newx)
        
        if flag == 1:
            newx = -newx
        if newx > 2147483648 or newx < -2147483648:
                  #2147483641
            #print 2333
            return 0
    
        return newx