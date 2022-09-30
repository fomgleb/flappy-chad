#pragma once

#include "base_includes.h"
#include "vector2.h"
#include "texture.h"

typedef struct s_building {
    t_vector2 position;
    t_texture texture;
    float speed;
    int flip_mode;
} t_building;

t_building create_building(float x, float y, t_texture texture, float speed, int flip_mode);
void update_building(t_building *building);
void render_building(t_building *building);

