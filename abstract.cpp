#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Helper function to find all combinations using backtracking
void findCombinations(vector<int>& coins, int amount, vector<int>& currentCombination, vector<vector<int>>& result, int startIndex) {
    // If amount becomes 0, we found a valid combination
    if (amount == 0) {
        result.push_back(currentCombination);
        return;
    }

    // Try all coins starting from the current index
    for (int i = startIndex; i < coins.size(); i++) {
        // If the coin is larger than the remaining amount, skip it
        if (coins[i] > amount) continue;

        // Choose the coin and continue
        currentCombination.push_back(coins[i]);
        findCombinations(coins, amount - coins[i], currentCombination, result, i);  // We can reuse the same coin

        // Backtrack, remove the coin
        currentCombination.pop_back();
    }
}

// Function to return all combinations of coins that sum to the target amount
vector<vector<int>> coinCombinations(vector<int>& coins, int amount) {
    vector<vector<int>> result;
    vector<int> currentCombination;

    // Sort coins to avoid duplicate combinations in the output
    sort(coins.begin(), coins.end());

    // Start the recursive search
    findCombinations(coins, amount, currentCombination, result, 0);

    return result;
}

int main() {
    vector<int> coins = {11,7,7,14,8,9,12,4,6}; // Denominations of the coins
    int amount = 33; // The target amount

    vector<vector<int>> combinations = coinCombinations(coins, amount);

    // Print all the combinations
    cout << "Combinations of coins to make amount " << amount << ":" << endl;
    for (const auto& combination : combinations) {
        for (int coin : combination) {
            cout << coin << " ";
        }
        cout << endl;
    }

    return 0;
}
