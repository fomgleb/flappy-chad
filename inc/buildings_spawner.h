#pragma once

#include "main.h"
#include "linked_list.h"
#include "building.h"
#include "random.h"
#include "texture.h"
#include "arrays.h"

typedef struct s_buildings_spawner {
    t_list *buildings_list;
    float seconds_between_spawns;
    t_textures_arr available_textures;
    float buildings_speed;  
    float timer;
} t_buildings_spawner;

typedef struct s_couple_of_buildings {
    t_building top_building;
    t_building bottom_building;
} t_couple_of_buildings;

t_buildings_spawner create_buildings_spawner(float seconds_between_spawns, t_textures_arr available_textures,
float buildings_speed);
void update_buildings_spawner(t_buildings_spawner *buildings_spawner, float delta);

