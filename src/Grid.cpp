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

Grid::Grid() 
{ }

Grid::Grid(Motor* motorUnitIn, MedicineDatabase* medicineDatabaseIn, int xdimensionsCm, int ydimensionsCm, int numUnitsX, int numUnitsY)
{
    if (xdimensionsCm <= 0 || ydimensionsCm <= 0 || numUnitsX <= 0 || numUnitsY <= 0) {
		//return out of bounds grid error
    }
    currentCoord = {0, 0};
    pickupLocation = {3, 3};
    // Calculate pulses per unit for each dimension
	pulsesPerUnitX = 1200;
	pulsesPerUnitY = 16000;
	pulsesPerLiftY = 3000;
	pulsesPerExtendZ = 4500;

	gridContainers.resize(numUnitsY);
	for(uint32_t i = 0; i < gridContainers.size(); i++)
	{
		gridContainers[i].resize(numUnitsX);
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



void Grid::printGrid()
{
	int row = 0;
	for(vector<GridUnit> gv : gridContainers)
	{

		cout << "-------------------- ";
		cout << "Row " << row;
		cout << " --------------------\n";
		int col = 0;
		for(GridUnit gu : gv)
		{
			cout << "Column: " << col << "\n";
			if(!gu.occupied)
			{
				printf("Space not occupied\n");
				col++;
				continue;		
			}
			printf("Occupied\n");
			MedicineDatabase::medPrint(&gu.med);
			col++;
			cout << "\n";
		}
		row++;
	}
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

	gridContainers[shelfCoord.y][shelfCoord.x].med.onShelf = returning;
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
	uint32_t x = gridUnit->med.coord.x;
	uint32_t y = gridUnit->med.coord.y;
	// memcpy((void*)&gridContainers[y][x], (void*)gridUnit, sizeof(GridUnit));
	gridContainers[y][x] = *gridUnit;
	return SUCCESS;
}

void Grid::isMedValid(Medicine * med, bool &valid)
{
	//TODO checks
	//Check bcode doesnt already exist on shelf and validity of values	
	(void)med;
	valid = true;
}

uint32_t Grid::returnToShelfByBarcode (string barcode) // search grid by name and call returntoshelf
{
	for(uint32_t x = 0; x < gridContainers.size(); x++)
	{
		for (uint32_t y = 0; y < gridContainers[x].size(); y++)
		{
			if (gridContainers[x][y].occupied == true)
			{
				if(gridContainers[x][y].med.barcode == barcode)
				{
					printf("PLace item in drop off, then click enter -");
					cin.ignore();
					cin.ignore();
					returnToShelf(gridContainers[x][y].med);
					return SUCCESS;
				}
			}
		}
	}
	return 1;
}

uint32_t Grid::fetchFromShelfByName (string medicationName) // search grid by name and call fetchfromshelf
{
	for(uint32_t x = 0; x < gridContainers.size(); x++)
	{
		for (uint32_t y = 0; y < gridContainers[x].size(); y++)
		{
			if (gridContainers[x][y].occupied == true)
			{
				if(gridContainers[x][y].med.medication_name == medicationName)
				{
					fetchFromShelf(gridContainers[x][y].med);
					return SUCCESS;
				}
			}
		}
	}
	return 1;
}

//take in bunch of inputs to create Medicine objects and set their location on shelf
//Do this during setup when things are already on shelf
uint32_t Grid::shelfSetup() {
	bool valid = false;
	//What already exist on the shelf?
	string name;
	string bcode;
	int x = 0;
	int y = 0;
	while(true)
	{
		cout << "Enter Name of Med:\n";
		cin >> name;
		cout << "Scan Barcode of medication\n";
		cin >> bcode;
		cout << "Enter Column Number: \n";
		cin >> x;
		cout << "Enter Row Number: \n";
		cin >> y;

		Medicine med{name, bcode, {uint8_t(x & 0x7f),uint8_t(y & 0x7f)}, true /* onShelf */};
		isMedValid(&med, valid);
		GridUnit gridUnit{med, true};

		if(valid) 
		{
			addNewItemToGrid(&gridUnit);
			printf("Item Added to Grid\n");
		}
		else
		{
			printf("Medicine is invalid\n");
		}

		int exit = 0;
		cout << "0 to EXIT 1 to CONTINUE\n";
		cin >> exit;
		if(exit == 0)
		{
			break;
		}

	}
	return SUCCESS;
}

uint32_t Grid::extendZ()
{
	motorUnit->move(Z_MOTOR_PIN, Z_MOTOR_DIR_PIN, EXTEND, pulsesPerExtendZ, Z_MOTOR_SPEED);
	return SUCCESS;
}

uint32_t Grid::retractZ()
{
	motorUnit->move(Z_MOTOR_PIN, Z_MOTOR_DIR_PIN, RETRACT, pulsesPerExtendZ, Z_MOTOR_SPEED);
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
	motorUnit->move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, direction, numPulses, Y_MOTOR_SPEED);
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
	motorUnit->move(X_MOTOR_PIN, X_MOTOR_DIR_PIN, direction, numPulses, X_MOTOR_SPEED);

	//Move to destination Y COORD
	int yMove = coordCurr.y - coordDest.y;
	if(yMove > 0){ direction = UP; }
	if(yMove < 0){ direction = DOWN; }
	
	numUnits = abs(yMove);
	numPulses = pulsesPerUnitY * numUnits;
	motorUnit->move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, direction, numPulses, Y_MOTOR_SPEED);
	
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