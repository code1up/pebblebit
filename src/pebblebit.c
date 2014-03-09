// RESOLUTION: 144w x 168h

// TODO: underscores.

// TODO: messaging / fitbit.

#include <pebble.h>

#include "pebblebit.h"
#include "ui.h"
#include "handlers.h"
#include "messages.h"

void fetch_steps() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> fetch_steps()");

  Tuplet steps_tuple = TupletInteger(APP_KEY_STEPS, 1);
  DictionaryIterator *i;

  app_message_outbox_begin(&i);

  if (i == NULL) {
    return;
  }

  dict_write_tuplet(i, &steps_tuple);
  dict_write_end(i);

  app_message_outbox_send();
}

static void app_init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> app_init()");

  ui_init();
  messages_init();
  handlers_init();
}

static void app_deinit() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> app_deinit()");

  handlers_deinit();
  messages_deinit();
  ui_deinit();
}

int main() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> main()");

  app_init();
  app_event_loop();
  app_deinit();
}
