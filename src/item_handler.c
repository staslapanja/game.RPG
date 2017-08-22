
#include "item_handler.h"

void create_item_holder(struct item_holder **new_item_p, char name[], int cost, char category[], float stat[STAT_NUM])
{
    struct item_holder* new_item_holder = (struct item_holder*)malloc(sizeof(struct item_holder));

    if(new_item_holder == NULL)
    {
        //write to log!!
        //printf("Error creating a new item_holder.\n");
        exit(0);
    }
    strcpy(new_item_holder->name, name);
    new_item_holder->cost = cost;
    strcpy(new_item_holder->category, category);
    int i;
    for(i=0; i<STAT_NUM; i++){
        new_item_holder->stat[i] = stat[i];
    }
    new_item_holder->equiped = 0;
    *new_item_p = new_item_holder;
}

void prepend_item(struct globals *globals,char name[], int cost, char category[], float stat0, float stat1, float stat2)
{
    struct item_holder* new_item_holder = NULL;
    create_item_holder(&new_item_holder, name, cost, category, (float [STAT_NUM]){stat0,stat1,stat2});
    new_item_holder->next_item = globals->p_items_list;
    globals->p_items_list = new_item_holder;
    globals->item_list_num++;
}

void copy_to_storage(struct item_holder* item, struct globals *globals)
{
    struct item_holder* new_item_holder = NULL;
    create_item_holder(&new_item_holder, item->name, item->cost, item->category, item->stat);
    new_item_holder->next_item = globals->p_storage_item;
    globals->p_storage_item = new_item_holder;
    globals->storage_item_num++;
}

struct item_holder* remove_item(struct item_holder* list_ptr, struct item_holder* item){
    //if list is empty there is nothing to delete
    if (list_ptr == NULL){
        return NULL;
    }
    //if item is the first in the list
    if (item == list_ptr){
        struct item_holder *rm_item = list_ptr;
        list_ptr = list_ptr->next_item;
        rm_item->next_item = NULL;
        //if this is the last item in the list - only one item in the list
        if (rm_item == list_ptr)
            list_ptr = NULL;
        free(rm_item);
        return list_ptr;
    }
    //if item is last in the list
    if (item->next_item == NULL){
        struct item_holder *cursor = list_ptr;
        struct item_holder *prev_item = NULL;
        //find last item and remember previous reference to this item
        while(cursor->next_item != NULL){
            prev_item=cursor;
            cursor=cursor->next_item;
        }
        //if there is a previous item, point its next_item pointer to NULL
        if (prev_item != NULL)
            prev_item->next_item=NULL;
        //no need to check if there is only one item in the list - previous block handles that
        free(cursor);
        return list_ptr;
    }
    //if item is in the middle of the list (3 or more items in the list)
    struct item_holder *cursor = list_ptr;
    //find previous item pointing to the item to be removed
    while(cursor != NULL)
    {
        if(cursor->next_item == item)
            break;
        cursor = cursor->next_item;
    }
    //point previous item to the next item pointed by the removed item
    if (cursor != NULL){
        struct item_holder *rm_item = cursor->next_item;
        cursor->next_item = rm_item->next_item;
        rm_item->next_item = NULL;
        free(rm_item);
    }
    return list_ptr;
}

void remove_from_item_list(struct item_holder* item, struct globals *glb)
{
    glb->p_items_list = remove_item(glb->p_items_list, item);
    glb->item_list_num--;
}

void remove_from_storage_list(struct item_holder* item, struct globals *glb)
{
    glb->p_storage_item = remove_item(glb->p_storage_item, item);
    glb->storage_item_num--;
}

struct item_holder* search_item_by_name(struct item_holder* last,char name[])
{
    struct item_holder *cursor = last;
    while(cursor!=NULL)
    {
        if(!strcmp(cursor->name, name))
            return cursor;
        cursor = cursor->next_item;
    }
    return NULL;
}

struct item_holder* search_item_by_category(struct item_holder* last,char category[])
{
    struct item_holder *cursor = last;
    while(cursor!=NULL)
    {
        if(!strcmp(cursor->category, category))
            return cursor;
        cursor = cursor->next_item;
    }
    return NULL;
}

void set_stat(struct item_holder* s, int sel_stat, float val)
{
    s->stat[sel_stat] = val;
}

void gen_sword(struct globals *globals)
{
    //struct
    char name[NAME_SIZE];
    int cost;
    char category[CAT_SIZE];
    int stat[STAT_NUM];
    //prefixes
    char quality0[NAME_SIZE] = "rusty ";
    char quality1[NAME_SIZE] = "good ";
    char quality2[NAME_SIZE] = "well made ";
    int r = rand()%3;
    switch(r){
        case 0: strcat( quality0,"sword");
                strcpy(name, quality0);
                break;
        case 1: strcat( quality1,"sword");
                strcpy(name, quality1);
                break;
        case 2: strcat( quality2,"sword");
                strcpy(name, quality2);
                break;
        default : strcpy(name, "default");
    }
    cost = 20+(r*50);
    strcpy(category,"sword");
    stat[0] = 10+(r*15);
    stat[1] = 5-(r*1);
    stat[2] = r;
    prepend_item(globals, name, cost, category, stat[0], stat[1], stat[2]);
}

void create_item_list(struct globals *globals){

    //static items
    prepend_item(globals, "stick" ,   1 ,"hand",   1,  0,  1);
    prepend_item(globals, "knife" ,   5 ,"hand",   3,  0,0.5);
    prepend_item(globals, "axe"   ,  20 ,"hand",   9, -1,  5);
    prepend_item(globals, "hammer",  20 ,"hand",  10,  1, 15);
    //dynamically generated items
    gen_sword(globals);
    gen_sword(globals);
    gen_sword(globals);
};

void remove_list(struct globals *globals)
{
    struct item_holder *cursor, *nxt_item, *list_ptr;
    list_ptr = globals->p_items_list;
    if (list_ptr != NULL){
        cursor = list_ptr;
        while(cursor != NULL){
            nxt_item = cursor->next_item;
            cursor->next_item = NULL;
            free(cursor);
            cursor=nxt_item;
        }
    }
    globals->p_items_list = NULL;
    globals->item_list_num = 0;
}

void remove_storage_list(struct globals *globals)
{
    struct item_holder *cursor, *nxt_item, *list_ptr;
    list_ptr = globals->p_storage_item;
    if (list_ptr != NULL){
        cursor = list_ptr;
        while(cursor != NULL){
            nxt_item = cursor->next_item;
            cursor->next_item = NULL;
            free(cursor);
            cursor=nxt_item;
        }
    }
    globals->p_storage_item = NULL;
    globals->storage_item_num = 0;
}
