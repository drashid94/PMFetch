#ifndef MEDICINEDATABASE_H
#define MEDICINEDATABASE_H

#include <vector>
#include <string>
#include "errors.h"
using namespace std;

struct Medicine {
  string medication_name;
  int barcode;
  int x_coordinate; // x and y coordinate variables will be populated if the medication is on the shelf, otherwise 0
  int y_coordinate;

  // maybe weight, quantity, empty bool
};

class MedicineDatabase {
  public:
    const Medicine& searchMedicine(const string namePartial) const = 0;
    const Medicine& searchMedicine(const int barcodeUPC) const = 0;
    vector<Medicine> getAllMedicines() const = 0; // returns allMedicines, likely to the grid
    ErrorCode loadFromJSON(const string& filename) = 0; // loads allMedicines vector

  private:
    vector<Medicine> allMedicines;
};

#endif // MEDICINEDATABASE_H