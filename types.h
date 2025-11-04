#ifndef TYPES_H
#define TYPES_H

//Included tools 
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

//All the constant definitions
#define INVALID_PAGE_NUM UINT32_MAX
#define TABLE_MAX_PAGES 100
#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define size_of_attribute(Struct, Attribute) sizeof(((Struct*)0)->Attribute)

//structs and enums
typedef struct{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE + 1];
    char email[COLUMN_EMAIL_SIZE + 1];
} Row;

typedef enum{
    NODE_INTERNAL,
    NODE_LEAF,
}NodeType;

//======================================================================================================
//======================================================================================================
//                                     FIXED ROW CONSTRAINTS
//======================================================================================================
//======================================================================================================

extern const uint32_t ID_SIZE;
extern const uint32_t USERNAME_SIZE;
extern const uint32_t EMAIL_SIZE;
extern const uint32_t ID_OFFSET;
extern const uint32_t USERNAME_OFFSET;
extern const uint32_t EMAIL_OFFSET;
extern const uint32_t ROW_SIZE;
extern const uint32_t PAGE_SIZE;

//======================================================================================================
//======================================================================================================
//                                   COMMON NODE HEADER LAYOUT
//======================================================================================================
//======================================================================================================

extern const uint32_t NODE_TYPE_SIZE;
extern const uint32_t NODE_TYPE_OFFSET;
extern const uint32_t IS_ROOT_SIZE;
extern const uint32_t IS_ROOT_OFFSET;
extern const uint32_t PARENT_POINTER_SIZE;
extern const uint32_t PARENT_POINTER_OFFSET;
extern const uint32_t COMMON_NODE_HEADER_SIZE;

//======================================================================================================
//======================================================================================================
//                                   LEAF NODE HEADER LAYOUT
//======================================================================================================
//======================================================================================================

extern const uint32_t LEAF_NODE_NUM_CELL_SIZE;
extern const uint32_t LEAF_NODE_NUM_CELL_OFFSET;
extern const uint32_t LEAF_NODE_NEXT_LEAF_SIZE;
extern const uint32_t LEAF_NODE_NEXT_LEAF_OFFSET;
extern const uint32_t LEAF_NODE_HEADER_SIZE;
 
//======================================================================================================
//======================================================================================================
//                                   LEAF NODE BODY LAYOUT
//======================================================================================================
//======================================================================================================

extern const uint32_t LEAF_NODE_KEY_SIZE;
extern const uint32_t LEAF_NODE_KEY_OFFSET;
extern const uint32_t LEAF_NODE_VALUE_SIZE;
extern const uint32_t LEAF_NODE_VALUE_OFFSET;
extern const uint32_t LEAF_NODE_CELL_SIZE;
extern const uint32_t LEAF_NODE_SPACE_FOR_CELLS;
extern const uint32_t LEAF_NODE_MAX_CELLS;

//======================================================================================================
//======================================================================================================
//                                   LEAF NODE BODY LAYOUT
//======================================================================================================
//======================================================================================================

extern const uint32_t INTERNAL_NODE_NUM_KEYS_SIZE;
extern const uint32_t INTERNAL_NODE_NUM_KEYS_OFFSET;
extern const uint32_t INTERNAL_NODE_RIGHT_CHILD_SIZE;
extern const uint32_t INTERNAL_NODE_RIGHT_CHILD_OFFSET;
extern const uint32_t INTERNAL_NODE_HEADER_SIZE;

//======================================================================================================
//======================================================================================================
//                                   LEAF NODE BODY LAYOUT
//======================================================================================================
//======================================================================================================

extern const uint32_t INTERNAL_NODE_KEY_SIZE;
extern const uint32_t INTERNAL_NODE_CHILD_SIZE;
extern const uint32_t INTERNAL_NODE_CELL_SIZE;
extern const uint32_t LEAF_NODE_RIGHT_SPLIT_COUNT;
extern const uint32_t INTERNAL_NODE_SPACE_FOR_CELLS;
extern const uint32_t INTERNAL_NODE_MAX_CELLS;
extern const uint32_t LEAF_NODE_LEFT_SPLIT_COUNT;


//======================================================================================================
//======================================================================================================
//                                  ENUM AND STRUCT DECLARATIONS
//======================================================================================================
//======================================================================================================

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    uint32_t num_pages;
    void* pages[TABLE_MAX_PAGES];
} Pager;

typedef struct{
    uint32_t root_page_num;
    Pager* pager;
} Table;

// Struct for defining prompt
typedef struct{
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

// Statements Types
typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;

// Statement Datatype
typedef struct {
  StatementType type;
  Row row_to_insert; // only used by insert statements
} Statement;

// Commands 
typedef enum{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// Results for prepare
typedef enum{
    PREPARE_SUCCESS,
    PREPARE_STRING_TOO_LONG,
    PREPARE_NEGATIVE_ID,
    PREPARE_SYNTAX_ERROR,
    PREPARE_UNRECGONIZED_STATEMENT
} PrepareResult;

// Results for execute
typedef enum{
    EXECUTE_SUCCESS,
    EXECUTE_DUPLICATE_KEY,
    EXECUTE_TABLE_FULL
} ExecuteResult;

//used the Cursor data structure that keeps track of the 
//table
//number of row its on
//is it end of table or not
typedef struct{
    Table* table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;

#endif