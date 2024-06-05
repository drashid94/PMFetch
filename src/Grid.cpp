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

#define RIGHT 1
#define UP 1
#define LEFT 0
#define DOWN 0

Grid::Grid() 
{ }

Grid::Grid(Motor* motorUnitIn, MedicineDatabase* medicineDatabaseIn, int xdimensions, int ydimensions, int numUnitsX, int numUnitsY)
{
    if (xdimensions <= 0 || ydimensions <= 0 || numUnitsX <= 0 || numUnitsY <= 0) {
		//return out of bounds grid error
    }
    currentCoord = {0, 0};
    // Calculate pulses per unit for each dimension
	pulsesPerUnitX = X_PULSES_PER_CENTIMETER * xdimensions / numUnitsX;
	pulsesPerUnitY = Y_PULSES_PER_CENTIMETER * ydimensions / numUnitsY;

	motorUnit = motorUnitIn;
	medicineDatabase = medicineDatabaseIn->getAllMedicines();
	// populate gridContainers[][] by running through medicine database and loading medicines with non-zero x and y coordinates?
  }

uint32_t Grid::getPulsesPerUnitX() const {
	return pulsesPerUnitX;
}

uint32_t Grid::getPulsesPerUnitY() const {
	return pulsesPerUnitY;
}

uint32_t Grid::getLocation(const Medicine& medication) const {
	// search gridContainers for barcodeUPC. If found return x position
	// or search MedicineDatabase and return x_coordinate from the medicine struct
	(void) medication;
	return SUCCESS;
}

bool Grid::IsSlotEmpty(shelfCoord c) {
	// check if gridContainers[x][y] points to a medicine
	(void)c;
	return true;
}

uint32_t Grid::addToShelf(const Medicine& medication) {
	// check if it exists in gridContainers
	// call move sequence for picking up drop off container and placing in new position
	// update gridContainer
	// update medicine database to include x and y coordinates for the medicine
	
	uint8_t direction = 0;
	uint8_t numUnits;
	uint32_t numPulses;
	//check valid coord

	//pickup from pickup location
	//Move on X
	int xMove = currentCoord.x - pickupLocation.x;
	if(xMove > 0){ direction = LEFT; }
	if(xMove < 0){ direction = RIGHT; }

	numUnits = abs(xMove);
	numPulses = pulsesPerUnitX * numUnits;
	motorUnit->move(X_MOTOR_PIN, X_MOTOR_DIR_PIN, direction, numPulses, 2000);

	//Move on Y
	int yMove = currentCoord.y - pickupLocation.y;
	if(yMove > 0){ direction = UP; }
	if(yMove < 0){ direction = DOWN; }
	
	numUnits = abs(yMove);
	numPulses = pulsesPerUnitY * numUnits;
	motorUnit->move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, direction, numPulses, 500);

	//Extend Z

	//Lift slightly

	//Retract Z

	//Move to medicine location
	xMove = currentCoord.x - medication.coord.x;
	if(xMove > 0){ direction = LEFT; }
	if(xMove < 0){ direction = RIGHT; }
	//TODO



	return SUCCESS;
}

uint32_t Grid::fetchFromShelf(const Medicine& medication) {
	// check if it exists in gridContainer
	// calculate pulses and directions
	// call move sequence for retrieving container and placing in pick up spot
	// update gridcontainer? do we remove entirely from grid?
	(void) medication;
	return SUCCESS;
}

/*//         if(sel == 'x')
//         {
//             motorPin = X_MOTOR_PIN;
//             motorDirPin = X_MOTOR_DIR_PIN;
//         }
//         else if (sel == 'y')
//         {
//             motorPin = Y_MOTOR_PIN;
//             motorDirPin = Y_MOTOR_DIR_PIN;
//         }
//         else if(sel == 'z')
//         {
//             motorPin = Z_MOTOR_PIN;
//         }
//         else if(sel == 'l')
//         {
//             motorPin = Y_MOTOR_PIN;
//             motorDirPin = Y_MOTOR_DIR_PIN;
//             lift = 1;
//         }
//         else if(sel == 'r')
//         {
//             //Extend Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//             // Lift on Y
//             move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, 1, 1);
//             // Retract Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//             // Move Y Full Step
//             move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, dir, 0);
//             // Move along X 
//             move(h, X_MOTOR_PIN, X_MOTOR_DIR_PIN, !dir, 0);
//             move(h, X_MOTOR_PIN, X_MOTOR_DIR_PIN, !dir, 0);
//             // Extend Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//             // Put down box
//             move(h, Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 1);
//             // Retract Z
//             move(h, Z_MOTOR_PIN, Y_MOTOR_DIR_PIN, 0, 0);
//         }
//         else if(sel == 'u')
//         {

//         }
//         if(sel != 'r' && sel != 'u')
//         {
//             // printf("motorPin: %d\nmotorDirPin: %d\n", motorPin, motorDirPin);
//             move(h, motorPin, motorDirPin, dir, lift);
//         }*/