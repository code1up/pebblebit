#pragma once

#include <pebble.h>
#include "pebblebit.h"

void controller_notify_error(const char *error);
void controller_notify_bluetooth_state(bool connected);
void controller_notify_battery_state(BatteryChargeState charge_state);
void controller_tick(struct tm* tick_time);
void controller_notify_fitbit_steps(uint16_t steps);
void controller_notify_status(const char* status);
