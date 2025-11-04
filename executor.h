#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "types.h"

MetaCommandResult do_meta_command(InputBuffer* input_buffer, Table* table);
ExecuteResult execute_insert(Statement* statement, Table* table);
ExecuteResult execute_select(Statement* statement, Table* table);
ExecuteResult execute_statement(Statement* statement, Table* table);

#endif