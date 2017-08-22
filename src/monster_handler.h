#ifndef MONSTER_HANDLER_H
#define MONSTER_HANDLER_H

#include "defines.h"
#include "global_handler.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct monster_object{
    char name[19];
    int id;
    float health;
    float health_mod;
    float damage;
    float damage_mod;
    float defence;
    float defence_mod;
    float xp;
    float credits;
    struct item_holder *loot;
    struct monster_object *next_monster;
};

void create_monster_object(struct monster_object **new_monster_p, char name[], int id, float health, float health_mod, float damage, float damage_mod, float defence, float defence_mod, float xp, float credits, struct item_holder *loot);
void prepend_monster(struct globals *glb, char name[], int id, float health, float health_mod, float damage, float damage_mod, float defence, float defence_mod, float xp, float credits, struct item_holder *loot);
struct monster_object* remove_monster(struct monster_object* list_ptr, struct monster_object* monster);
void remove_from_monster_list(struct monster_object* monster, struct globals *glb);
void create_monster_list(struct globals *glb);
void remove_monster_list(struct globals *glb);

#endif
