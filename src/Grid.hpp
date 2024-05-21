#ifndef GRID_H
#define GRID_H

#include "MedicineDatabase.hpp"
#include "Motor.hpp"

class Grid {
public:
	Grid(int xdimensions, int ydimensions, int pulsesPerUnit);
	//ErrorCode moveMedicine(const std::string& barcodeUPC, const std::string& destination);
	int getPulsesPerUnitX() const;
	int getPulsesPerUnitY() const;
	int getLocationX(const std::string& barcodeUPC) const;
	int getLocationY(const std::string& barcodeUPC) const;

	bool IsSlotEmpty(int x, int y); // include some error check to ensure x and y are within bounds

	ErrorCode addToShelf(const Medicine& medication); // calls move from motor unit
	ErrorCode retrieveMedicine(const int barcodeUPC) = 0; // calls move from motor unit


private:
	int pulsesPerUnitX;
	int pulsesPerUnitY;
	vector<Medicine> medicineDatabase_; // populated by calling getAllMedicines() from medicine database?
	Medicine* gridContainers [5][5]; //adjust size based on actual number of rows and columns in shelf
};

#endif // GRID_H