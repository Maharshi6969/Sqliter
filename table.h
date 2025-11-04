#ifndef TABLE_H
#define TABLE_H

#include "types.h"

Table* db_open(const char* filename);
void db_close(Table* table);
void free_table(Table* table);
Cursor* table_start(Table* table);

#endif