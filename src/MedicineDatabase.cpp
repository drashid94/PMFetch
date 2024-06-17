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

MedicineDatabase::MedicineDatabase() { }

MedicineDatabase::MedicineDatabase (const string& filename)
{
    //assuming database is in json file format as in software design spec
    // loadFromJSON(filename);
    //This call should populate allMedicines member variable
    (void)filename; // compiler warning
}

const void MedicineDatabase::medPrint(Medicine * med)
{
    printf("Printing Medicine:\n");
    printf("Med Name: %s\n", med->medication_name);
    printf("Med barcode: %s\n", med->barcode);
    printf("X Coord: %d", med->coord.x);
    printf("Y Coord: %d", med->coord.y);
    printf("On Shelf?: %d", med->onShelf);
    printf("Done Printing Medicine\n");
}

const vector<Medicine>* MedicineDatabase::getAllMedicines() const
{
    return &allMedicines;
}

