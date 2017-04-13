class Solution {
public:
    string reverseWords(string s) {
    	int i = 0;
    	int len;
    
    	len = s.length();
    	int k = 0;
    	string ss = "";
    	int ss_num = 0;
    	while(i < len){
    		if (s[i] != ' ')
    		{
    			k++;
    		}
    		else if(s[i] == ' ')
    		{
    			for (int j = 0; j < k; ++j)
    			{
    				ss+= s[i-j -1];
    				ss_num++;
    			}
    			ss+= ' ';
    			ss_num++;
    			// cout << k << endl;
    			k = 0;
    		}
    		// cout << s[i];
    		i++;
    	}
    
    	for (int j = 0; j < k; ++j)
    	{
    		ss+= s[i-j -1];
    		ss_num++;
    	}
    	cout << endl;
    	return ss;
    }
};