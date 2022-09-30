#include "../inc/main.h"

void init_sdl() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL_INIT has failed. SDL_ERROR: %s\n", SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        printf("IMG_INIT has failed. SDL_ERROR: %s\n", SDL_GetError());
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init has failed. SDL_ERROR: %s\n", SDL_GetError());
    }
}

void free_buildings(t_buildings_spawner *buildings_spawner) {
    for (t_list *node = buildings_spawner->buildings_list; node != NULL; node = node->next) {
        free(node->data);
    }
    clear_list(&buildings_spawner->buildings_list);
}

int main () {
    srand(time(NULL));
    init_sdl();
    render_window("Game kurilshika v0.2", WINDOW_WIDTH, WINDOW_HEIGHT);
    printf("Game oppened successfully\n");

    SDL_Rect window_rect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Rect centered_rect = {500, 200, WINDOW_WIDTH - 1000, WINDOW_HEIGHT - 400};

    // Loading textures
    SDL_Texture *sky_texture = IMG_LoadTexture(get_renderer(), "resource/images/sky.jpg");
    // t_texture nuke_texture = load_texture("resource/nuke.png", 0.2);
    t_texture nuke_texture = load_texture("resource/images/gigachad2.png", 0.2);
    t_texture building_texture1 = load_texture("resource/images/building1.png", 1); // ~1.4 for Full HD
    t_texture building_texture2 = load_texture("resource/images/building2.png", 1); // ~1.4 for Full HD
    t_texture building_texture3 = load_texture("resource/images/building3.png", 1); // ~1.4 for Full HD
    t_texture building_texture4 = load_texture("resource/images/building4.png", 1); // ~1.4 for Full HD
    t_textures_arr buildings_textures = {malloc(4 * sizeof(t_texture)), 4};
    buildings_textures.arr[0] = building_texture1;
    buildings_textures.arr[1] = building_texture2;
    buildings_textures.arr[2] = building_texture3;
    buildings_textures.arr[3] = building_texture4;

    // Init audio
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    Mix_Music *menu_music = Mix_LoadMUS("resource/audio/darren-curtis-danger-around-the-corner.mp3");
    Mix_Music *music = Mix_LoadMUS("resource/audio/soundtrack.mp3");
    Mix_Chunk *bonk_sound = Mix_LoadWAV("resource/audio/bonk.wav");

    // Init colors
    SDL_Color white_color = {255, 255, 255, 255};
    SDL_Color red_color = {255, 0, 0, 255};
    SDL_Color gold_color = {230, 199, 0, 255};
    SDL_Color black_color = {0, 0, 0, 255};
    SDL_Color grey_color = {100, 100, 100, 255};

    // Loading fonts
    TTF_Font *ubuntu_bold_24 = TTF_OpenFont("resource/fonts/Ubuntu-Bold.ttf", 24);
    // TTF_Font *ubuntu_bold_40 = TTF_OpenFont("resource/fonts/Ubuntu-Bold.ttf", 40);
    TTF_Font *bungee_spice_regular_40 = TTF_OpenFont("resource/fonts/BungeeSpice-Regular.ttf", 40);

    // Init Labels
    t_label new_game_label = create_label("New Game", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50);
    t_label continue_label = create_label("Continue", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 50);
    t_label about_label = create_label("About", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 20);
   
    t_label settings_label = create_label("Settings", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 10);
    t_label set_volume_label = create_label("Volume:", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2 - 40, WINDOW_HEIGHT / 2 - 50);
    t_label increase_volume_label = create_label(">", ubuntu_bold_24, grey_color, WINDOW_WIDTH / 2 + 95, WINDOW_HEIGHT / 2 - 50);
    t_label decrease_volume_label = create_label("<", ubuntu_bold_24, grey_color, WINDOW_WIDTH / 2 + 25, WINDOW_HEIGHT / 2 - 50);
    t_label current_volume_label = create_label("0", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2 + 45, WINDOW_HEIGHT / 2 - 50);
    t_label settings_back_label = create_label("Back", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 50);

    t_label quit_label = create_label("Quit", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 40);
    t_label back_label = create_label("Back", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + 10);
    t_label score_counter_label = create_label("0", bungee_spice_regular_40, gold_color, WINDOW_WIDTH / 2, 30);
    t_label tip_label = create_label("Press 'W' to fly", ubuntu_bold_24, black_color, 100, WINDOW_HEIGHT - 50);
    t_label developers_label = create_label("Developers:", bungee_spice_regular_40, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 220);
    t_label gleb_label = create_label("fomgleb", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 170);
    t_label maxim_label = create_label("maximus", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 140);
    t_label mihail_label = create_label("mihail", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 110);
    t_label kirill_label = create_label("kirill", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 - 80);
    t_label score_text = create_label("Score: ", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2 - 15, WINDOW_HEIGHT / 2 - 90);
    t_label loose_menu_score = create_label("0", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2 + 35, WINDOW_HEIGHT / 2 - 90);
    t_label best_score_text = create_label("Best score: ", bungee_spice_regular_40, gold_color, WINDOW_WIDTH / 2 - 25, 30);
    t_label best_score_label = create_label("0", bungee_spice_regular_40, gold_color, WINDOW_WIDTH / 2 + 140, 30);
    t_label main_menu_label = create_label("Main Menu", ubuntu_bold_24, white_color, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 +30);
    t_labels_arr loose_menu_labels = {malloc(4 * sizeof(t_label)), 4};
    loose_menu_labels.arr[0] = score_text;
    loose_menu_labels.arr[1] = loose_menu_score;
    loose_menu_labels.arr[2] = best_score_label;
    loose_menu_labels.arr[3] = best_score_text;
    t_labels_arr about_menu_labels = {malloc(5 * sizeof(t_label)), 5};
    about_menu_labels.arr[0] = developers_label;
    about_menu_labels.arr[1] = gleb_label;
    about_menu_labels.arr[2] = maxim_label;
    about_menu_labels.arr[3] = mihail_label;
    about_menu_labels.arr[4] = kirill_label;
    t_labels_arr main_menu_labes = {malloc(2 * sizeof(t_label)), 2};
    main_menu_labes.arr[0] = best_score_label;
    main_menu_labes.arr[1] = best_score_text;

    t_labels_arr settings_menu_labels = {malloc(2 * sizeof(t_label)), 2};
    settings_menu_labels.arr[0] = set_volume_label;
    settings_menu_labels.arr[1] = current_volume_label;

    // Init Buttons
    t_button new_game_button = {new_game_label, red_color, white_color, NEW_GAME};
    t_button continue_button = {continue_label, red_color, white_color, CONTINUE};

    t_button settings_button = {settings_label, red_color, white_color, SETTINGS};
    t_button settings_increase_vol_button = {increase_volume_label, red_color, grey_color, INCREASE_VOLUME};
    t_button settings_decrease_vol_button = {decrease_volume_label, red_color, grey_color, DECREASE_VOLUME};
    t_button settings_back_button = {settings_back_label, red_color, white_color, BACK};

    t_button about_button = {about_label, red_color, white_color, ABOUT};
    t_button quit_button = {quit_label, red_color, white_color, QUIT};
    t_button back_button = {back_label, red_color, white_color, BACK};
    t_button main_menu_button = {main_menu_label, red_color, white_color, GOTO_MAIN_MENU};

    t_buttons_arr main_menu_buttons = {malloc(4 * sizeof(t_button)), 4};
    main_menu_buttons.arr[0] = new_game_button;
    main_menu_buttons.arr[1] = about_button;
    main_menu_buttons.arr[2] = settings_button;
    main_menu_buttons.arr[3] = quit_button;

    t_buttons_arr settings_menu_buttons = {malloc(3 * sizeof(t_button)), 3};
    settings_menu_buttons.arr[0] = settings_increase_vol_button;
    settings_menu_buttons.arr[1] = settings_decrease_vol_button;
    settings_menu_buttons.arr[2] = settings_back_button;

    t_buttons_arr loose_menu_buttons = {malloc(2 * sizeof(t_button)), 2};
    loose_menu_buttons.arr[0] = new_game_button;
    loose_menu_buttons.arr[1] = main_menu_button;
    t_buttons_arr escape_menu_buttons = {malloc(2 * sizeof(t_button)), 2};
    escape_menu_buttons.arr[0] = continue_button;
    escape_menu_buttons.arr[1] = main_menu_button;
    t_buttons_arr about_menu_buttons = {malloc(1 * sizeof(t_button)), 1};
    about_menu_buttons.arr[0] = back_button;

    const int FPS = 60;
    const int MAX_FRAME_DELAY = 1000 / FPS;
    Uint32 frame_start = 0;
    Uint32 frame_time = 0;
    float delta = 0;
    Uint32 mouse_moved = SDL_GetTicks();

    int score_count = 0;
    int best_score = load_int_from_file(PATH_TO_SAVE_FILE);

    t_nuke nuke = create_nuke(START_PLAYER_POS, 0, 0, nuke_texture);
    t_buildings_spawner buildings_spawner = create_buildings_spawner(2, buildings_textures, 7);
    SDL_Event event;
    const Uint8 *key_states = SDL_GetKeyboardState(NULL);
    bool is_first_build_setted = false; 
    bool is_score_increased = false; 

    bool loose = false;
    bool exit_request = false;
    bool understood_controls = false;
    bool main_menu_request = true;
    bool new_game_started = false;

    Uint32 hide_cursor_after_ms = 2000;
    int volume = 100;

    while(!exit_request) {
        new_game_started = false;
        if (main_menu_request)
            Mix_PlayMusic(menu_music, -1);
        while (main_menu_request) {
            char buf[10];
            SDL_itoa(best_score, buf, 10);
            main_menu_labes.arr[0].text = buf;
            create_text_texture(&best_score_label);
            Mix_VolumeMusic(volume);
            t_button_action main_menu_result = show_menu(main_menu_buttons, &main_menu_labes, black_color, &window_rect, false);
            if (main_menu_result == NEW_GAME) {
                Mix_PlayMusic(music, -1);
                Mix_VolumeMusic(volume);
                Mix_Volume(-1, volume);
                new_game_started = true;
                main_menu_request = false;
            } else if (main_menu_result == ABOUT) {
                show_menu(about_menu_buttons, &about_menu_labels, black_color, &window_rect, false);
            } else if (main_menu_result == SETTINGS) {
                show_settings_menu(settings_menu_buttons, &settings_menu_labels, black_color, &window_rect, false, &volume);
            } else if (main_menu_result == QUIT) {
                exit_request = true;
                main_menu_request = false;
            }    
        }
        
        frame_start = SDL_GetTicks();

        // Input
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                loose = true;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    exit_request = true;
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    Mix_PauseMusic();
                    SDL_ShowCursor(true);
                    Uint32 menu_started = SDL_GetTicks();
                    t_button_action loose_menu_result = show_menu(escape_menu_buttons, NULL, black_color, &centered_rect, true);
                    frame_start += SDL_GetTicks() - menu_started;
                    if (loose_menu_result == CONTINUE) {
                        Mix_ResumeMusic();
                    } else if (loose_menu_result == GOTO_MAIN_MENU) {
                        main_menu_request = true;
                    }
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                SDL_ShowCursor(true);
                mouse_moved = SDL_GetTicks();
            }
        }

        // Nuke moving, some updates and calculations
        if (SDL_GetTicks() - mouse_moved >= hide_cursor_after_ms) {
            SDL_ShowCursor(false);
        }
        if (key_states[SDL_SCANCODE_W]) {
            understood_controls = true;
            nuke.velocity.y -= (delta * 13);
        } else {
            nuke.velocity.y += (delta * 9.8f);
        }
        update_nuke(&nuke);
        for (t_list *node = buildings_spawner.buildings_list; node != NULL; node = node->next) {
            if (node->data != NULL) {
                t_building *top_building = &((*(t_couple_of_buildings *)node->data).top_building);
                t_building *bottom_building = &((*(t_couple_of_buildings *)node->data).bottom_building);
                update_building(top_building);
                update_building(bottom_building);
            }
        }
        update_buildings_spawner(&buildings_spawner, delta);
        buildings_spawner.buildings_speed += 0.002;
        
        int fisrst_build_param[3];

        // Collider
        SDL_Rect rect_buffer;
        SDL_Rect nuke_rect = {nuke.position.x - nuke.texture.dst_size.x / 2 + 40,
                            nuke.position.y - nuke.texture.dst_size.y / 2 + 20,
                            nuke.texture.dst_size.x - 40, nuke.texture.dst_size.y - 20};
        for (t_list *node = buildings_spawner.buildings_list; node != NULL; node = node->next) {
            if (node->data == NULL) break;
            t_couple_of_buildings couple_of_buildings = *(t_couple_of_buildings *)node->data;

            t_building top_building = couple_of_buildings.top_building;
            t_building bottom_building = couple_of_buildings.bottom_building;
            SDL_Rect top_building_rect = {top_building.position.x - top_building.texture.dst_size.x / 2,
                                        top_building.position.y - top_building.texture.dst_size.y / 2,
                                        top_building.texture.dst_size.x, top_building.texture.dst_size.y};
            SDL_Rect bottom_building_rect = {bottom_building.position.x - bottom_building.texture.dst_size.x / 2,
                                            bottom_building.position.y - bottom_building.texture.dst_size.y / 2,
                                            bottom_building.texture.dst_size.x, bottom_building.texture.dst_size.y};
            if (SDL_IntersectRect(&nuke_rect, &top_building_rect, &rect_buffer)) {
                loose = true;
            } else if (SDL_IntersectRect(&nuke_rect, &bottom_building_rect, &rect_buffer)) {
                loose = true;
            }
            if (is_first_build_setted == false) {
                fisrst_build_param[0] = top_building_rect.x;
                fisrst_build_param[1] = bottom_building_rect.y;
                fisrst_build_param[2] = bottom_building_rect.h;
                is_first_build_setted = true;
            }
        }

        if (is_first_build_setted == true) {
            SDL_Rect score_collider_rect = {fisrst_build_param[0] + nuke_rect.w, fisrst_build_param[1] - (fisrst_build_param[2] / 2) + (nuke_rect.h / 2),
                                            1, nuke_rect.w * 2};
            if (nuke_rect.x + (nuke_rect.w / 2) < score_collider_rect.x - (score_collider_rect.w / 2)
                && SDL_IntersectRect(&nuke_rect, &score_collider_rect, &rect_buffer) 
                && is_score_increased == false) {
                score_count += 1;
                char buffer[10];
                render_int_label(&score_counter_label, score_count, buffer);
                is_score_increased = true;
            }
            if (nuke_rect.x + (nuke_rect.w / 2) > score_collider_rect.x + (score_collider_rect.w / 2)
                && !SDL_IntersectRect(&nuke_rect, &score_collider_rect, &rect_buffer) 
                && is_score_increased == true){
                is_score_increased = false;
            }
            is_first_build_setted = false;
        }


        //Falling under screen
        if (nuke_rect.y + (nuke_rect.h * (-1)) >= WINDOW_HEIGHT) {
            loose = true;
        }
        
        // Render
        //clear_window();
        if (new_game_started) {
            
        }
        SDL_RenderCopy(get_renderer(), sky_texture, NULL, NULL);
        for (t_list *node = buildings_spawner.buildings_list; node != NULL; node = node->next) {
            if (node->data != NULL) {
                t_building *top_building = &((*(t_couple_of_buildings *)node->data).top_building);
                t_building *bottom_building = &((*(t_couple_of_buildings *)node->data).bottom_building);
                render_building(top_building);
                render_building(bottom_building);
            }
        }
        render_nuke(nuke);
        render_label(score_counter_label);
        if (!understood_controls) {
            render_label(tip_label);
        }
        display();

        // FPS limiter
        frame_time = SDL_GetTicks() - frame_start;
        if (MAX_FRAME_DELAY > frame_time) {
            SDL_Delay(MAX_FRAME_DELAY - frame_time);
            delta = (float)MAX_FRAME_DELAY / 1000;
        } else {
            delta = (float)frame_time / 1000;
        }

        if (loose || main_menu_request) {
            if (loose)
                Mix_PlayChannel(-1, bonk_sound, 0);
            Mix_PauseMusic();
            if (score_count > best_score) {
                best_score = score_count;
                write_int_to_file(best_score, PATH_TO_SAVE_FILE);
            }
            SDL_ShowCursor(true);

            if (loose) {
                char buffer1[10];
                char buffer2[10];
                render_int_label(&loose_menu_labels.arr[2], best_score, buffer1);
                render_int_label(&loose_menu_labels.arr[1], score_count, buffer2);
                t_button_action loose_menu_result = show_menu(loose_menu_buttons, &loose_menu_labels, black_color, &centered_rect, true);
                if (loose_menu_result == NEW_GAME) {
                    Mix_PlayMusic(music, -1);
                    new_game_started = true;
                } else if (loose_menu_result == GOTO_MAIN_MENU) {
                    main_menu_request = true;
                }
                loose = false;
            }
            
            nuke.position = START_PLAYER_POS;
            nuke.velocity.x = 0;
            nuke.velocity.y = 0;
            free_buildings(&buildings_spawner);
            score_count = 0;
            buildings_spawner.buildings_speed = START_BUILDINGS_SPEED;
            char buffer[10];
            render_int_label(&score_counter_label, score_count, buffer);
        }
    }
    if (score_count > best_score) {
        write_int_to_file(score_count, PATH_TO_SAVE_FILE);
    }

    // Free everything and exit
    for (int i = 0; i < buildings_textures.size; i++) {
        SDL_DestroyTexture(buildings_textures.arr[i].tex);
    }
    SDL_DestroyTexture(nuke_texture.tex);
    
    free_buildings(&buildings_spawner);

    Mix_FreeMusic(music);
    Mix_FreeChunk(bonk_sound);
    Mix_CloseAudio();

    TTF_CloseFont(ubuntu_bold_24);
    TTF_CloseFont(bungee_spice_regular_40);

    free(loose_menu_labels.arr);
    free(about_menu_labels.arr);
    free(buildings_textures.arr);
    free(main_menu_buttons.arr);
    free(loose_menu_buttons.arr);
    free(escape_menu_buttons.arr);
    free(about_menu_buttons.arr);
    destroy_window_and_renderer();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();


    
    // SDL_Texture *grass_texture = load_texture("resource/images/super_grass.jpg");
    // t_entity platform0 = create_entity(100, 100, grass_texture);

    // SDL_Rect dest;
    // SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);

    // dest.x = (WINDOW_WIDTH - dest.w) / 2;

    // //float y_pos = WINDOW_HEIGHT;

    return 0;
}

