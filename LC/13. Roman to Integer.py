def romanToInt(s):
    s_len = len(s)
    sum = 0
    for i in range(s_len - 1, -1, -1):#1,5,10,50,100,500,1000
        if s[i] == 'I' and sum < 5:
            sum += 1
        elif s[i] == 'I' and sum >= 5:
            sum -= 1
        elif s[i] == 'V':
            sum += 5
        elif s[i] == 'X' and sum < 50:
            sum += 10
        elif s[i] == 'X' and sum >= 50:
            sum -= 10
        elif s[i] == 'L':
            sum += 50
        elif s[i] == 'C' and sum < 500:
            sum += 100
        elif s[i] == 'C' and sum >= 500:
            sum -= 100
        elif s[i] == 'D':
            sum += 500  
        elif s[i] == 'M':
        	sum += 1000  
    return sum        

s = "MMMXL"  # 1884
a = romanToInt(s)
print a
