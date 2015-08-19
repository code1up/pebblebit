#include "views.h"

#define WATCH_WIDTH 144
#define WATCH_HEIGHT 168

#define DATE_TIME_LAYER_HEIGHT 112
#define DATE_TIME_LAYER_LEFT 8
#define DATE_TIME_LAYER_WIDTH (WATCH_WIDTH - (DATE_TIME_LAYER_LEFT * 2))

#define STEPS_LAYER_LEFT 16
#define STEPS_LAYER_HEIGHT (WATCH_HEIGHT - DATE_TIME_LAYER_HEIGHT - 8)
#define STEPS_LAYER_WIDTH (WATCH_WIDTH - (STEPS_LAYER_LEFT * 2))

Window *window;

// Date and time layers.
Layer *date_time_layer;
TextLayer *date_text_layer;
TextLayer *time_text_layer;
Layer *date_time_separator_layer;

// Fitbit layers.
Layer *fitbit_layer;
TextLayer *fitbit_steps_text_layer;

void separator_layer_update_callback(Layer *layer, GContext* ctx) {
  graphics_context_set_fill_color(ctx, GColorWhite);
  graphics_fill_rect(ctx, layer_get_bounds(layer), 0, GCornerNone);
}

void views_init_date_text_layer(Layer *parent_layer) {
  static const int16_t LEFT = 0;
  static const int16_t TOP = 26;
  static const int16_t WIDTH = DATE_TIME_LAYER_WIDTH;
  static const int16_t HEIGHT = 32;

  GFont font = fonts_load_custom_font(
    resource_get_handle(RESOURCE_ID_FONT_DATE_21));

  date_text_layer = text_layer_create(GRect(LEFT, TOP, WIDTH, HEIGHT));

  text_layer_set_text_color(date_text_layer, GColorWhite);
  text_layer_set_background_color(date_text_layer, GColorClear);
  text_layer_set_font(date_text_layer, font);

  layer_add_child(parent_layer, text_layer_get_layer(date_text_layer));

  text_layer_set_text(date_text_layer, "March 9");
}

void views_init_date_time_separator_layer(Layer *parent_layer) {
  static const int16_t LEFT = 0;
  static const int16_t TOP = 52;
  static const int16_t WIDTH = DATE_TIME_LAYER_WIDTH;
  static const int16_t HEIGHT = 2;

  date_time_separator_layer = layer_create(GRect(LEFT, TOP, WIDTH, HEIGHT));

  layer_set_update_proc(date_time_separator_layer, separator_layer_update_callback);
  layer_add_child(parent_layer, date_time_separator_layer);
}

void views_init_time_text_layer(Layer *parent_layer) {
  static const int16_t LEFT = 0;
  static const int16_t TOP = 48;
  static const int16_t WIDTH = DATE_TIME_LAYER_WIDTH;
  static const int16_t HEIGHT = DATE_TIME_LAYER_HEIGHT - TOP;

  time_text_layer = text_layer_create(GRect(LEFT, TOP, WIDTH, HEIGHT));

  GFont font = fonts_load_custom_font(
    resource_get_handle(RESOURCE_ID_FONT_TIME_49));

  text_layer_set_text_color(time_text_layer, GColorWhite);
  text_layer_set_text_alignment(time_text_layer, GTextAlignmentCenter);
  text_layer_set_background_color(time_text_layer, GColorClear);

  text_layer_set_font(time_text_layer, font);

  layer_add_child(parent_layer, text_layer_get_layer(time_text_layer));
}

void views_init_date_time_layer(Layer *root_layer) {
  static const int16_t LEFT = DATE_TIME_LAYER_LEFT;
  static const int16_t TOP = 0;
  static const int16_t WIDTH = WATCH_WIDTH;
  static const int16_t HEIGHT = DATE_TIME_LAYER_HEIGHT;

  date_time_layer = layer_create(GRect(LEFT, TOP, WIDTH, HEIGHT));

  views_init_date_text_layer(date_time_layer);
  views_init_date_time_separator_layer(date_time_layer);
  views_init_time_text_layer(date_time_layer);

  layer_add_child(root_layer, date_time_layer);
}

void views_init_fitbit_steps_text_layer(Layer *parent_layer) {
  static const int16_t LEFT = 0;
  static const int16_t TOP = 8;
  static const int16_t WIDTH = STEPS_LAYER_WIDTH;
  static const int16_t HEIGHT = STEPS_LAYER_HEIGHT;

  fitbit_steps_text_layer = text_layer_create(GRect(LEFT, TOP, WIDTH, HEIGHT));

  GFont font = fonts_load_custom_font(
    resource_get_handle(RESOURCE_ID_FONT_STEPS_32));

  text_layer_set_text_color(fitbit_steps_text_layer, GColorBlack);
  text_layer_set_text_alignment(fitbit_steps_text_layer, GTextAlignmentCenter);
  text_layer_set_background_color(fitbit_steps_text_layer, GColorWhite);

  text_layer_set_font(fitbit_steps_text_layer, font);

  layer_add_child(parent_layer, text_layer_get_layer(fitbit_steps_text_layer));

  text_layer_set_text(fitbit_steps_text_layer, "...");
}

void views_init_fitbit_layer(Layer *root_layer) {
  static const int16_t LEFT = STEPS_LAYER_LEFT;
  static const int16_t TOP = DATE_TIME_LAYER_HEIGHT - 8;
  static const int16_t WIDTH = STEPS_LAYER_WIDTH;
  static const int16_t HEIGHT = STEPS_LAYER_HEIGHT;

  fitbit_layer = layer_create(GRect(LEFT, TOP, WIDTH, HEIGHT));

  views_init_fitbit_steps_text_layer(fitbit_layer);

  layer_add_child(root_layer, fitbit_layer);
}

void views_init() {  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> views_init()");

  // Create root window.
  window = window_create();

  window_stack_push(window, true);
  window_set_background_color(window, GColorBlack);

  // Get root layer.
  Layer *root_layer = window_get_root_layer(window);

  // Create time and date layers.
  views_init_date_time_layer(root_layer);

  // Create Fitbit layers.
  views_init_fitbit_layer(root_layer);
}

void views_deinit() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> views_deinit()");

  // Create time and date layers.
  text_layer_destroy(date_text_layer);
  layer_destroy(date_time_separator_layer);
  text_layer_destroy(time_text_layer);
  layer_destroy(date_time_layer);

  // Create Fitbit layers.
  layer_destroy(fitbit_layer);
  text_layer_destroy(fitbit_steps_text_layer);

  // Destroy root layer and window.
  window_destroy(window); 
}

void views_draw_bluetooth_icon(bool connected) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> views_bluetooth_icon_draw()");
}

void views_drawbattery_icon(BatteryChargeState charge_state) {   
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> views_battery_icon_draw()");
}

void views_draw_date_time(struct tm* tick_time) {
   // CRITICAL: must be static because it's used by the system later.
  static char time_text[] = "00:00";
  static char date_text[] = "Xxxxxxxxx 00";

  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> views_update_date_time()");

  // Draw date.
  strftime(date_text, sizeof(date_text), "%B %e", tick_time);
  text_layer_set_text(date_text_layer, date_text);

  // Draw time.
  strftime(time_text, sizeof(time_text), "%R", tick_time);

  text_layer_set_text(time_text_layer, time_text);
}

void views_draw_fitbit_steps(uint16_t steps) {
  static char steps_text[] = "000000";

  snprintf(steps_text, sizeof(steps_text), "%d", steps);

  text_layer_set_text(fitbit_steps_text_layer, steps_text);
}

void views_draw_status(const char* status) {
  text_layer_set_text(fitbit_steps_text_layer, status);
}

void views_draw_error(const char* error) {
  text_layer_set_text(fitbit_steps_text_layer, error);
}
