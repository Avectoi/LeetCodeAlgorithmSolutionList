# class Solution(object):
def longestCommonPrefix(strs):
    len_s = len(strs)

    min_len = len(strs[0])

    for i in range(len_s):
        min_len = min(min_len, len(strs[i]))
    if len_s == 0 or min_len == 0:
        return ""
    j = 0
    flag = True
    while j < min_len:
        tmp = strs[0][j]
        for i in range(1, len_s):
            if strs[i][j] == tmp:
                continue
            else:
                flag = False
                break
        if flag == False:
            break
        j += 1
    return strs[0][0:j]


strs = ["ADB", "ADF"]
print longestCommonPrefix(strs)
