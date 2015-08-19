#include "controller.h"
#include "messages.h"

const int IN_BUF_SIZE = 256;
const int OUT_BUF_SIZE = 65;

void in_received_fitbit_steps_handler(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> in_received_fitbit_steps_handler()");

  Tuple *tuple = dict_find(iter, APP_KEY_STEPS);

  if (tuple) {
    uint16_t steps = tuple->value->int16;

    controller_notify_fitbit_steps(steps);
  }
}

void in_received_status_handler(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> in_received_status_handler()");

  Tuple *tuple = dict_find(iter, APP_KEY_STATUS);

  if (tuple) {
    const char* status = tuple->value->cstring;

    APP_LOG(APP_LOG_LEVEL_DEBUG, "----> got status");
    APP_LOG(APP_LOG_LEVEL_DEBUG, status);

    controller_notify_status(status);
  }
}

void in_received_error_handler(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> in_received_error_handler()");

  Tuple *tuple = dict_find(iter, APP_KEY_ERROR);

  if (tuple) {
    const char* error = tuple->value->cstring;

    APP_LOG(APP_LOG_LEVEL_DEBUG, "----> got error");
    APP_LOG(APP_LOG_LEVEL_DEBUG, error);

    controller_notify_error(error);
  } else {
    APP_LOG(APP_LOG_LEVEL_DEBUG, "----> OK");    
  }
}

void in_received_handler(DictionaryIterator *iter, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> in_received_handler()");

  in_received_fitbit_steps_handler(iter, context);
  in_received_status_handler(iter, context);
  in_received_error_handler(iter, context);
}

void in_dropped_handler(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "----> in_dropped_handler()");

  // TODO: controller_notify_error("EIN");
}

void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "out_failed_handler()");

  controller_notify_error("EOUT");
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
