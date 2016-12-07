def romanToInt(s):
    c = [[""for i in range(4)]for j in range(10)]
    c = [["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"],  # 1
         ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"],  # 10
         ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"],  # 100
         ["", "M", "MM", "MMM"]  # 1000
         ]
    s_len = len(s)
    sumnum = 0
    for j in range(3, 0, -1):
        if s.find(c[3][j]) != -1:
            c_len = len(c[3][j])
            s.find(c[3][j])
            sumnum = 1000 * j
            # print c_len
            s = s[c_len: len(s)]
            # print s#,sumnum
            # print sumnum

    for i in range(2, -1, -1):
        for j in range(9, 0, -1):
            # print i,j
            # s.find(c[i][j])
            if s.find(c[i][j]) != -1:
                # print s.find(c[i][j])
                # print c[i][j]
                c_len = len(c[i][j])
                lon = len(s)
                s = s[c_len: lon]
                print s
                sumnum += 10**i * j
                # print sumnum
                break

    # print sumnum
    return sumnum

s = "MDCCCLXXXIV"  # 1884
a = romanToInt(s)
print a
