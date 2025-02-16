#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <set>

#define NUM_OF_DISKS 9

struct disk{
	std::string name;
	int command_value;
	char size;
	int uniqueness;
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

enum{
	uniquedisk = 0,
	nonunique
};

const std::vector<disk> vc_deck = { // vc one standard set deck
    { "black knights"   ,11   ,'M',nonunique, 2},
    { "banshee"         ,7    ,'S',nonunique, 3},
    { "necromancers"    ,7    ,'S',nonunique, 3},
    { "zombie dragon"   ,14   ,'L',uniquedisk, 1},
    { "grave guard"     ,8    ,'S',nonunique, 3},
    { "vargheist"       ,9    ,'M',nonunique, 2},
    { "black coach"     ,12   ,'M',uniquedisk, 2},
    { "skeleton"        ,4    ,'S',nonunique, 3},
    { "dire wolves"     ,6    ,'S',nonunique, 3}
};

using namespace std;

void findCombinations(const vector<disk>& disks, int amount, vector<disk>& currentCombination, vector<vector<disk>>& result, int startIndex) {
    // If amount becomes 0, we found a valid combination
    if (amount == 0) {
        result.push_back(currentCombination);
        return;
    }

    // Try all disks starting from the current index
    for (int i = startIndex; i < disks.size(); i++) {
        // If the disk is larger than the remaining amount, skip it
        if (disks[i].command_value > amount) continue;

        // Choose the disk and continue
        currentCombination.push_back(disks[i]);
        findCombinations(disks, amount - disks[i].command_value, currentCombination, result, i);  // We can reuse the same disk

        // Backtrack, remove the disk
        currentCombination.pop_back();
    }
}

vector<vector<disk>> diskCombinations(const vector<disk>& disks, int amount) {
    vector<vector<disk>> result;
    vector<disk> currentCombination;

    // Sort disks to avoid duplicate combinations in the output
    // sort(disks.begin(), disks.end());

    // Start the recursive search
    findCombinations(disks, amount, currentCombination, result, 0);

    return result;
}

vector<vector<disk>> ValidDiskCombinations(const vector<disk>& disks, int amount){
	auto AllCombinations = diskCombinations(disks, amount); // all mathematically possible combinations of disks that amount to general's command value
	for (auto combination = AllCombinations.begin(); combination != AllCombinations.end();){
		int num_of_uniq = 0, num_small = 0, num_medium = 0, num_large = 0;
		for(auto& disk: *combination){ // check if unique
			if(disk.uniqueness == uniquedisk) num_of_uniq ++;
			if(disk.size == 'S') num_small++;
			if(disk.size == 'M') num_medium++;
			if(disk.size == 'L') num_large++;
		}
		// IMPLEMENT:
		// we run twice over the same combination to check if there are more than max number of disks available to player
		// if there are, discard that combination

		// delete combinations with multiple unique disks - 1st constraint of the game
        if (num_of_uniq > 1 || (num_small < num_medium + num_large)) {
            combination = AllCombinations.erase(combination);  // Erase and get the new iterator
        } else {
            ++combination;
        }
		// cout<< "kraj kombinacije\n\n";
	}
	return AllCombinations;

}
void printCombinationsTable(vector<vector<disk>> combinations){
     for (const auto& combination : combinations) {
         for (disk disk : combination) {
             std::cout << "|" << setw(15) << disk.name << "[" << setw(2) << disk.command_value <<"] " <<  left;
         }
         cout << "|" << endl;
     }
}

int main(int argc, char* argv[]){
    vector<vector<disk>> combinations = diskCombinations(vc_deck, 33);
	cout << "this is the size of all combinations:" << combinations.size() << endl;
	combinations = ValidDiskCombinations(vc_deck,33);
	printCombinationsTable(combinations);
	cout << "this is the size of all valid combinations:" << combinations.size() << endl;
}
