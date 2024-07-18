#ifndef GRID_H
#define GRID_H

#include "MedicineDatabase.hpp"
#include "Motor.hpp"
#include "defines.hpp"
#include <pthread.h>
#include <vector>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fstream>

struct GridUnit
{
	Medicine med;
	bool occupied;
};

uint32_t getInputBarcode(std::string * barcode, int timeout);

class Grid {
public:
	//Grid(int xdimensions, int ydimensions, int pulsesPerUnit);
	Grid();
	Grid(Motor * motorUnitIn, MedicineDatabase * medicineDatabaseIn, int xdimensionsCm, int ydimensionsCm, int numUnitsX, int numUnitsY);
	uint32_t getPulsesPerUnitX() const;
	uint32_t getPulsesPerUnitY() const;
	uint32_t getLocation(const Medicine& medication) const;
	uint32_t shelfSetup();
	uint32_t shelfSetupByBarcode();
	uint32_t deleteFromShelf(string barcode);
	uint32_t getInputBarcode(std::string * barcode, int timeoutInSeconds, bool liftAndPlace, bool isFetch);
	void printGrid();

	bool IsSlotEmpty(ShelfCoord c); // include some error check to ensure x and y are within bounds
	uint32_t isMedValid(string barcode);


	//Movement
	uint32_t extendZ();
	uint32_t retractZ();
	uint32_t containerLiftOrPlace(bool lift);
	uint32_t moveXY(ShelfCoord coordCurr, ShelfCoord coordDest, bool pollingOn);
	uint32_t returnToShelfByBarcode (string barcode,  bool force); // search grid by name and call returntoshelf
	uint32_t fetchFromShelfByBarcode (string barcode); // search grid by name and call fetchFromShelf
	uint32_t fetchFromShelfByName (string medicationName); // search grid by name and call fetchfromshelf
	uint32_t returnToShelf(const Medicine& medication); // calls move from motor unit
	uint32_t fetchFromShelf(const Medicine& medication); // calls move from motor unit
	uint32_t returnToShelf();
	uint32_t forceReturn(); // return during recovery mode or if item was manually fetched


private:

	uint32_t addNewItemToGrid(GridUnit * gridUnit); // grid update
	uint32_t addNewItemToGrid(string barcode); // grid update
	uint32_t permanantlyRemoveFromGrid(Medicine * med); // grid update
	uint32_t updateGrid(ShelfCoord shelfCoord, bool returning); // grid update
	uint32_t getMedFromBarcode(string barcode, Medicine *med);
	uint32_t getEmptyGridUnit(GridUnit * gridUnit);
	//void *getBarcode(string & barcode);
	//void *timeout();

public:
	uint32_t pulsesPerUnitX;
	uint32_t pulsesPerUnitY;
	uint32_t pulsesPerLiftY;
	uint32_t pulsesPerExtendZ;
	ShelfCoord currentCoord;
	ShelfCoord pickupLocation;
	ShelfCoord returnLocations[NUM_RETURN_LOCATIONS];

	Motor* motorUnit;
	const std::vector<Medicine>* medicineDatabase; // populated by calling getAllMedicines() from medicine database?
	// Medicine gridContainers[gridMaxY][gridMaxX]; //TODO adjust size based on actual number of rows and columns in shelf
	std::vector<std::vector<GridUnit>> gridContainers; // grid update
	std::string gridfile = "grid.txt";
	void serializeGrid();
};

#endif // GRID_H

// test