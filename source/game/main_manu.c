#include "core.h"

extern struct level_c_f load_level_1();

static struct main_menu {
  struct sprite_f title;
  struct sprite_f credit;
  struct sprite_f background;
  struct buttom_f btn_start_game;
  struct buttom_f btn_fullscreen;
  struct buttom_f btn_quit_game;
} * level;

// Declaration
static void level_start();
static void level_update(float delta_time);
static void level_draw(float delta_time);
static void level_end();

// Buttom
void buttom_on_hovered(struct buttom_f *buttom);
void buttom_on_unhovered(struct buttom_f *buttom);
void buttom_on_start_game(struct buttom_f *buttom);
void buttom_on_set_fullscreen(struct buttom_f *buttom);
void buttom_on_quit_game(struct buttom_f *buttom);

struct level_c_f load_main_menu() {
  struct level_c_f lv = {0};
  lv.on_level_start = &level_start;
  lv.on_level_update = &level_update;
  lv.on_level_draw = &level_draw;
  lv.on_level_end = &level_end;
  level = (struct main_menu *)get_memory_f(sizeof(struct main_menu));
  return lv;
}

void level_start() {
  set_show_cursor_p(true);

  struct rect_f bg_rect = {SCREEN_X_CENTER, SCREEN_Y_CENTER, SCREEN_RIGHT / 2.f, SCREEN_TOP / 2.f};
  level->background = create_sprite_g(FIND_ASSET("texture/main_menu/background.bmp"), bg_rect);
  level->background.position.z = -1;

  struct rect_f credit_rect = {SCREEN_X_CENTER, SCREEN_BOTTON + 7, SCREEN_RIGHT / 2 - 5, 2.5};
  level->credit = create_sprite_g(FIND_ASSET("texture/main_menu/credit.bmp"), credit_rect);

  struct rect_f title_rect = {SCREEN_X_CENTER, SCREEN_TOP - 15, 30, 10};
  level->title = create_sprite_g(FIND_ASSET("texture/main_menu/title.bmp"), title_rect);

  struct rect_f start_game_rect = {SCREEN_X_CENTER, SCREEN_Y_CENTER, 5, 2};
  level->btn_start_game.icon = create_sprite_g(FIND_ASSET("texture/main_menu/start_game.bmp"), start_game_rect);
  level->btn_start_game.on_hovered = &buttom_on_hovered;
  level->btn_start_game.on_unhovered = &buttom_on_unhovered;
  level->btn_start_game.on_pressed = &buttom_on_start_game;

  struct rect_f fullscreen_rect = {SCREEN_X_CENTER, SCREEN_Y_CENTER - 6, 10, 2};
  level->btn_fullscreen = create_buttom_f(fullscreen_rect);
  level->btn_fullscreen.icon = create_sprite_g(FIND_ASSET("texture/main_menu/fullscreen.bmp"), fullscreen_rect);
  level->btn_fullscreen.on_hovered = &buttom_on_hovered;
  level->btn_fullscreen.on_unhovered = &buttom_on_unhovered;
  level->btn_fullscreen.on_pressed = &buttom_on_set_fullscreen;

  struct rect_f quit_game_rect = {SCREEN_X_CENTER, SCREEN_Y_CENTER - 12, 10, 1.5};
  level->btn_quit_game = create_buttom_f(quit_game_rect);
  level->btn_quit_game.icon = create_sprite_g(FIND_ASSET("texture/main_menu/quit_game.bmp"), quit_game_rect);
  level->btn_quit_game.on_hovered = &buttom_on_hovered;
  level->btn_quit_game.on_unhovered = &buttom_on_unhovered;
  level->btn_quit_game.on_pressed = &buttom_on_quit_game;
}

void level_update(float delta_time) {
  if (is_key_pressed_f(KEY_ESCAPE)) {
    quit_game_p();
  }
  if (is_key_pressed_f(KEY_TAB)) {
    set_window_fullscreen_p();
  }

  update_buttom_f(&level->btn_start_game);
  update_buttom_f(&level->btn_fullscreen);
  update_buttom_f(&level->btn_quit_game);
}

void level_draw(float delta_time) {
  draw_sprite_g(level->background, WHITE);
  draw_sprite_g(level->title, WHITE);
  draw_sprite_g(level->credit, WHITE);
  draw_sprite_g(level->btn_start_game.icon, WHITE);
  draw_sprite_g(level->btn_fullscreen.icon, WHITE);
  draw_sprite_g(level->btn_quit_game.icon, WHITE);
}

void level_end() {
  destroy_sprite_g(level->title);
  destroy_sprite_g(level->credit);
  destroy_sprite_g(level->background);
  destroy_sprite_g(level->btn_start_game.icon);
  destroy_sprite_g(level->btn_fullscreen.icon);
  destroy_sprite_g(level->btn_quit_game.icon);
  free_memory_f(level);
  G_LOG(LOG_WARNING, "Clean Main Menu");
}

void buttom_on_hovered(struct buttom_f *buttom) {
  buttom->icon.scale = vector3_add_scale(buttom->icon.scale, 1);
}

void buttom_on_unhovered(struct buttom_f *buttom) {
  buttom->icon.scale = vector3_sub_scale(buttom->icon.scale, 1);
}

void buttom_on_start_game(struct buttom_f *buttom) {
  open_level_c_f(load_level_1());
}

void buttom_on_set_fullscreen(struct buttom_f *buttom) {
  set_window_fullscreen_p();
}

void buttom_on_quit_game(struct buttom_f *buttom) {
  quit_game_p();
}
