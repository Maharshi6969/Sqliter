// main.c (This is your GOAL)

#include "types.h"
#include "pager.h"
#include "btree.h"
#include "table.h"
#include "parser.h"
#include "executor.h"

//======================================================================================================
//                                     INPUT BUFFER FUNCTIONS
//======================================================================================================

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = (InputBuffer*) malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

void print_prompt(char filename[]){
    printf("%s > ", filename); 
}

void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0){
        printf("ERROR reading input\n");
        exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

void close_input_buffer(InputBuffer* input_buffer){
    free(input_buffer->buffer);
    free(input_buffer);
}

//======================================================================================================
//                                         MAIN FUNCTUION
//======================================================================================================

int main(int argc, char* argv[]){
    if(argc < 2){
        printf("Must supply a database filename. \n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];
    char filename_as_string[100];
    strcpy(filename_as_string, filename);
    filename[strlen(filename)-3] = '\0';
    Table* table = db_open(filename_as_string);
    InputBuffer* input_buffer = new_input_buffer();

    while (1){
        print_prompt(filename);
        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.'){
            switch (do_meta_command(input_buffer, table)){
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognised command %s . \n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)){
            case PREPARE_SUCCESS:
                break;
            case PREPARE_SYNTAX_ERROR:
                printf("Syntax error. couldn't parse statement. \n");
                continue;
            case PREPARE_STRING_TOO_LONG:
                printf("String too long error..");
                continue;
            case PREPARE_NEGATIVE_ID:
                printf("Negative id entered");
                continue;
            case PREPARE_UNRECGONIZED_STATEMENT:
                printf("Unrecognised keyword at the start of %s . \n", input_buffer->buffer);
                continue;
        }

        switch (execute_statement(&statement, table)){
            case EXECUTE_SUCCESS:
                printf("Executed.\n");
                break;
            case EXECUTE_DUPLICATE_KEY:
                printf("Error: Duplicate key. \n");
                break;
            case EXECUTE_TABLE_FULL:
                printf("Table full.\n");
                break;
        }
    }
}