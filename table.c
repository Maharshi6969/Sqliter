#include"table.h"
#include"btree.h"
#include"pager.h"

Table* db_open(const char* filename){
    Pager* pager = pager_open(filename);

    Table* table = (Table*)malloc(sizeof(Table));
    table->pager = pager;
    table->root_page_num = 0;

    if(pager->num_pages == 0){
        //New database file. Initialize 0 as leaf node
        void* root_node = get_page(pager, 0);
        initialize_leaf_node(root_node);
    }
    return table;
}

void db_close(Table* table){
    Pager* pager = table->pager;

    for(uint32_t i = 0; i< pager->num_pages; i++){
        if(pager->pages[i] == NULL){
            continue;
        }
        pager_flush(pager, i);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }
    int result = close(pager->file_descriptor);
    if(result == -1){
        printf("Error closing db file.\n");
        exit(EXIT_FAILURE);
    }
    for(uint32_t i = 0;i<TABLE_MAX_PAGES;i++){
        void* page = pager->pages[i];
        if(page){
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
}

void free_table(Table* table){
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++){
        if (table->pager->pages[i] != NULL){
            free(table->pager->pages[i]);
            table->pager->pages[i] = NULL;
        }
    }
    free(table);
}

Cursor* table_start(Table* table){
    Cursor* cursor = table_find(table, 0);

    void* node = get_page(table->pager, cursor->page_num);
    uint32_t num_cells = *leaf_node_num_cells(node);
    cursor->end_of_table = (num_cells == 0);

    return cursor;
}