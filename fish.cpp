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
//ADVANCE DOESN"T SEEM TO WORK!!!
////////////////////////advance(it, i); //get element i (iterator to be thrown out every run)
			myFish = *it; // or just "it" (no pointer*)?
			pond.erase(it); // *pluck*
			if ((j = isSimulationFinished())) //if finished
				reportDeath(myFish->type);
			else
				runSimulation(); //loop again, the fish is still out
			it = pond.begin();
//ADVANCE DOESN'T SEEM TO WORK!!!
////////////////////////advance(it, i);
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

int main()
{
	int fishType[] = {2, 2, 1}; //trout catfish Dan
	char *fishNames[(sizeof(fishType)/sizeof(int))];
	fishNames[0] = "Trout";
	fishNames[1] = "Catfish";
	fishNames[2] = "Dan";
	int importantFishTypes[] = {0, 2}; //trout and Dan; when one dies, the simulation is done (ending conditions)
	simData simulation((int)(sizeof(fishType)/sizeof(int)), fishType, (int)(sizeof(importantFishTypes)/sizeof(int)), importantFishTypes); //update the lines above to change the arrays
	simulation.runSimulation();
	cout << simulation.simulationCycles << endl;
	int i, j;
	for (i = 0; i < (int)(sizeof(importantFishTypes)/sizeof(int)); i++)
		cout << fishNames[importantFishTypes[i]] << " have died " << simulation.getImportantFishDeaths()[i] << " times.\n";
	for (i = 0; i < (int)(sizeof(fishType)/sizeof(int)); i++) {
		for (j = 0; j < (int)(sizeof(importantFishTypes)/sizeof(int)); j++)
			if (importantFishTypes[j] == i)
				break; //inner loop
		if (j != sizeof(importantFishTypes)/sizeof(int))
			continue; //outer loop
		//else
		cout << fishNames[i] << " were not counted, as they aren't an ending condition.\n";
	}
	return 0;
}
