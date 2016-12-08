def threeSum(nums):
    n = len(nums)
    table = [[0 for i in range(n)] for j in range(n)]
    res = []

    for i in range(n - 2):
        for j in range(i + 1, n - 1):
            for k in range(j + 1, n):
                if nums[i] + nums[j] + nums[k] == 0:
                    num1 = min(nums[i], nums[j], nums[k])
                    num3 = max(nums[i], nums[j], nums[k])
                    num2 = 0 - num1 - num3
                    if [num1, num2, num3] not in res:
                        res.append([num1, num2, num3])
                        break

    return res

S = [-1, 0, 1, 2, -1, -4]
print threeSum(S)
