#include "ui.h"

Window *window;

TextLayer *time_layer; 
TextLayer *battery_layer;
TextLayer *bluetooth_layer;

GFont arcade_font_24;

BitmapLayer *overlay_layer;
GBitmap *overlay_bitmap;

void ui_init() {  
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> app_ui_init()");

  // Create root window.
  window = window_create();

  window_stack_push(window, true);
  window_set_background_color(window, GColorWhite);

  // Get root layer.
  Layer *root_layer = window_get_root_layer(window);
  GRect frame = layer_get_frame(root_layer);

  // Load custom fonts.
  ResHandle arcade_font_24_handle = resource_get_handle(RESOURCE_ID_FONT_ARCADE_N_24);

  arcade_font_24 = fonts_load_custom_font(arcade_font_24_handle);

  // Create time layer.
  time_layer = text_layer_create(GRect(0, 4, frame.size.w /* width */, 80 /* height */));

  text_layer_set_text_color(time_layer, GColorBlack);
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  text_layer_set_font(time_layer, arcade_font_24);

  // Create connection layer.
  bluetooth_layer = text_layer_create(GRect(0, 90, /* width */ frame.size.w, 34 /* height */));

  text_layer_set_text_color(bluetooth_layer, GColorBlack);
  text_layer_set_background_color(bluetooth_layer, GColorClear);
  text_layer_set_text_alignment(bluetooth_layer, GTextAlignmentCenter);
  text_layer_set_font(bluetooth_layer, arcade_font_24);

  // Create battery layer.
  battery_layer = text_layer_create(GRect(0, 120, /* width */ frame.size.w, 34 /* height */));

  text_layer_set_text_color(battery_layer, GColorBlack);
  text_layer_set_background_color(battery_layer, GColorClear);
  text_layer_set_text_alignment(battery_layer, GTextAlignmentCenter);
  text_layer_set_text(battery_layer, "?");
  text_layer_set_font(battery_layer, arcade_font_24);

  // Create overlay layer.
  overlay_layer = bitmap_layer_create(GRect(0, 0, frame.size.w, frame.size.h));

  layer_add_child(root_layer, text_layer_get_layer(time_layer));
  layer_add_child(root_layer, text_layer_get_layer(bluetooth_layer));
  layer_add_child(root_layer, text_layer_get_layer(battery_layer));
  layer_add_child(root_layer, bitmap_layer_get_layer(overlay_layer));
}

void ui_deinit() {
  // Destroy text layers.
  text_layer_destroy(time_layer);
  text_layer_destroy(bluetooth_layer);
  text_layer_destroy(battery_layer);

  // Destroy bitmap resources.
  bitmap_layer_destroy(overlay_layer);
  gbitmap_destroy(overlay_bitmap);

  // Unload custom fonts.
  fonts_unload_custom_font(arcade_font_24);

  // Destroy root window.
  window_destroy(window);    
}

void ui_draw_bluetooth_icon(bool connected) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> draw_bluetooth_icon()");

  if (overlay_bitmap) {
    gbitmap_destroy(overlay_bitmap);
  }

  overlay_bitmap = gbitmap_create_with_resource(RESOURCE_ID_BATTERY_75);
  bitmap_layer_set_bitmap(overlay_layer, overlay_bitmap);
}

void ui_draw_battery_charge_icon(BatteryChargeState charge_state) {   
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> draw_battery_charge_icon()");

  static char battery_text[] = "100%";

  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> battery_state_handler()");

  if (charge_state.is_charging) {
    snprintf(battery_text, sizeof(battery_text), ">>>>");

  } else {
    snprintf(battery_text, sizeof(battery_text), "%d%%", charge_state.charge_percent);

  }

  // text_layer_set_text(battery_layer, battery_text);
}
