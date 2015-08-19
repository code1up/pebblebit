#pragma once

#include <pebble.h>

void views_init();
void views_deinit();

void views_draw_bluetooth_icon(bool connected);
void views_draw_battery_icon(BatteryChargeState charge_state);

void views_draw_status(const char* status);
void views_draw_error(const char* error);

void views_draw_date_time(struct tm* tick_time);
void views_draw_fitbit_steps(uint16_t steps);
