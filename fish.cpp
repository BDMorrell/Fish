#include <iostream>
#include <list>
using namespace std;

class fish { //has nested unique id factory
private:
	static int *nextIdFactory; //id factory value
public:
	fish(int breed) {
		if (fish::nextIdFactory == 0) fish::nextIdFactory = new int(0); //make id factory value
		id = (*fish::nextIdFactory)++;
		type = breed;
	}
	int type;
	int getId() {return id;}
private:
	int id; //don't change me!
};
int * fish::nextIdFactory = 0;

class simData {
public:
	simData(int numOfType, int *numInType, int numOfImportant, int *Important) { //argc, argv for numbers
		int i, j; //count fish to make
		simulationCycles = 0;
		totalFish = 0;
		typesOfFish = numOfType;
		for (i = 0; i < numOfType; i++)
			totalFish += numInType[i];
		allFish = new fish*[totalFish];
		numImportantFishTypes = numOfImportant;
		importantFishTypes = new int[numOfImportant];
		importantFishDeaths = new int[numOfImportant];
		for (i = 0; i < numOfImportant; i++) {
			importantFishTypes[i] = Important[i];
			importantFishDeaths[i] = 0;
		}
		int count = 0; //populate pond
		for (i = 0; i < numOfType; i++)
			for (j = 0; j < numInType[i]; j++)
				allFish[count++] = new fish(i);
		repopulate();
	}
	~simData() { // We're responsible people! :D
		//delete pond; //not a pointer to a list, should distroy with object
		int i;
		for (i = 0; i < totalFish; i++)
			delete allFish[i];
		delete[] allFish;
		delete[] importantFishTypes;
		delete[] importantFishDeaths;
	}

	void runSimulation() {
		simulationCycles++;
		int i, j, size;
		fish *myFish = 0; //the one being held onto;
		list<fish*>::iterator it;
		size = pond.size(); //remove?
		for (i = 0; i < size; i++) {
			it = pond.begin(); //throw out iterator just to be safe; remove?
			advance(it, i); //get element i (iterator to be thrown out every run)
			myFish = *it; // or just "it" (no pointer*)?
			pond.erase(it); // *pluck*
			if ((j = isSimulationFinished())) { //if finished //We don't need j, do we?
				reportDeath(myFish->type);
			} else
				runSimulation(); //loop again, the fish is still out
			it = pond.begin();
			advance(it, i);
			pond.insert(it, myFish); //put the fish back
		}
	}

	void reset() { //if we want to re-run, this is pretty much useless.
		int i;
		for (i = 0; i < numImportantFishTypes; i++)
			importantFishDeaths[i] = 0;
		repopulate();
	}
	void repopulate() { //return all fish to the pond
		pond.clear(); //to remove any possible duplicates
		int i;
		for (i = 0; i < totalFish; i++)
			pond.push_front(allFish[i]);
	}
	int *getLivingFishTypes() { //total amounts of living fish //destroy return value when done
		int *types = new int[typesOfFish];
		int i; for (i = 0; i < typesOfFish; i++) types[i] = 0; //This was missing, THAT WAS A BIG MEAN BUG!!!
		list<fish*>::iterator it;
		for (it = pond.begin(); it != pond.end(); it++)
			types[(*it)->type]++;
		return types;
	}
	int getImportantFishByType(int type) {
		int i;
		for (i = 0; i < numImportantFishTypes; i++)
			if (importantFishTypes[i] == type) {
				break;
			}
		if (i == numImportantFishTypes) return -1; //nothing was found
		return i;
	}
	int reportDeath(int type, int num = 1) {
		int fishNum = getImportantFishByType(type);
		if (fishNum == -1) return -1;
		importantFishDeaths[fishNum] += num;
		return importantFishDeaths[fishNum];
	}
	int isSimulationFinished() { //if an important fish type is extinct
		int *livingBreeds = getLivingFishTypes(); //delete returned value
		int i;
		int finished = 0; //value to return
		for (i = 0; i < numImportantFishTypes && finished == 0; i++)
			if (livingBreeds[importantFishTypes[i]] == 0)
				finished = i+1; //who died +1
		delete[] livingBreeds;
		return finished;
	}
	int getTotalImportantFishDeaths() {
		int i, total = 0;
		for (i = 0; i < numImportantFishTypes ;i++)
			total += importantFishDeaths[i];
		return total;
	}
	int *getImportantFishDeaths() {return importantFishDeaths;}
	int getTypesOfFish() {return typesOfFish;}
	int getTotalFish() {return totalFish;}
	fish **allFish; // * of array, * to element in array
	list<fish*> pond; // "living" fish
	int numImportantFishTypes; //size of importantFishTypes
	int *importantFishTypes; //array of who's important
	int simulationCycles;
private:
	int typesOfFish; //for totaling the ammounts of living fish
	int totalFish; //so we can delete the fish when we are done
	// results:
	int *importantFishDeaths; //who died
};

int atoi(char* str) {
	int ret = 0;
	int i;
	for (i = 0; str[i] >= '0' && str[i] <= '9'; i++) {
		ret *= 10;
		ret += str[i] - '0';
	}
	return ret;
}

int main()
{
	/*int fishType[] = {4, 4, 1}; //trout catfish Dan
	const char *fishNames[(sizeof(fishType)/sizeof(int))];
	fishNames[0] = "Trout";
	fishNames[1] = "Catfish";
	fishNames[2] = "Dan";
	int importantFishTypes[] = {0, 2}; //trout and Dan; when one dies, the simulation is done (ending conditions)*/

/**************NOTE****************
I'm not that good at getting user
input with clean code. I appologize
to anyone who has to deal with my
input code in the future.
**********************************/

	int i, j;

	int fishType[] = {4, 4, 1}; //trout catfish Dan
	const char *fishNames[(sizeof(fishType)/sizeof(int))];
	fishNames[0] = "Trout";
	fishNames[1] = "Catfish";
	fishNames[2] = "Dan";
	int fishTypeNumber = (sizeof(fishType)/sizeof(int));
	int importantFishTypes[] = {0, 2}; //trout and Dan; when one dies, the simulation is done (ending conditions)
	int importantFishNumber = (sizeof(importantFishTypes)/sizeof(int));

	/**************NOTE****************
	This current version doesn't work:(
	cout << "There are some fish in a lake. Fish are going to be caught at random until a crucial species dies." << endl;
	cout << "You get to set up this lake.\nHow many different kinds of fish are in the lake?" << endl;
	int fishTypeNumber;
	cin >> fishTypeNumber;
	int fishType[fishTypeNumber];
	char *fishNames[fishTypeNumber];
	char str[1024];
	cout << endl << "Names of each kind of fish:" << endl;
	for (i = 0; i < fishTypeNumber; i++) {
		cout << "What is the name of fish type " << i << "?\n";
		cin >> str;
		for (j = 0; str[j] != '\0'; j++) ;
		fishNames[i] = new char[j];
		for (; j >= 0; j--) fishNames[i][j] = str[j];
		cout << "How many " << fishNames[i] << " are in the lake?\n";
		cin >> fishType[i];
	}
	int importantFishNumber;
	cout << endl << "Important Fish\nHow many of the fish above are important?" << endl;
	cin >> importantFishNumber;
	if (importantFishNumber > fishTypeNumber) {
		cout << "The important fish can't be more numerous than how many fish types there are." << endl;
		return -1;
	}
	cout << "Important Fish:\nWhich fish are important? (See table below:)" << endl;
	cout << "num |  name" << endl;
	cout << "----+---------------" << endl;
	for (i = 0; i < fishTypeNumber; i++)
		cout << cout.width(3) << i << ": " << fishNames[i] << endl; //why does width(3) seem to make space of size 4? And a trailing 0?
	int importantFishTypes[importantFishNumber];
	cout << "Input the number corrisponding to the type of fish that are ending conditions." << endl;
	for (i = 0; i < importantFishNumber; i++) {
		cout << i << "/" << importantFishNumber << ": ";
		for (j = 0; j < 1024; j++) str[j] = '\0';
		for (j = 0; j < 1024 && str[(j)?(j-1):0] != '\0'; j++)
			cin >> str[j];
		j = 0;
		for (j = 0; j < 1024; j++)
			if (str[i] == '\0') break;
			else if (str[i] < '0' && str[i] > '9') {
				cout << "Input wasn't only just numbers" << endl;
				i--;
				j = 1;
				break;
			}
		if (j) continue; // != 0 retry
		j = atoi(str);
		cout << j << endl;
		if (j >= fishTypeNumber || j < 0) {
			cout << "Invalid input (out of range)" << endl;
			i--; //so the user can try again
			continue;
		}
		importantFishTypes[i] = j;
	}
	cout << endl << "Running. This may take a while." << endl;*/

	simData simulation(fishTypeNumber, fishType, importantFishNumber, importantFishTypes); //update the lines above to change the arrays
	simulation.runSimulation();
	cout << "The main loop of the function has ran " << simulation.simulationCycles << " times." << endl;
	//int i, j;
	for (i = 0; i < importantFishNumber; i++)
		cout << fishNames[importantFishTypes[i]] << " have died " << simulation.getImportantFishDeaths()[i] << " times.\n";
	for (i = 0; i < fishTypeNumber; i++) {
		for (j = 0; j < importantFishNumber; j++)
			if (importantFishTypes[j] == i)
				break; //inner loop
		if (j != importantFishNumber)
			continue; //outer loop
		//else
		cout << fishNames[i] << " were not counted, as they aren't an ending condition.\n";
	}

	//for (i = 0; i < fishTypeNumber; i++) delete[] fishNames[i];
	return 0;
}
