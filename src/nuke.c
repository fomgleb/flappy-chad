#include "../inc/main.h"
#include "../inc/nuke.h"
#include "../inc/vector2.h"
#include "../inc/renderer.h"
#include "../inc/texture.h"

t_nuke create_nuke(t_vector2 position, float vel_x, float vel_y, t_texture texture) {
    t_nuke new_entity = {position, {vel_x, vel_y}, texture};
    return new_entity;
}

// Must executes each frame
void update_nuke(t_nuke *nuke) {
    t_vector2 new_nuke_position = plus_vectors(nuke->position, nuke->velocity);
    if (new_nuke_position.y >= 0) {
        nuke->position = new_nuke_position;
    } else {
        nuke->velocity = devide_vector_by(negate_vector(nuke->velocity), 2);
    }
}

void render_nuke(t_nuke nuke) {
    render_texture(nuke.texture, nuke.position, nuke.velocity.y * 5, SDL_FLIP_NONE);
}

