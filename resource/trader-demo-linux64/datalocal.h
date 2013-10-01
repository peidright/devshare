#ifndef DATALOCAL_H_
#define DATALOCAL_H_
#include "sqlite3.h"
#include <string>
#include <vector>
using namespace std;
class datalocal {
public:
	datalocal();
	~datalocal();
	void get_product_list(vector<string> *product_list);
	sqlite3 *db;
};
#endif