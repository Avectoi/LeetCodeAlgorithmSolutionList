class Solution {
public:

    int * ten2two(int num){
        int *array = new int[33];
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
        array[32] = i - 1;
        return array;
        
    }
    
    void change(int * array){
        for(int i = 0 ; i < array[32];  i++)
            if(array[i] == 0)
                array[i] = 1;
            else if(array[i] == 1)
                array[i] = 0;
    }
    
    long long int two2ten(int * array){
        long long int tmp = 0;
        for(int i = 0 ; i < array[32];  i++)
        {
            if(array[i] == 1)
                tmp += pow(2,i);
        }
        return tmp;
    }
    
    int findComplement(int num) {
        int * arr1;
        arr1 = ten2two(num);
        change(arr1);
        long long int res;
        res = two2ten(arr1);
        delete [] arr1;
        return res;
    }
};