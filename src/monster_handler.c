#include "monster_handler.h"

void create_monster_object(struct monster_object **new_monster_p, char name[], int id, float health, float health_mod, float damage, float damage_mod, float defence, float defence_mod, float xp, float credits, struct item_holder *loot)
{
    struct monster_object* new_monster = (struct monster_object*)malloc(sizeof(struct monster_object));
    if(new_monster == NULL)
    {
        //write to log!!
        //printf("Error creating a new new_monster.\n");
        exit(0);
    }
    strcpy(new_monster->name, name);
    new_monster->id = id;
    new_monster->health = health;
    new_monster->health_mod = health_mod;
    new_monster->damage = damage;
    new_monster->damage_mod = damage_mod;
    new_monster->defence = defence;
    new_monster->defence_mod = defence_mod;
    new_monster->xp = xp;
    new_monster->credits = credits;
    new_monster->loot = loot;

    *new_monster_p = new_monster;
}

void prepend_monster(struct globals *glb, char name[], int id, float health, float health_mod, float damage, float damage_mod, float defence, float defence_mod, float xp, float credits, struct item_holder *loot)
{
    struct monster_object* new_monster = NULL;
    create_monster_object(&new_monster, name, id, health, health_mod, damage, damage_mod, defence, defence_mod, xp, credits, loot);
    new_monster->next_monster = glb->p_monster_list;
    glb->p_monster_list = new_monster;
    glb->monster_list_num++;
}

struct monster_object* remove_monster(struct monster_object* list_ptr, struct monster_object* monster)
{
    //if list is empty there is nothing to delete
    if (list_ptr == NULL){
        return NULL;
    }
    //if monster is the first in the list
    if (monster == list_ptr){
        struct monster_object *rm_monster = list_ptr;
        list_ptr = list_ptr->next_monster;
        rm_monster->next_monster = NULL;
        //if this is the last monster in the list - only one monster in the list
        if (rm_monster == list_ptr)
            list_ptr = NULL;
        free(rm_monster);
        return list_ptr;
    }
    //if monster is last in the list
    if (monster->next_monster == NULL){
        struct monster_object *cursor = list_ptr;
        struct monster_object *prev_monster = NULL;
        //find last monster and remember previous reference to this monster
        while(cursor->next_monster != NULL){
            prev_monster=cursor;
            cursor=cursor->next_monster;
        }
        //if there is a previous monster, point its next_monster pointer to NULL
        if (prev_monster != NULL)
            prev_monster->next_monster=NULL;
        //no need to check if there is only one monster in the list - previous block handles that
        free(cursor);
        return list_ptr;
    }
    //if monster is in the middle of the list (3 or more items in the list)
    struct monster_object *cursor = list_ptr;
    //find previous monster pointing to the monster to be removed
    while(cursor != NULL)
    {
        if(cursor->next_monster == monster)
            break;
        cursor = cursor->next_monster;
    }
    //point previous monster to the next monster pointed by the removed monster
    if (cursor != NULL){
        struct monster_object *rm_monster = cursor->next_monster;
        cursor->next_monster = rm_monster->next_monster;
        rm_monster->next_monster = NULL;
        free(rm_monster);
    }
    return list_ptr;
}

void remove_from_monster_list(struct monster_object* monster, struct globals *glb)
{
    glb->p_monster_list = remove_monster(glb->p_monster_list, monster);
    glb->monster_list_num--;
}

void create_monster_list(struct globals *glb)
{

    //monsters
    //                  name        , id, health, health_mod, damage, damage_mod, defence, defence_mod,    xp, credits, loot
    prepend_monster(glb, "monster 0",  0,      5,          1,      1,          1,       0,           1,     2,       0, NULL);
    prepend_monster(glb, "monster 1",  0,     50,          1,      5,          1,       1,           1,     5,       2, NULL);
    prepend_monster(glb, "monster 2",  0,    500,          1,     25,          1,       4,           1,    20,      11, NULL);
    prepend_monster(glb, "monster 3",  0,   1000,          1,     70,          1,      20,           1,   100,      28, NULL);
    prepend_monster(glb, "monster 4",  0,   3000,          1,    200,          1,     100,           1,  1000,     165, NULL);
    prepend_monster(glb, "boss"     ,  0,  10000,          1,    500,          1,     500,           1, 10000,    5000, NULL);
};

void remove_monster_list(struct globals *glb)
{
    struct monster_object *cursor, *nxt_monster, *list_ptr;
    list_ptr = glb->p_monster_list;
    if (list_ptr != NULL){
        cursor = list_ptr;
        while(cursor != NULL){
            nxt_monster = cursor->next_monster;
            cursor->next_monster = NULL;
            free(cursor);
            cursor=nxt_monster;
        }
    }
    glb->p_monster_list = NULL;
    glb->monster_list_num = 0;
}
