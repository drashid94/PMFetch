#ifndef GRID_H
#define GRID_H

#include "MedicineDatabase.hpp"
#include "Motor.hpp"

class Grid {
public:
	//Grid(int xdimensions, int ydimensions, int pulsesPerUnit);
	Grid(Motor& motorUnitIn, MedicineDatabase& medicineDatabaseIn, int xdimensions, int ydimensions, int numUnitsX, int numUnitsY);
	int getPulsesPerUnitX() const;
	int getPulsesPerUnitY() const;
	int getLocationX(const std::string& barcodeUPC) const;
	int getLocationY(const std::string& barcodeUPC) const;

	bool IsSlotEmpty(int x, int y); // include some error check to ensure x and y are within bounds

	uint32_t addToShelf(const Medicine& medication); // calls move from motor unit
	uint32_t retrieveMedicine(const int barcodeUPC); // calls move from motor unit


private:
	int pulsesPerUnitX;
	int pulsesPerUnitY;
	Motor* motorUnit;
	vector<Medicine>* medicineDatabase; // populated by calling getAllMedicines() from medicine database?
	Medicine* gridContainers [5][5]; //TODO adjust size based on actual number of rows and columns in shelf
};

#endif // GRID_H

// test