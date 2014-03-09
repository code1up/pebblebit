#include "pebblebit.h"
#include "controller.h"
#include "messages.h"

const int IN_BUF_SIZE = 64;
const int OUT_BUF_SIZE = 64;

void in_received_handler(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> in_received_handler()");

  Tuple *steps_tuple = dict_find(iter, APP_KEY_STEPS);

  if (steps_tuple) {
    uint16_t steps = steps_tuple->value->int16;

    static char steps_text[] = "000000";

    snprintf(steps_text, sizeof(steps_text), "%d", steps);

    /// text_layer_set_text(battery_layer, steps_text);

    // TODO: vibes_short_pulse();

  } else {
    /// text_layer_set_text(battery_layer, "REC");

  }
}

void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> in_dropped_handler()");

text_layer_set_text(battery_layer, "IN");
}

void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "out_failed_handler()");

  /// text_layer_set_text(battery_layer, "OUT");
}

void messages_init() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> messages_init()");

  app_message_register_inbox_received(in_received_handler);
  app_message_register_inbox_dropped(in_dropped_handler);
  app_message_register_outbox_failed(out_failed_handler);

  app_message_open(IN_BUF_SIZE, OUT_BUF_SIZE);
}

void messages_deinit() {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> messages_deinit()");

  app_message_deregister_callbacks();
}
