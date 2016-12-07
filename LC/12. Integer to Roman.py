def length(a):
    int_len = 100
    while a / (10**int_len) == 0 and int_len >= 0:
        int_len -= 1
    return int_len + 1
    """
	a should be int.
	"""


def intToRoman(num):
    c = [[""for i in range(4)]for j in range(10)]
    c = [["", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"],  # 1
         ["", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"],  # 10
         ["", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"],  # 100
         ["", "M", "MM", "MMM"]  # 1000
         ]
    s = ""
    s = s + c[3][num / 1000 % 10]
    s = s + c[2][num / 100 % 10]
    s = s + c[1][num / 10 % 10]
    s = s + c[0][num / 1 % 10]

    return s

s = 520
print intToRoman(s)