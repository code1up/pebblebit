#include "handlers.h"
#include "ui.h"

void bluetooth_connection_handler(bool connected) {
  ui_draw_bluetooth_icon(connected);
}

void battery_state_handler(BatteryChargeState charge_state) {
  ui_draw_battery_charge_icon(charge_state);
}

void tick_timer_handler(struct tm* tick_time, TimeUnits units_changed) {
  static char time_text[] = "00:00"; // Needs to be static because it's used by the system later.

  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> tick_timer_handler()");

  strftime(time_text, sizeof(time_text), "%R", tick_time);
  /// text_layer_set_text(time_layer, time_text);

  // TODO: Update battery and Bluetooth states every minute.
  // battery_state_handler(battery_state_service_peek());
  // bluetooth_connection_handler(bluetooth_connection_service_peek());

  /// fetch_steps();
}

void handlers_init() {
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  tick_timer_handler(current_time, MINUTE_UNIT);

  tick_timer_service_subscribe(MINUTE_UNIT, &tick_timer_handler);
  battery_state_service_subscribe(&battery_state_handler);
  bluetooth_connection_service_subscribe(&bluetooth_connection_handler);    
}

void handlers_deinit() {
  tick_timer_service_unsubscribe();
  battery_state_service_unsubscribe();
  bluetooth_connection_service_unsubscribe();
}