using System.Collections.Generic;

public class Solution {
    public int FindLucky(int[] arr) {
        Dictionary<int, int> freq = new Dictionary<int, int>();

        // Count frequency
        foreach (int num in arr) {
            if (freq.ContainsKey(num))
                freq[num]++;
            else
                freq[num] = 1;
        }

        int lucky = -1;

        // Find largest lucky number
        foreach (var kvp in freq) {
            if (kvp.Key == kvp.Value) {
                lucky = System.Math.Max(lucky, kvp.Key);
            }
        }

        return lucky;
    }
}
