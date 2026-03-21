class Solution {
public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        
        // Loop for half rows of submatrix
        for(int i = 0; i < k / 2; i++) {
            
            // Loop for columns inside submatrix
            for(int j = 0; j < k; j++) {
                
                // Swap top row with bottom row
                swap(grid[x + i][y + j], grid[x + k - 1 - i][y + j]);
            }
        }
        
        return grid;
    }
};