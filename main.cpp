#include <iostream>
#include <vector>
#include <iomanip>
#include <string.h>
#include <algorithm>
#include <unordered_map>
#include <set>
#ifdef EMSCRIPTENBUILD
#include <emscripten/emscripten.h>
#endif

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

struct disk {
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

enum{
	elite = 0,
	nonelite
};

const std::vector<disk> empire_deck = { // vc one standard set deck
    {"Steam Tank"               ,13    ,'L'   ,elite     ,1},
    {"Hellblaster Volley Gun"   ,10    ,'L'   ,elite     ,1},
    {"Hochland Pistoliers"      ,9     ,'M'   ,nonelite  ,1},
    {"Knights Panther"          ,10    ,'M'   ,nonelite  ,1},
    {"Warrior Priests"          ,9     ,'M'   ,nonelite  ,2},
    {"Bright Wizard"            ,7     ,'S'   ,nonelite  ,1},
    {"Huntsmen"                 ,8     ,'S'   ,nonelite  ,1},
    {"Marienburg Swordsmen"     ,5     ,'S'   ,nonelite  ,3},
    {"Reikland Crossbowmen"     ,7     ,'S'   ,nonelite  ,2},
    {"Talabecland Halberdiers"  ,5     ,'S'   ,nonelite  ,3},
    {"Talabheim Greatswords"    ,8     ,'S'   ,nonelite  ,1}
};

const std::vector<disk> elves_deck = { // vc one standard set deck
    {"Bolt Thrower"				,10 ,'L'	,elite		,1},
    {"Sun Dragon"				,15 ,'L'	,elite		,1},
    {"Ellyrian Reavers"			,9  ,'M'	,nonelite	,1},
    {"Silver Helms"				,12 ,'M'	,nonelite	,2},
    {"Sky Cutter"				,11 ,'M'	,elite		,1},
    {"High Mage"				,7  ,'S'	,nonelite	,1},
    {"Lothern Sea Guard"		,5  ,'S'	,nonelite	,3},
    {"Maiden Guard"				,9  ,'S'	,nonelite	,1},
    {"Militia Archers"			,6  ,'S'	,nonelite	,2},
    {"Militia Spearmen"			,6  ,'S'	,nonelite	,2},
    {"Swordmasters of Hoeth"	,9  ,'S'	,nonelite	,2}
};
const std::vector<disk> chaos_deck = { // vc one standard set deck
	{"Bloodthirster"		,15	    ,'L'	,elite		,1},
	{"Hellcannon"			,12	    ,'L'	,elite		,1},
	{"Bloodcrushers"		,10	    ,'M'	,nonelite	,1},
	{"Hellstriders"			,8		,'M'	,nonelite	,1},
	{"Screamers"			,7		,'M'	,nonelite	,2},
	{"Deamonettes"			,6		,'S'	,nonelite	,3},
	{"Flamers"				,8		,'S'	,nonelite	,3},
	{"Kurgan Marauders"		,5		,'S'	,nonelite	,3},
	{"Plaguebearers"		,8		,'S'	,nonelite	,1},
	{"Sorcerer of Tzeentch"	,7		,'S'	,nonelite	,1}
};


const std::vector<disk> orc_deck = { // vc one standard set deck
	{"Rock Lobber"		   ,9  ,'L' ,elite	  ,1},
	{"Boar Boys"		   ,11 ,'M' ,nonelite ,1},
	{"Doom Diver Catapult" ,5  ,'M' ,nonelite ,2},
	{"River Troll"		   ,12 ,'M' ,elite	  ,1},
	{"Wolf Riders"		   ,8  ,'M' ,nonelite ,2},
	{"Arrer Boyz"		   ,6  ,'S' ,nonelite ,2},
	{"Big Boss"			   ,8  ,'S' ,nonelite ,1},
	{"Black Orcs"		   ,8  ,'S' ,nonelite ,1},
	{"Goblin Doom Diver"   ,4  ,'S' ,nonelite ,3},
	{"Night Goblins"	   ,4  ,'S' ,nonelite ,3},
	{"Orc Boyz"			   ,6  ,'S' ,nonelite ,3},
	{"Stone Fangz Shaman"  ,7  ,'S' ,nonelite ,7}
};

const std::vector<disk> vc_deck = { // vc one standard set deck
    { "Black knights"   ,11   ,'M', nonelite, 2},
    { "Banshee"         ,7    ,'S', nonelite, 3},
    { "Necromancers"    ,7    ,'S', nonelite, 3},
    { "Zombie dragon"   ,14   ,'L', elite,    1},
    { "Grave guard"     ,8    ,'S', nonelite, 3},
    { "Vargheist"       ,9    ,'M', nonelite, 2},
    { "Black coach"     ,12   ,'M', elite,    2},
    { "Skeleton"        ,4    ,'S', nonelite, 3},
    { "Dire wolves"     ,6    ,'S', nonelite, 3}
};

const std::vector<disk> dwarves_deck = { // vc one standard set deck
	{"Flame Cannon"				,9		,'L'	,nonelite	,1}	,
	{"Runic Cannon"				,12	    ,'L'	,elite		,1}	,
	{"Ancestor Statue"			,7		,'M'	,nonelite	,2}	,
	{"Gyrocopter"				,12	    ,'M'	,elite		,2}	,
	{"Karak Azul Warriors"		,6		,'S'	,nonelite	,3}	,
	{"Karak Hirn Miners"		,7		,'S'	,nonelite	,3}	,
	{"Karaz-a-Karak Hammerers"	,8		,'S'	,nonelite	,3}	,
	{"Karaz-a-Karak Thunderers"	,8		,'S'	,nonelite	,3}	,
	{"Master Engineer"			,8		,'S'	,nonelite	,3}	,
	{"Venerable Runesmith"		,6		,'S'	,nonelite	,3}
};

const std::vector<disk> lizardmen_deck = {
    {"Salamander", 9, 'M', nonelite, 2},
    {"Skink Skirmishers", 8, 'S', nonelite, 3}
};

const std::vector<disk> wood_deck = {
    {"Athel Loren Dryads", 7, 'S', nonelite, 3},
    {"Wardancers", 9, 'S', nonelite, 3}
};

const std::vector<disk> darkelves_deck = {
    {"Black Ark Corsairs", 6, 'S', nonelite, 3},
    {"Karond Kar Harpies", 7, 'S', nonelite, 3}
};

const std::vector<disk> skaven_deck = {
    {"Ratling Gun", 9, 'M', nonelite, 2},
    {"Gutter Runners", 7, 'S', nonelite, 3}
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
		std::unordered_map<disk, int> disk_count;
		for(auto& disk: *combination){ // check if unique
			if(disk.elite == elite) num_of_elite ++;
			if(disk.size == 'S') num_small++;
			if(disk.size == 'M') num_medium++;
			if(disk.size == 'L') num_large++;
			disk_count[disk]++;  // Increment the number of the same disk in one combination
		}

		for (const auto& disk : disk_count) { // copy restriction  check
			if( disk.first.size == 'L' && disk.second > 1
			|| ( disk.first.size == 'M' && disk.second > 2)
			|| ( disk.first.size == 'S' && disk.second > 3)){
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
            std::cout << "|" << std::setw(21) << std::left << disk.name
                      << "[" << std::setw(2) << std::left << disk.command_value << "] ";
         }
         cout << "|" << endl;
     }
}

void PrettyPrintCombinationsTable(vector<vector<disk>> combinations){
	cout <<  endl;
	std::cout<<"| Max \n|disks|"<<endl;
    for (const auto& combination : combinations) {
		std::unordered_map<disk, int> disk_count;
        for (disk disk : combination) { // fill up the map
			disk_count[disk]++;
        }
		std::cout<< "|  " << combination.size() << " | ";
		for (const auto& disk : disk_count) { // copy restriction  check
            std::cout <<  disk.second << "x " << std::setw(25) << std::left << disk.first.name << " | ";
		}
		cout<<endl;
		disk_count = {};
	}
 }


#ifdef EMSCRIPTENBUILD
EXTERN EMSCRIPTEN_KEEPALIVE
#endif
void help(){
	cout<<"Run like this: ./diskbuild <army_name> <regiment_size>"<<endl;
	cout<<"Possible army names are:"<<endl
#ifndef EMSCRIPTENBUILD
		<<"    - empire"<<endl
		<<"    - elves"<<endl
		<<"    - orcs"<<endl
		<<"    - chaos"<<endl
		<<"    - vc (vampire counts)"<<endl
		<<"    - dwarves"<<endl;
#endif
#ifdef EMSCRIPTENBUILD
		<<"    1 - empire"<<endl
		<<"    2 - elves"<<endl
		<<"    3 - orcs"<<endl
		<<"    4 - chaos"<<endl
		<<"    5 - vc (vampire counts)"<<endl
		<<"    6 - dwarves"<<endl;
#endif
}

int main(int argc, char* argv[]){

	if(argv[1] == NULL || argv[2] == NULL){
		cout << "no arguments provided";
		return -1;
	}
	if((strcmp(argv[1],"help") == 0) || (strcmp(argv[1],"--help") == 0) ){
		help();
		return -1;
	}
	char* deck_type = argv[1];

	const std::vector<disk>* chosen_deck;
    if      (strcmp(deck_type,"empire") == 0)  chosen_deck = &empire_deck;
    else if (strcmp(deck_type, "elves") == 0)  chosen_deck = &elves_deck;
    else if (strcmp(deck_type, "orcs")  == 0)  chosen_deck = &orc_deck;
    else if (strcmp(deck_type, "chaos") == 0)  chosen_deck = &chaos_deck;
    else if (strcmp(deck_type, "vc")    == 0)  chosen_deck = &vc_deck;
    else if (strcmp(deck_type, "dwarves") == 0)chosen_deck = &dwarves_deck;
	else{
		cout<<"invalid race"<<endl;
		return -1;
	}

	// if(argv[1] == "empire") chosen_deck		= empire_deck;
	// if(argv[1] == "elves")  chosen_deck		= elves_deck;
	// if(argv[1] == "orcs")   chosen_deck		= orc_deck;
	// if(argv[1] == "chaos")  chosen_deck		= chaos_deck;
	// if(argv[1] == "vc")     chosen_deck		= vc_deck;
	// if(argv[1] == "dwarves")chosen_deck	    = dwarves_deck;

	int deck_size = atoi(argv[2]);

    vector<vector<disk>> combinations;
	cout << "this is the size of all combinations:" << combinations.size() << endl;
	combinations = ValidDiskCombinations(*chosen_deck,deck_size);
	// printCombinationsTable(combinations);
	PrettyPrintCombinationsTable(combinations);

	cout << "\nmax number of combinations is: " << combinations.size() << endl;
}


#ifdef EMSCRIPTENBUILD
EXTERN EMSCRIPTEN_KEEPALIVE
#endif
void PrintToBrowser(int deck_size, int race) {

	const std::vector<disk>* chosen_deck;
    if      (race == 0)  help();
    else if (race == 1)  chosen_deck = &empire_deck;
    else if (race == 2)  chosen_deck = &elves_deck;
    else if (race == 3)  chosen_deck = &orc_deck;
    else if (race == 4)  chosen_deck = &chaos_deck;
    else if (race == 5)  chosen_deck = &vc_deck;
    else if (race == 6)  chosen_deck = &dwarves_deck;

    vector<vector<disk>> combinations;
	cout << "this is the size of all combinations:" << combinations.size() << endl;
	combinations = ValidDiskCombinations(*chosen_deck,deck_size);
	// printCombinationsTable(combinations);
	PrettyPrintCombinationsTable(combinations);
}

