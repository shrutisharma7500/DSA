class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int,int>mp;
        //count freq
        for(int num:nums){
            mp[num]++;

        }
        //taking freq outside the func by refrence
        sort(nums.begin(),nums.end(),[&](int a,int b){
        if(mp[a] == mp[b])
            return a>b;
            return mp[a] < mp[b];
        });

return nums;

    }
};