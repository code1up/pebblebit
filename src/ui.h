#pragma once

#include <pebble.h>

void ui_init();
void ui_deinit();

void ui_draw_bluetooth_icon(bool connected);
void ui_draw_battery_charge_icon(BatteryChargeState charge_state);
