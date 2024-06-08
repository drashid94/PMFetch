#ifndef GRID_H
#define GRID_H

#include "MedicineDatabase.hpp"
#include "Motor.hpp"
#include "defines.hpp"
#include <vector>

class Grid {
public:
	//Grid(int xdimensions, int ydimensions, int pulsesPerUnit);
	Grid();
	Grid(Motor* motorUnitIn, MedicineDatabase* medicineDatabaseIn, int xdimensionsCm, int ydimensionsCm, int numUnitsX, int numUnitsY);
	uint32_t getPulsesPerUnitX() const;
	uint32_t getPulsesPerUnitY() const;
	uint32_t getLocation(const Medicine& medication) const;
	uint32_t shelfSetup();

	bool IsSlotEmpty(ShelfCoord c); // include some error check to ensure x and y are within bounds

	uint32_t returnToShelf(const Medicine& medication); // calls move from motor unit
	uint32_t fetchFromShelf(const Medicine& medication); // calls move from motor unit

private:

	uint32_t addNewItemToGrid(Medicine *med);
	uint32_t permanantlyRemoveFromGrid(Medicine *med);
	uint32_t updateGrid(ShelfCoord shelfCoord, bool returning);
public:
	uint32_t pulsesPerUnitX;
	uint32_t pulsesPerUnitY;	

private:
	ShelfCoord currentCoord;
	ShelfCoord pickupLocation;

	Motor* motorUnit;
	const std::vector<Medicine>* medicineDatabase; // populated by calling getAllMedicines() from medicine database?
	// Medicine gridContainers[gridMaxY][gridMaxX]; //TODO adjust size based on actual number of rows and columns in shelf
	std::vector<std::vector<Medicine>> gridContainers;
};

#endif // GRID_H

// test