#ifndef DATALOCAL_H_
#define DATALOCAL_H_
#include "sqlite3.h"
class datalocal {
public:
	datalocal();
	sqlite3 *db;
};
#endif