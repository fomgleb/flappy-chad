#include "../inc/buildings_spawner.h"

t_buildings_spawner create_buildings_spawner(float seconds_between_spawns, t_textures_arr available_textures,
float buildings_speed) {
    t_list *buildings_list = create_node(NULL);
    t_buildings_spawner buildings_spawner = {buildings_list, seconds_between_spawns, available_textures, buildings_speed, 0};
    return buildings_spawner;
}

void update_buildings_spawner(t_buildings_spawner *buildings_spawner, float delta) {
    if (buildings_spawner->timer >= buildings_spawner->seconds_between_spawns) {
        buildings_spawner->timer = 0;
        float random_y_offset = random_range(WINDOW_HEIGHT / -2 + 120, WINDOW_HEIGHT / 2 - 120);
        int top_random_texture_index = random_range(0, buildings_spawner->available_textures.size - 1);
        int bottom_random_texture_index = random_range(0, buildings_spawner->available_textures.size - 1);
        t_building top_building = create_building(WINDOW_WIDTH + 150, random_y_offset,
            buildings_spawner->available_textures.arr[top_random_texture_index], buildings_spawner->buildings_speed, SDL_FLIP_VERTICAL);
        t_building bottom_building = create_building(WINDOW_WIDTH + 150, WINDOW_HEIGHT + random_y_offset,
            buildings_spawner->available_textures.arr[bottom_random_texture_index], buildings_spawner->buildings_speed, SDL_FLIP_NONE);

        t_couple_of_buildings *couple_of_buildings = malloc(sizeof(t_couple_of_buildings));
        couple_of_buildings->top_building = top_building;
        couple_of_buildings->bottom_building = bottom_building;
        if (buildings_spawner->buildings_list != NULL && buildings_spawner->buildings_list->data == NULL) {
            buildings_spawner->buildings_list->data = couple_of_buildings;
        } else {
            push_back(&buildings_spawner->buildings_list, couple_of_buildings);
        }
    } else {
        buildings_spawner->timer += delta;
    }

    t_couple_of_buildings *first_couple_of_buildings = NULL;
    if (buildings_spawner->buildings_list != NULL)
        first_couple_of_buildings = (t_couple_of_buildings *)buildings_spawner->buildings_list->data;

    if (first_couple_of_buildings != NULL && first_couple_of_buildings->top_building.position.x <= -150) {
        free(buildings_spawner->buildings_list->data);
        pop_front(&(buildings_spawner->buildings_list));
    }
}

