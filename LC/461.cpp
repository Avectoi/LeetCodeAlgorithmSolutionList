class Solution {
public:
    int * ten2two(int num){
        int *array = new int[32];
        int tmp;
        for(int i = 0 ; i < 32;  i++)
            array[i] = 0;
        int i = 0;
        while(num != 0)
        {
            tmp = num % 2;
            num = num / 2;
            array[i] = tmp;
            i++;
        }
        return array;
        
    }
    int hammingDistance(int x, int y) {
        int * arr1;
        int * arr2;
        arr1 = ten2two(x);
        arr2 = ten2two(y);
        int sum_num = 0;
        for(int i = 0 ; i < 32;  i++)
            if(arr1[i] != arr2[i])
            sum_num++;
        // cout << sum_num << endl;
        
        delete [] arr1;
        delete [] arr2;
        return sum_num;
    }
};