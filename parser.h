#ifndef PARSER_H
#define PARSER_H

#include "types.h"

PrepareResult prepare_insert(InputBuffer* input_buffer, Statement* statement);
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement);

#endif