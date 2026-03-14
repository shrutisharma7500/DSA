class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
    unordered_map<int,int>freq;
    vector<int>result;
    //freq cunt
    for(int num:nums){
    freq[num]++;
    }
    for(auto it:freq){
        if(it.second>1){
            result.push_back(it.first);
        }
    }
     return result;   
    }
};