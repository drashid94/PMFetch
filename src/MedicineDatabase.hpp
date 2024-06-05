#ifndef MEDICINEDATABASE_H
#define MEDICINEDATABASE_H

#include <vector>
#include <string>
#include "errors.hpp"
#include "defines.hpp"
using namespace std;

struct Medicine {
  string medication_name;
  int barcode;
  shelfCoord coord;

  // maybe weight, quantity, empty bool
};

class MedicineDatabase {
  public:
    MedicineDatabase (const string& filename); //assuming database is in json format as in software design spec
    const Medicine& searchMedicine(const string namePartial) const;
    const Medicine& searchMedicine(const int barcodeUPC) const;
    const vector<Medicine>* getAllMedicines() const; // returns allMedicines, likely to the grid
    int loadFromJSON(const string& filename); // loads allMedicines vector - assuming database is in json format as in software design spec

  private:
    vector<Medicine> allMedicines;
};

#endif // MEDICINEDATABASE_H