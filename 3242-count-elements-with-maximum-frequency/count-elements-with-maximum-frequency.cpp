class Solution {
public:
    int maxFrequencyElements(vector<int>& nums) {
        unordered_map<int,int>mp;
        //count
        for(int num:nums){
            mp[num]++;

        }
        //find max freq
        int maxf=0;
        for(auto it:mp){
            maxf=max(it.second,maxf);

        }
        //add max fre
        int result=0;
        for(auto it:mp){
            if(it.second==maxf){
                result += it.second;
            }
        }
       return result;
        
    }
};