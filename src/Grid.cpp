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
#include <string.h>
#include <iostream>

#define RIGHT 1
#define UP 1
#define LEFT 0
#define DOWN 0

Grid::Grid() 
{ }

Grid::Grid(Motor* motorUnitIn, MedicineDatabase* medicineDatabaseIn, int xdimensionsCm, int ydimensionsCm, int numUnitsX, int numUnitsY)
{
    if (xdimensionsCm <= 0 || ydimensionsCm <= 0 || numUnitsX <= 0 || numUnitsY <= 0) {
		//return out of bounds grid error
    }
    currentCoord = {0, 0};
    pickupLocation = {1, 1};
    // Calculate pulses per unit for each dimension
	pulsesPerUnitX = X_PULSES_PER_CENTIMETER * xdimensionsCm / numUnitsX;
	pulsesPerUnitY = Y_PULSES_PER_CENTIMETER * ydimensionsCm / numUnitsY;
	pulsesPerLiftY = Y_PULSES_PER_CENTIMETER * LIFT_AMOUNT_CM;

	gridContainers.resize(numUnitsY);
	for(vector<GridUnit> v : gridContainers)
	{
		v.resize(numUnitsX);
	}

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

bool Grid::IsSlotEmpty(ShelfCoord c) {
	// check if gridContainers[x][y] points to a medicine
	(void)c;
	return true;
}



uint32_t Grid::printGrid()
{
	for(vector<GridUnit> gv : gridContainers)
	{
		for(GridUnit gu : gv)
		{
			printf("|\t");			
			if(!gu.occupied)
			{
				printf("Space not occupied\t");
				continue;		
			}
			printf("Occupied\t");
			MedicineDatabase::medPrint(gu.med);

			printf("|\t");
		}
	}
	MedicineDatabase::medPrint();
}

/*
 * Function:  updateGrid 
 * --------------------
 * update grid data structure after fetching or retrieving a med
 *
 * Description:
 * 	call this when a med is retrieved or being returned. 
 * Parameters:
 *   returning - true if item is being returned
 * Returns:
 *   Status
 */
uint32_t Grid::updateGrid(ShelfCoord shelfCoord, bool returning)
{
	//check coord params valid

	gridContainers[shelfCoord.y][shelfCoord.x].med->onShelf = returning;
	return SUCCESS;
}

/*
 * Function:  addNewItemToGrid 
 * --------------------
 * Add new item to a shelf/grid unit
 *
 * Description:
 * 	Only call this when a new item is being added to an empty spot in the grid
 * 	If medicine exists on shelf delete first before adding a new med there.
 * Parameters:
 *   med - the medication to be added to the grid.
 * Returns:
 *   Status
 */
uint32_t Grid::addNewItemToGrid(GridUnit * gridUnit)
{
	//TODO Ensure no med is at these coords already
	uint32_t x = gridUnit->med->coord.x;
	uint32_t y = gridUnit->med->coord.y;
	printf("Performing memcpy\n");
	memcpy((void*)&gridContainers[y][x], (void*)gridUnit, sizeof(GridUnit));	
	return SUCCESS;
}

void Grid::isMedValid(Medicine * med, bool &valid)
{
	//TODO checks
	//Check bcode doesnt already exist on shelf and validity of values	
	(void)med;
	valid = true;
}

//take in bunch of inputs to create Medicine objects and set their location on shelf
//Do this during setup when things are already on shelf
uint32_t Grid::shelfSetup() {
	bool valid = false;
	//What already exist on the shelf?
	string name;
	string bcode;
	uint8_t x = 0;
	uint8_t y = 0;
	while(bcode != "100" && x != 100 && y != 100)
	{
		cin >> name;
		cin >> bcode;
		cin >> x;
		cin >> y;
			
		Medicine med{name, bcode, {x,y}, true /* onShelf */};
		isMedValid(&med, valid);
		GridUnit gridUnit{&med, true};

		if(valid) 
		{
			addNewItemToGrid(&gridUnit);
			printf("Item Added to Grid\n");
		}
		else
		{
			printf("Medicine is invalid\n");
		}

	}
	return SUCCESS;
}

uint32_t Grid::extendZ()
{
	//Will implement once Z axis design finalized
	printf("Extending Z\n");
	return SUCCESS;
}

uint32_t Grid::retractZ()
{
	//Will implement once Z axis design finalized
	printf("Retracting Z\n");
	return SUCCESS;
}

uint32_t Grid::containerLiftOrPlace(bool lift)
{
	uint8_t direction = 0;
	uint32_t numPulses = 0;

	printf("Lifting on Y\n");
	numPulses = pulsesPerLiftY;
	direction = DOWN;
	if(lift) direction = UP;
	motorUnit->move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, direction, numPulses, yMotorSpeed);
	return SUCCESS;

}

//Takes current location and destination and moves there
uint32_t Grid::moveXY(ShelfCoord coordCurr, ShelfCoord coordDest)
{
	uint8_t direction = 0;
	uint8_t numUnits = 0;
	uint32_t numPulses = 0;

	//Move to destination X COORD
	int xMove = coordCurr.x - coordDest.x;
	if(xMove > 0){ direction = LEFT; }
	if(xMove < 0){ direction = RIGHT; }

	numUnits = abs(xMove);
	numPulses = pulsesPerUnitX * numUnits;
	motorUnit->move(X_MOTOR_PIN, X_MOTOR_DIR_PIN, direction, numPulses, xMotorSpeed);

	//Move to destination Y COORD
	int yMove = coordCurr.y - coordDest.y;
	if(yMove > 0){ direction = UP; }
	if(yMove < 0){ direction = DOWN; }
	
	numUnits = abs(yMove);
	numPulses = pulsesPerUnitY * numUnits;
	motorUnit->move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, direction, numPulses, yMotorSpeed);
	
	currentCoord = coordDest;
	return SUCCESS;

}

uint32_t Grid::returnToShelf(const Medicine& medication) {
	// check if it exists in gridContainers
	// call move sequence for picking up drop off container and placing in new position
	// update gridContainer
	// update medicine database to include x and y coordinates for the medicine
	
	uint32_t returnValue = SUCCESS;

	//check valid coord

	/* --------------------- pickup from pickup location ------------------- */
	//Move to pickup location
	returnValue = moveXY(currentCoord, pickupLocation);

	//Extend Z
	returnValue = extendZ();

	//Lift slightly
	returnValue = containerLiftOrPlace(true);

	//Retract Z
	returnValue = retractZ();

	/* --------------------- move to medicine's location ------------------- */
	returnValue = moveXY(currentCoord, medication.coord);

	//Extend Z
	returnValue = extendZ();

	// Lower container
	returnValue = containerLiftOrPlace(false);

	// retract Z
	returnValue = retractZ();

	//Inform gridContainers that this medicine has been returned
	updateGrid(medication.coord, true);

	return returnValue;
}

uint32_t Grid::fetchFromShelf(const Medicine& medication) {
	// check if it exists in gridContainer
	// calculate pulses and directions

	/* --------------------- pickup at medicine's location ------------------- */
	uint32_t returnValue = SUCCESS;

	returnValue = moveXY(currentCoord, medication.coord);

	//Extend Z
	returnValue = extendZ();

	// Lower container
	returnValue = containerLiftOrPlace(true);

	// retract Z
	returnValue = retractZ();

	/* --------------------- dropoff at pickup location ------------------- */

	//Move to pickup location
	returnValue = moveXY(currentCoord, pickupLocation);

	//Extend Z
	returnValue = extendZ();

	//Lift slightly
	returnValue = containerLiftOrPlace(false);

	//Retract Z
	returnValue = retractZ();

	//Inform gridContainers that this medicine has been taken
	updateGrid(medication.coord, false);

	return returnValue;
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