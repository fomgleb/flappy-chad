#include "../inc/main.h"
#include "../inc/building.h"
#include "../inc/renderer.h"

t_building create_building(float x, float y, t_texture texture, float speed, int flip_mode) {
    t_vector2 building_position = {x, y};
    t_building building = {building_position, texture, speed, flip_mode};
    return building;
}

// Must be called each frame
void update_building(t_building *building) {
    building->position.x -= building->speed;
}

void render_building(t_building *building) {
    render_texture(building->texture, building->position, 0, building->flip_mode);
}

