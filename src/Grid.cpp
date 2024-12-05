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
#include <ncurses.h>
#include <fcntl.h>
#include <errno.h>
#include <termios.h>
#include <unistd.h>


// uint32_t Grid::getInputBarcodeComPort(std::string * barcode, int timeoutInSeconds, bool liftAndPlace, bool isFetch)
// {
// 	// std::cout << "Scanning..\n";
// 	// int fd = open("/dev/hidraw0", O_RDONLY);

// 	// if(fd < 0)
// 	// {
// 	// 	std::cout << "ERROR OPENING PORT\n";
// 	// }

// 	// while(1)
// 	// {
// 	// 	char readBuf[1024];
// 	// 	int n  = read(fd, &readBuf, sizeof(readBuf));
// 	// 	if(n < 0) cout << "Error reading\n";
// 	// 	cout << "readBuf:\n" << readBuf << "\n";asd
// 	// 	usleep(1000000);
// 	// }
// 	// struct termios tty;

// 	// if(tcgetattr(serial_port, &tty) != 0) {
//     // 	printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
// 	// }

// 	// tty.c_cflag &= ~PARENB;
// 	// tty.c_cflag &= ~CSTOPB;
// 	// tty.c_cflag &= ~CSIZE;
// 	// tty.c_cflag |= CS8;
// 	// tty.c_cflag &= ~CRTSCTS;
// 	// tty.c_lflag &= ~ICANON;
// 	// tty.c_lflag &= ~ECHO; // Disable echo
// 	// tty.c_lflag &= ~ECHOE; // Disable erasure
// 	// tty.c_lflag &= ~ECHONL; 
// 	// tty.c_lflag &= ~ISIG;
// 	// tty.c_iflag &= ~(IXON | IXOFF | IXANY);
// 	// tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);
// 	// tty.c_cc[VTIME] = 5;    // Wait for up to 1s (10 deciseconds), returning as soon as any data is received.
// 	// tty.c_cc[VMIN] = 0;
// 	// cfsetispeed(&tty, B9600);
// 	// cfsetospeed(&tty, B9600);

// 	// char read_buf[256];
// 	// while(1)
// 	// {
// 	// 	int n = read(serial_port, &read_buf, sizeof(read_buf));
// 	// 	if(n < 0)
// 	// 	{
// 	// 		std::cout << "No scan detected\n";
// 	// 	}
// 	// 	std::cout << "read_buf:\n";
// 	// 	std::cout << read_buf << "\n";
// 	// 	usleep(1000000);
// 	// }
	


// }

uint32_t Grid::getInputBarcode(std::string * barcode, int timeoutInSeconds, bool liftAndPlace, bool isFetch)
{    
	std::cout << "Scanning......\n";
	initscr();
    refresh();
    flushinp();
    if(liftAndPlace)
    {
    	if(isFetch)
    	{
    		containerLiftOrPlace(false);
			containerLiftOrPlace(true);		
    	}
    	else
    	{
	    	containerLiftOrPlace(true);
			containerLiftOrPlace(false);	
		}
    }
    char input[100];
    timeout(timeoutInSeconds*1000);
    int retVal = getstr(input);
    endwin();

    *barcode = input;
    return (retVal == ERR) ? 1 : SUCCESS;
}

Grid::Grid() 
{ }

Grid::Grid(Motor* motorUnitIn, MedicineDatabase* medicineDatabaseIn, int xdimensionsCm, int ydimensionsCm, int numUnitsX, int numUnitsY)
{
    if (xdimensionsCm <= 0 || ydimensionsCm <= 0 || numUnitsX <= 0 || numUnitsY <= 0) {
		//return out of bounds grid error
    }
    currentCoord = {0, 0};
    // pickupLocation = {3, 3}; // rightmost column of the bottom row
	returnLocations[0] = {0, GRID_UNIT_MAX_ROW-1};
	returnLocations[1] = {1, GRID_UNIT_MAX_ROW-1};
	returnLocations[2] = {2, GRID_UNIT_MAX_ROW-1}; 
	returnLocations[3] = {3, GRID_UNIT_MAX_ROW-1};
	returnLocations[4] = {4, GRID_UNIT_MAX_ROW-1};
	returnLocations[5] = {5, GRID_UNIT_MAX_ROW-1}; // All bottom row
    // Calculate pulses per unit for each dimension
	pulsesPerUnitX = 4620; // keith chnaged this from 1155 to 4620
	pulsesPerUnitY = 13150;
	pulsesPerLiftY = 2180;
	pulsesPerExtendZ = 8500;  // keith chnaged this from 4250 to 8500

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
				std::cout << "Space not occupied\n";
				col++;
				continue;		
			}
			std::cout << "Occupied\n";
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
	cout << "Updating Grid:\n " << shelfCoord.x << " " << shelfCoord.y << "\n";

	gridContainers[shelfCoord.y][shelfCoord.x].med.onShelf = returning;
	serializeGrid();
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
	serializeGrid();
	return SUCCESS;
}

uint32_t Grid::isMedValid(string barcode)
{
	uint32_t returnValue = SUCCESS;
	for(uint32_t x = 0; x < gridContainers.size(); x++)
	{
		for (uint32_t y = 0; y < gridContainers[x].size(); y++)
		{
			if (gridContainers[x][y].occupied == true)
			{
				if(gridContainers[x][y].med.barcode == barcode)
				{
					return returnValue;
				}
			}
		}
	}
	returnValue = 1;
	return returnValue;
}

uint32_t Grid::returnToShelfByBarcode(string barcode, bool force)// search grid by name and call returntoshelf
{
	uint32_t returnValue = SUCCESS;
	for(uint32_t x = 0; x < gridContainers.size(); x++)
	{
		for (uint32_t y = 0; y < gridContainers[x].size(); y++)
		{
			if (gridContainers[x][y].occupied == true)
			{
				if(gridContainers[x][y].med.barcode == barcode)
				{
					if(gridContainers[x][y].med.onShelf && !force)
					{
						std::cout << "Medication already on shelf\n";
						returnValue = 1;
					}
					else
					{
						returnValue = returnToShelf(gridContainers[x][y].med);
					}
					return returnValue;
				}
			}
		}
	}
	std::cout << "Medicine not on shelf\n";
	return returnValue;
}

uint32_t Grid::fetchFromShelfByBarcode(string barcode, int returnLocationNum)
{
	uint32_t returnValue = SUCCESS;
	for(uint32_t x = 0; x < gridContainers.size(); x++)
	{
		for (uint32_t y = 0; y < gridContainers[x].size(); y++)
		{
			if (gridContainers[x][y].occupied && gridContainers[x][y].med.onShelf)
			{
				if(gridContainers[x][y].med.barcode == barcode)
				{
					std::cout << "Barcode recognized\n";
					returnValue = fetchFromShelf(gridContainers[x][y].med, returnLocationNum);
				}				
			}
		}
	}
	return returnValue;
}

uint32_t Grid::getMedFromBarcode(string barcode, Medicine *med)
{
	uint32_t returnValue = SUCCESS;
	for(uint32_t x = 0; x < gridContainers.size(); x++)
	{
		for (uint32_t y = 0; y < gridContainers[x].size(); y++)
		{
			if (gridContainers[x][y].occupied)
			{
				if(gridContainers[x][y].med.barcode == barcode)
				{
					*med = gridContainers[x][y].med;
					return SUCCESS;
				}				
			}
		}
	}
	returnValue = 1;
	return returnValue;
}

uint32_t Grid::deleteFromShelf(string barcode)
{
	Medicine med;
	uint32_t returnValue = SUCCESS;
	if(getMedFromBarcode(barcode, &med) == SUCCESS)
	{
		if(med.onShelf)
		{
			std::cout << "Cannot delete something on the shelf\nFetch first\n";
			returnValue = 1;
		}
		else
		{
			gridContainers[med.coord.y][med.coord.x].occupied = false;
			serializeGrid();
		}
	}
	else
	{
		std::cout << "Could not find medicine\n";
		returnValue = 1;
	}
	return returnValue;
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
		GridUnit gridUnit{med, true};

		if(valid) 
		{
			addNewItemToGrid(&gridUnit);
			std::cout << "Item Added to Grid\n";
		}
		else
		{
			std::cout << "Medicine is invalid\n";
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

uint32_t Grid::addNewItemToGrid(string barcode)
{
	for(uint32_t x = 0; x < gridContainers.size(); x++)
	{
		for (uint32_t y = 0; y < gridContainers[x].size(); y++)
		{
			if(!gridContainers[x][y].occupied)
			{
				cout << "ANITG " << x << " " << y << "\n";
				Medicine med = {"", barcode, {(int)(y&INT32_MAX), (int)(x&INT32_MAX)}, 1};
				gridContainers[x][y].med = med;
				gridContainers[x][y].occupied = true;
				cout << "ANITG " << gridContainers[x][y].med.coord.x << " " << gridContainers[x][y].med.coord.y << "\n";
				cout << "Added medicine to gridContainers\n";
				serializeGrid();
				return SUCCESS;
			}
		}
	}
	return 1;
}



uint32_t Grid::shelfSetupByBarcode()
{
	for(int i = 0; i < NUM_RETURN_LOCATIONS; i++)
	{
		string barcode;
		moveXY(currentCoord, returnLocations[i], false);
		cout << "Calling get input func\n";
		uint32_t retval = getInputBarcode(&barcode, 1, true, false);
		if(retval == SUCCESS)
		{
			if(isMedValid(barcode) == SUCCESS)
			{
				std::cout << "Barcode is on shelf already\n";
				returnToShelfByBarcode(barcode, false);
				continue;
			}

			std::cout << "Container detected\nLocate empty spot on shelf\n";
			std::cout << "BARCODE: " << barcode << "\n";			
			if(addNewItemToGrid(barcode) != SUCCESS)
			{
				std::cout << "Grid: Could not place medicine on Shelf during setup\n";
				moveXY(currentCoord, {0,0}, false);
				return 1;
			}
			printGrid();
			Medicine med;
			getMedFromBarcode(barcode, &med);
			std::cout << med.coord.x << " " << med.coord.y << "\n";
			returnToShelf(med);
			std::cout << "New container moved to shelf\n";
		}
		else
		{
			std::cout << "Container not found\nMove to next return location\n";
		}
		usleep(500000);
	}
	return SUCCESS;
}

uint32_t Grid::extendZ()
{
	pthread_t ptid;
	motorUnit->move(Z_MOTOR_PIN, Z_MOTOR_DIR_PIN, EXTEND, pulsesPerExtendZ, Z_MOTOR_SPEED, &ptid);
	pthread_join(ptid, NULL);
	return SUCCESS;
}

uint32_t Grid::retractZ()
{
	pthread_t ptid;
	motorUnit->move(Z_MOTOR_PIN, Z_MOTOR_DIR_PIN, RETRACT, pulsesPerExtendZ, Z_MOTOR_SPEED, true, &ptid);
	pthread_join(ptid, NULL);
	return SUCCESS;
}

uint32_t Grid::containerLiftOrPlace(bool lift)
{
	uint8_t direction = 0;
	uint32_t numPulses = 0;

	std::cout << ((lift) ? "Lifting" : "Placing Down") << "On Y";
	numPulses = pulsesPerLiftY;
	direction = DOWN;
	if(lift) direction = UP;
	pthread_t ptid;
	motorUnit->move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, direction, numPulses, Y_MOTOR_SPEED, &ptid);
	pthread_join(ptid, NULL);
	return SUCCESS;

}

//Takes current location and destination and moves there
uint32_t Grid::moveXY(ShelfCoord coordCurr, ShelfCoord coordDest, bool pollingOn)
{
	uint8_t direction = 0;
	uint8_t numUnits = 0;
	uint32_t numXPulses = 0;
	uint32_t numYPulses = 0;

	pthread_t ptidx;
	pthread_t ptidy;
	//Move to destination X COORD
	int xMove = coordCurr.x - coordDest.x;
	if(xMove > 0){ direction = LEFT; }
	if(xMove < 0){ direction = RIGHT; }

	numUnits = abs(xMove);
	numXPulses = pulsesPerUnitX * numUnits;
	if(numXPulses > 0)
		motorUnit->move(X_MOTOR_PIN, X_MOTOR_DIR_PIN, direction, numXPulses, X_MOTOR_SPEED, pollingOn, &ptidx);
	
	//Move to destination Y COORD
	int yMove = coordCurr.y - coordDest.y;
	if(yMove > 0){ direction = UP; }
	if(yMove < 0){ direction = DOWN; }
	
	numUnits = abs(yMove);
	numYPulses = pulsesPerUnitY * numUnits;
	if(numYPulses > 0)
		motorUnit->move(Y_MOTOR_PIN, Y_MOTOR_DIR_PIN, direction, numYPulses, Y_MOTOR_SPEED, pollingOn, &ptidy);

	if(numXPulses > 0)
		pthread_join(ptidx, NULL);
	if(numYPulses > 0)
		pthread_join(ptidy, NULL);
	std::cout << "Finished Executing Thread\n";
	
	currentCoord = coordDest;
	return SUCCESS;
}

struct threadArguments {
  int* valuePtr;
  // Add other members for additional data
};


uint32_t Grid::returnToShelf() {
	cout << "Return sequence started\n";
	uint32_t returnValue = SUCCESS;
	string returnBarcodes[NUM_RETURN_LOCATIONS];

	for(int i = 0; i < NUM_RETURN_LOCATIONS; i++)
	{
		string barcode;
		moveXY(currentCoord, returnLocations[i], false);

		uint32_t retval = getInputBarcode(&barcode, 1, true, false);
		if(retval == SUCCESS)
		{
			std::cout << "BARCODE: " << barcode << "\n";			
			if(returnToShelfByBarcode(barcode, false) != SUCCESS)
			{
				std::cout << "Error\n";
			}
		}
		else
		{
			std::cout << "Container not found\nMove to next return location\n";
		}
		usleep(1000000);
	}

	return returnValue;
}

uint32_t Grid::returnToShelf(const Medicine& medication) {
	// check if it exists in gridContainers
	// call move sequence for picking up drop off container and placing in new position
	// update gridContainer
	// update medicine database to include x and y coordinates for the medicine
	
	uint32_t returnValue = SUCCESS;

	// //check valid coord

	// /* --------------------- pickup from pickup location ------------------- */
	// //Move to pickup location
	// returnValue = moveXY(currentCoord, pickupLocation, false);

	//Extend Z
	returnValue = extendZ();

	//Lift slightly
	returnValue = containerLiftOrPlace(true);

	//Retract Z
	returnValue = retractZ();

	/* --------------------- move to medicine's location ------------------- */
	returnValue = moveXY(currentCoord, medication.coord, false);

	//Extend Z
	returnValue = extendZ();

	// Lower container
	returnValue = containerLiftOrPlace(false);

	// retract Z
	returnValue = retractZ();

	//Inform gridContainers that this medicine has been returned
	updateGrid(medication.coord, true);
	serializeGrid();
	return returnValue;
}

uint32_t Grid::fetchFromShelf(const Medicine& medication, int returnLocationNum) {
	// check if it exists in gridContainer
	// calculate pulses and directions

	/* --------------------- pickup at medicine's location ------------------- */
	uint32_t returnValue = SUCCESS;


	returnValue = moveXY(currentCoord, medication.coord, false);

	//Extend Z
	returnValue = extendZ();

	// Lower container
	returnValue = containerLiftOrPlace(true);

	// retract Z
	returnValue = retractZ();


	/* --------------------- dropoff at pickup location ------------------- */

	string barcode;
	//Move to pickup locations
	for(int i = returnLocationNum; i < NUM_RETURN_LOCATIONS; i++)
	{
		string barcode;
		returnValue = moveXY(currentCoord, returnLocations[i], false);		
		returnValue = getInputBarcode(&barcode, 1, true, true);
		if(returnValue == 1) //Empty space found
		{
			break;
		}
		else
		{
			std::cout << "Space occupied - checking next";
		}
		if(i == NUM_RETURN_LOCATIONS-1) // No empty spaces
		{
			moveXY(currentCoord, medication.coord, false);
			extendZ();
			containerLiftOrPlace(false);
			retractZ();
			moveXY(currentCoord, {0,0}, false);
			return 1;
		}
	}
	
	//Extend Z
	returnValue = extendZ();

	//Lift slightly
	returnValue = containerLiftOrPlace(false);

	//Retract Z
	returnValue = retractZ();

	//Inform gridContainers that this medicine has been taken
	updateGrid(medication.coord, false);
	moveXY(currentCoord, {currentCoord.x,currentCoord.y-2}, true); //move one up
	serializeGrid();

	return returnValue;
}

uint32_t Grid::forceReturn()
{
	cout << "Force return sequence started\n";
	uint32_t returnValue = SUCCESS;
	string returnBarcodes[NUM_RETURN_LOCATIONS];

	for(int i = 0; i < NUM_RETURN_LOCATIONS; i++)
	{
		string barcode;
		moveXY(currentCoord, returnLocations[i], false);

		uint32_t retval = getInputBarcode(&barcode, 1, true, false); //confirm last 2 arguments
		if(retval == SUCCESS)
		{
			std::cout << "BARCODE: " << barcode << "\n";			
			if(returnToShelfByBarcode(barcode, true) != SUCCESS)
			{
				std::cout << "Error\n";
			}
		}
		else
		{
			std::cout << "Container not found\nMove to next return location\n";
		}
		usleep(1000000);
	}

	return returnValue;
}

std::string BoolToString(bool b)
{
  return b ? "true" : "false";
}

void Grid::serializeGrid() {
  std::ofstream file(gridfile);
  if (!file.is_open()) {
    // file opening error
    return;
  }

  // Write the number of GridUnits
  //int numUnits = gridContainers.size();
  //file << numUnits << std::endl;

  // Loop through each row and column and serialize its data
  for (auto & gridRow: gridContainers)
  {
	for (const GridUnit& unit : gridRow) {
		if (unit.occupied != TRUE)
		{
			continue;
		}
		// Serialize Medicine data
		file << std::to_string(unit.med.coord.x) << std::endl;
		file << std::to_string(unit.med.coord.y) << std::endl;
		file << unit.med.medication_name << std::endl;
		file << unit.med.barcode << std::endl;
		file << BoolToString(unit.med.onShelf) << std::endl;
		file << BoolToString(unit.occupied) << std::endl;
	}
  }

  file.close();
}

void Grid::recoverGrid() {
	std::ifstream file(gridfile);
	if (!file.is_open()) {
		std::cout << "file not found\n";
		return;
	}

	std::cout << "grid file found\n";
	// Clear the existing gridUnits vector before recovering
	int numUnitsY = gridContainers.size();
	int numUnitsX = gridContainers[0].size();

	gridContainers.clear();
	gridContainers.resize(numUnitsY);
	for(uint32_t i = 0; i < gridContainers.size(); i++)
	{
		gridContainers[i].resize(numUnitsX);
	}

	while(file.peek()!=EOF) {
		GridUnit unit;
		Medicine med;
		int unitX, unitY;
		string name, barcode;
		bool onshelf, occupied;

		string inputBuffer;

		std::getline(file, inputBuffer);	// X coordinate
		unitX = std::stoi(inputBuffer);
		std::getline(file, inputBuffer);	// Y coordinate
		unitY = std::stoi(inputBuffer);
		std::getline(file, name);			// medication_name
		std::getline(file, barcode);		// barcode
		std::getline(file, inputBuffer);	// onShelf
		onshelf = (inputBuffer == "true" ? TRUE : FALSE);
		std::getline(file, inputBuffer);	// occupied
		occupied = (inputBuffer == "true" ? TRUE : FALSE);

		med = {name, barcode, {unitX, unitY}, onshelf};

		gridContainers[unitY][unitX].med = med;
		gridContainers[unitY][unitX].occupied = occupied;
	}

  file.close();
}

/*
gridunit x
gridunit y
name
barcode
onshelf
occupied

struct GridUnit
{
	Medicine med;
	bool occupied;
};

struct Medicine {
  string medication_name;
  string barcode;
  ShelfCoord coord;
  bool onShelf;
  // maybe weight, quantity, empty bool
};
*/
