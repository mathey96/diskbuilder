#include <iostream>
#include <vector>
#include <iomanip>
#define NUM_OF_DISKS 9

struct disk{
	std::string name;
	int command_value;
	char type;
	int num_of_disks;
};

struct general {
	std::string name;
	int command_value;
};

general generals[] = {
	{"mannfred", 31},
	{"isabella", 33},
	{"heinrich", 34}
};

std::vector<disk> vc_deck = { // vc one standard set deck
    { "black knights"   ,11   ,'M'  , 2},
    { "banshee"         ,7    ,'S'  , 3},
    { "necromancers"    ,7    ,'S'  , 3},
    { "zombie dragon"   ,14   ,'L'  , 1},
    { "grave guard"     ,8    ,'S'  , 3},
    { "vargheist"       ,9    ,'M'  , 2},
    { "black coach"     ,12   ,'M'  , 2},
    { "skeleton"        ,4    ,'S'  , 3},
    { "dire wolves"     ,6    ,'S'  , 3}
};

using namespace std;

void findCombinations(vector<disk>& coins, int amount, vector<disk>& currentCombination, vector<vector<disk>>& result, int startIndex) {
    // If amount becomes 0, we found a valid combination
    if (amount == 0) {
        result.push_back(currentCombination);
        return;
    }

    // Try all coins starting from the current index
    for (int i = startIndex; i < coins.size(); i++) {
        // If the coin is larger than the remaining amount, skip it
        if (coins[i].command_value > amount) continue;

        // Choose the coin and continue
        currentCombination.push_back(coins[i]);
        findCombinations(coins, amount - coins[i].command_value, currentCombination, result, i);  // We can reuse the same coin

        // Backtrack, remove the coin
        currentCombination.pop_back();
    }
}

vector<vector<disk>> coinCombinations(vector<disk>& coins, int amount) {
    vector<vector<disk>> result;
    vector<disk> currentCombination;

    // Sort coins to avoid duplicate combinations in the output
    // sort(coins.begin(), coins.end());

    // Start the recursive search
    findCombinations(coins, amount, currentCombination, result, 0);

    return result;
}

int main(int argc, char* argv[]){

    vector<vector<disk>> combinations = coinCombinations(vc_deck, 33);
    for (const auto& combination : combinations) {
        for (disk coin : combination) {
            std::cout << "|" << setw(15) << coin.name << "[" << setw(2) << coin.command_value <<"] " <<  left;
        }
        cout << "|" << endl;
    }
}
