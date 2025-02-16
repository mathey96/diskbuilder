#include <iostream>
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
	{"mannfred",31},
	{"isabella",33},
	{"heinrich",34}
};

disk vc_disks[NUM_OF_DISKS] = {
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

int disk_values[NUM_OF_DISKS] = {11,7,7,14,8,9,12,4,6};
int ways[33] = {0};
using namespace std;

int main(int argc, char* argv[]){

	for(int i=0;i < NUM_OF_DISKS; i++)
		vector<vector<disk>> disk_combinations = 
	}
	int i= 0;
	for(int i =0;i<NUM_OF_DISKS; i++){
		int j = 0;
		vc_disks[0] +


	}

}
