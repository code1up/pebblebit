#include "controller.h"
#include "handlers.h"

void bluetooth_connection_handler(bool connected) {
  controller_notify_bluetooth_state(connected);
}

void battery_state_handler(BatteryChargeState charge_state) {
  controller_notify_battery_state(charge_state);
}

void tick_timer_handler(struct tm* tick_time, TimeUnits units_changed) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> tick_timer_handler()");

  controller_tick(tick_time);
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
