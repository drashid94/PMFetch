/*Database itself would be some data structure like an array or map or something
should have function for adding and removing something to a database
Could we feed it a JSON file so that it can load everything all at once?
 - location
 - is it being used?
 - barcode upc
 - weight??quantity left??empty??
 - getters
 - setters
*/
#include "MedicineDatabase.hpp"
#include <iostream>

MedicineDatabase::MedicineDatabase() { }

MedicineDatabase::MedicineDatabase (const string& filename)
{
    //assuming database is in json file format as in software design spec
    // loadFromJSON(filename);
    //This call should populate allMedicines member variable
    (void)filename; // compiler warning
}

void MedicineDatabase::medPrint(Medicine * med)
{
    string medName = med->medication_name;
    cout << "Printing Medicine:\n";
    cout << "Med Name: " << medName << "\n";
    cout << "Med barcode: "<< med->barcode << "\n";
    cout << "X Coord: " << med->coord.x << "\n";
    cout << "Y Coord: " << med->coord.y << "\n";
    cout << "On Shelf?: " << med->onShelf << "\n";
    cout << "Done Printing Medicine\n";
}

const vector<Medicine>* MedicineDatabase::getAllMedicines() const
{
    return &allMedicines;
}

