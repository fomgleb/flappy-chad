#pragma once

#include "base_includes.h"
#include "vector2.h"
#include "texture.h"

typedef struct s_nuke {
    t_vector2 position;
    t_vector2 velocity;
    t_texture texture;
} t_nuke;

t_nuke create_nuke(t_vector2 position, float vel_x, float vel_y, t_texture texture);
void update_nuke(t_nuke *nuke);
void render_nuke(t_nuke nuke);

