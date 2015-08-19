#include "fitbit.h"
#include "views.h"
#include "controller.h"

void controller_notify_error(const char *error) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "----> controller_notify_error()");
    APP_LOG(APP_LOG_LEVEL_DEBUG, error);

    views_draw_error(error);
}

void controller_notify_bluetooth_state(bool connected) {

}

void controller_notify_battery_state(BatteryChargeState charge_state) {
    
}

void controller_tick(struct tm* tick_time) {
    views_draw_date_time(tick_time);
    fitbit_get_steps();
}

void controller_notify_fitbit_steps(uint16_t steps) {
    views_draw_fitbit_steps(steps);
}

void controller_notify_status(const char* status) {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "----> controller_notify_status()");
    APP_LOG(APP_LOG_LEVEL_DEBUG, status);

    views_draw_status(status);
}
