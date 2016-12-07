# 3 1 5 7

# class Solution(object):
#     def maxArea(self, array):


def maxArea(array):
    water = 0
    i, j = 0, len(array) - 1
    while i < j:
        print i, j
        high = min(array[i], array[j])
        water = max(water, (j - i) * high)
        while array[i] <= high and i < j:
            i += 1
        while array[j] <= high and i < j:
            j -= 1

    return water


array1 = [2, 3, 4, 5, 18, 17, 6]  # 17
# array2 = [3, 1, 2, 3]  # 9
# array3 = [2, 1]  # 1
# array4 = [1, 1]  # 1

water1 = maxArea(array1)
# water2 = maxArea(array2)
# water3 = maxArea(array3)
# water4 = maxArea(array4)
print water1  # , water2, water3, water4
