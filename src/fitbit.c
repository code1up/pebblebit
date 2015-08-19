#include <pebble.h>
#include "pebblebit.h"
#include "fitbit.h"

void fitbit_get_steps() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> fitbit_get_steps()");

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
