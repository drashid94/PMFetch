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
#include "MedicineDatabase.h"

MedicineDatabase::MedicineDatabase (const string& filename)
{
    //assuming database is in json file format as in software design spec
    // loadFromJSON(filename);
    //This call should populate allMedicines member variable
}