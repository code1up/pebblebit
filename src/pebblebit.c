#include <pebble.h>

#include "pebblebit.h"
#include "views.h"
#include "handlers.h"
#include "messages.h"

static void app_init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> app_init()");

  views_init();
  messages_init();
  handlers_init();
}

static void app_deinit() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> app_deinit()");

  handlers_deinit();
  messages_deinit();
  views_deinit();
}

int main() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> main()");

  app_init();
  app_event_loop();
  app_deinit();
}
