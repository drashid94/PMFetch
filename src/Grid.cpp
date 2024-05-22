/* Has 'move' function that takes medicine and destination location
	- searches the MedicineDatabase to find out the inital location of that medicine and calls the 'move' functions from Motor module as necessary
 - Location of meds
	- gets this from Medicine Database?
 - dimensions of grid
 - pulses per unit movement in either direction
 - getters
 - setters
*/

#include "Grid.hpp"

Grid::Grid(MedicineDatabase& medicineDatabaseIn, int xdimensions, int ydimensions, int numUnitsX, int numUnitsY)
{
    if (xdimensions <= 0 || ydimensions <= 0 || numUnitsX <= 0 || numUnitsY <= 0) {
		//return out of bounds grid error
    }

    // Calculate pulses per unit for each dimension
	pulsesPerUnitX = X_PULSES_PER_CENTIMETER * xdimensions / numUnitsX;
	pulsesPerUnitY = Y_PULSES_PER_CENTIMETER * ydimensions / numUnitsY;

	medicineDatabase_ = medicineDatabaseIn->getAllMedicines();
	// populate gridContainers[][] by running through medicine database and loading medicines with non-zero x and y coordinates?
  }

int Grid::getPulsesPerUnitX() const {
	return pulsesPerUnitX;
}

int Grid::getPulsesPerUnitY() const {
	return pulsesPerUnitY;
}

int Grid::getLocationX(const std::string& barcodeUPC) const {
	// search gridContainers for barcodeUPC. If found return x position
	// or search MedicineDatabase and return x_coordinate from the medicine struct
}

int Grid::getLocationY(const std::string& barcodeUPC) const {
	// search gridContainers for barcodeUPC. If found return x position
	// or search MedicineDatabase and return x_coordinate from the medicine struct
}

bool Grid::IsSlotEmpty(int x, int y) {
	// check if gridContainers[x][y] points to a medicine
}

uint32_t Grid::addToShelf(const Medicine& medication) {
	// check if it exists in gridContainers
	// call move sequence for picking up drop off container and placing in new position
	// update gridContainer
	// update medicine database to include x and y coordinates for the medicine
}

uint32_t Grid::retrieveMedicine(const int barcodeUPC) {
	// check if it exists in gridContainer
	// call move sequence for retrieving container and placing in pick up spot
	// update gridcontainer? do we remove entirely from grid?
}