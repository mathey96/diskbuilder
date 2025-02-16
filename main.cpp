#include <unordered_map>
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
	int elite;
	int num_of_disks;
	bool operator<(const disk& other) const {
		return name < other.name;  // Or any other criteria for elite
    }
    bool operator==(const disk& other) const {
        return name == other.name && size == other.size;
    }
};

namespace std {
    template <>
    struct hash<disk> {
        size_t operator()(const disk& d) const {
            size_t h1 = std::hash<std::string>{}(d.name);  // Hash for name
            size_t h2 = std::hash<char>{}(d.size);          // Hash for size
            return h1 ^ (h2 << 1); // Combine the two hashes using XOR
        }
    };
}


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
	elite = 0,
	nonelite
};

const std::vector<disk> vc_deck = { // vc one standard set deck
    { "Black knights"   ,11   ,'M',nonelite, 2},
    { "Banshee"         ,7    ,'S',nonelite, 3},
    { "Necromancers"    ,7    ,'S',nonelite, 3},
    { "Zombie dragon"   ,14   ,'L',elite, 1},
    { "Grave guard"     ,8    ,'S',nonelite, 3},
    { "Vargheist"       ,9    ,'M',nonelite, 2},
    { "Black coach"     ,12   ,'M',elite, 2},
    { "Skeleton"        ,4    ,'S',nonelite, 3},
    { "Dire wolves"     ,6    ,'S',nonelite, 3}
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

    // Start the recursive search
    findCombinations(disks, amount, currentCombination, result, 0);

    return result;
}


/* constraints of the regiments are following:
1. no regiments with multiple elite disks
2. There cannot be more than 3 copies of a small disk, 2 copies of a
medium disk, and 1 copy of a large disk per regiment.
3. count of large + medium disks <= count of small disks
*/

vector<vector<disk>> ValidDiskCombinations(const vector<disk>& disks, int amount){
	auto AllCombinations = diskCombinations(disks, amount); // all mathematically possible combinations of disks that amount to general's command value
	for (auto combination = AllCombinations.begin(); combination != AllCombinations.end();){
		int num_of_elite = 0, num_small = 0, num_medium = 0, num_large = 0;
		std::set<disk> unique_disks;
		std::unordered_map<disk, int> disk_count;
		for(auto& disk: *combination){ // check if unique
			if(disk.elite == elite) num_of_elite ++;
			if(disk.size == 'S') num_small++;
			if(disk.size == 'M') num_medium++;
			if(disk.size == 'L') num_large++;
            unique_disks.insert(disk);
			disk_count[disk]++;  // Increment the number of the same disk in one combination
		}

		for (const auto& entry : disk_count) { // copy restriction  check
			if( entry.first.size == 'L' && entry.second > 1
			|| ( entry.first.size == 'M' && entry.second > 2)
			|| ( entry.first.size == 'S' && entry.second > 3)){
				goto erase_thiscombo;
			}
		 }

        if (num_of_elite > 1 || (num_small < num_medium + num_large) ) {
			erase_thiscombo:
            combination = AllCombinations.erase(combination);  // Erase and get the new iterator
        } else {
            ++combination;
        }
	}
	return AllCombinations;
	}

void printCombinationsTable(vector<vector<disk>> combinations){
	cout <<  endl;
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
