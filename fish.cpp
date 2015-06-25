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
	simData(int numOfType, int *numInType) { //argc, argv for numbers
		int i, j; //count fish to make
		totalFish = 0;
		for (i = 0; i < numOfType; i++)
			totalFish += numInType[i];
		allFish = new fish*[totalFish];
		int count = 0; //populate pond
		for (i = 0; i < numOfType; i++)
			for (j = 0; j < numInType[i]; j++)
				allFish[count++] = new fish(i);
	}
	~simData() {
		//delete pond; //not a pointer to a list, should distroy with object
		int i;
		for (i = 0; i < totalFish; i++)
			delete allFish[i];
		delete[] allFish;
	}
	void repopulate() { //return all fish to the pond
		pond.clear(); //to remove any possible duplicates
		int i;
		for (i = 0; i < totalFish; i++)
			pond.push_front(allFish[i]);
	}
	int getTotalFish() {return totalFish;}
	fish **allFish; // * of array, * to element in array
	list<fish*> pond; // "living" fish
private:
	int totalFish; //so we can delete the fish when we are done
};

/*
TODO:
Run the simulation (peudo code below):
funciton test():
	while (havn't reun through all the fish)
		take next fish
		if (!done) //Dan or all trout died
			test()
		else
			report results
*/
int main()
{
	int fishType[] {5, 9, 1}; //trout catfish Dan
	simData simulation((sizeof(fishType)/sizeof(int)), fishType); //update the line above to change the array
	
	
	return 0;
}

