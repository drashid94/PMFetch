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
	Grid(Motor* motorUnitIn, MedicineDatabase* medicineDatabaseIn, int xdimensions, int ydimensions, int numUnitsX, int numUnitsY);
	uint32_t getPulsesPerUnitX() const;
	uint32_t getPulsesPerUnitY() const;
	uint32_t getLocationX(const std::string& barcodeUPC) const;
	uint32_t getLocationY(const std::string& barcodeUPC) const;

	bool IsSlotEmpty(int x, int y); // include some error check to ensure x and y are within bounds

	uint32_t addToShelf(const Medicine& medication); // calls move from motor unit
	uint32_t retrieveMedicine(const int barcodeUPC); // calls move from motor unit

private:

public:
	uint32_t pulsesPerUnitX;
	uint32_t pulsesPerUnitY;	

private:
	
	Motor* motorUnit;
	std::vector<Medicine>* medicineDatabase; // populated by calling getAllMedicines() from medicine database?
	// Medicine gridContainers[gridMaxY][gridMaxX]; //TODO adjust size based on actual number of rows and columns in shelf
	std::vector<std::vector<Medicine>> gridContainers;
};

#endif // GRID_H

// test