#ifndef ITEM_HANDLER_H
#define ITEM_HANDLER_H

#include "defines.h"
#include "global_handler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct item_holder{
    char name[NAME_SIZE];
    int cost;
    char category[CAT_SIZE];
    float stat[STAT_NUM];
    int equiped;
    struct item_holder *next_item;
};

void create_item_holder(struct item_holder **new_item_p, char name[], int cost, char category[], float stat[STAT_NUM]);
void prepend_item(struct globals *globals,char name[], int cost, char category[], float stat0, float stat1, float stat2);
void copy_to_storage(struct item_holder* item, struct globals *globals);
struct item_holder* remove_item(struct item_holder* list_ptr, struct item_holder* item);
void remove_from_item_list(struct item_holder* item, struct globals *glb);
void remove_from_storage_list(struct item_holder* item, struct globals *glb);
struct item_holder* search_item_by_name(struct item_holder* last,char name[]);
struct item_holder* search_item_by_category(struct item_holder* last,char category[]);
void set_stat(struct item_holder* s, int sel_stat, float val);
void gen_sword(struct globals *globals);
void create_item_list(struct globals *globals);
void remove_list(struct globals *globals);
void remove_storage_list(struct globals *globals);

#endif
