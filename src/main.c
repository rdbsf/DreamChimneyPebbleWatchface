#include <pebble.h>
#include <stdio.h>
#include <ctype.h>
  
#define KEY_TEMPERATURE 0
#define KEY_CONDITIONS 1
  
static Window *s_main_window;
static TextLayer *s_time_layer;
static TextLayer *s_date_layer;
static TextLayer *s_date_2_layer;
static TextLayer *s_track_title_layer;
static TextLayer *s_track_layer;

static GFont s_time_font;
static GFont s_date_font;
static GFont s_weather_font;

static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

char *upcase(char *str)
{
    char *s = str;

    while (*s)
    {
        *s++ = toupper((int)*s);
    }

    return str;
}

static void update_time(struct tm *tick_time) {
  // Get a tm structure
  //time_t temp = time(NULL); 
  //struct tm *tick_time = localtime(&temp);

  // Create a long-lived buffer
  static char buffer[] = "00:00";
  
  // Write the current hours and minutes into the buffer
  //if(clock_is_24h_style() == true) {
    //Use 2h hour format
  //  strftime(buffer, sizeof("00:00"), "%H:%M", tick_time);
  //} else {
    //Use 12 hour format
    strftime(buffer, sizeof("00:00"), "%I:%M", tick_time);
  // }
  
  // Display this time on the TextLayer
  text_layer_set_text(s_time_layer, buffer);

  
  
}



static void main_window_load(Window *window) {
  //Create GBitmap, then set to created BitmapLayer
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_DC_ES_BMP);
  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));
  
  // Create time TextLayer
  //s_time_layer = text_layer_create(GRect(5, 65, 139, 65));
  s_time_layer = text_layer_create(GRect(10, 70, 100, 99));
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_text(s_time_layer, "00:00");
  
  //Create GFont
  s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_FUTURA_30));
  
  //Apply to TextLayer
  text_layer_set_font(s_time_layer, s_time_font);
  //text_layer_set_text_alignment(s_time_layer, GTextAlignmentRight);

  time_t temp = time(NULL); 
  struct tm *tick_time = localtime(&temp);
  
  
    // Create Date layer
//  s_date_layer = text_layer_create(GRect(5, 89, 139, 89));
  s_date_layer = text_layer_create(GRect(115, 70, 134, 70));
  text_layer_set_background_color(s_date_layer, GColorClear);
  text_layer_set_text_color(s_date_layer, GColorBlack);
  text_layer_set_text(s_date_layer, "Mon");

  static char bufferDate[] = "Mon";
  strftime(bufferDate, sizeof("Mon"), "%a", tick_time);
  //  strftime(bufferDate, sizeof("Mon Feb 04"), "%a %b %d", tick_time);
// convert each lowercase char in the string to uppercase
  upcase(bufferDate);
  text_layer_set_text(s_date_layer, bufferDate);
  text_layer_set_overflow_mode(s_date_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(s_date_layer, GTextAlignmentLeft);

      // Create Date layer
//  s_date_layer = text_layer_create(GRect(5, 89, 139, 89));
  s_date_2_layer = text_layer_create(GRect(100, 85, 134, 85));
  text_layer_set_background_color(s_date_2_layer, GColorClear);
  text_layer_set_text_color(s_date_2_layer, GColorBlack);
  text_layer_set_text(s_date_2_layer, "Mon Feb 04");

  static char bufferDate2[] = "Feb 10";
  strftime(bufferDate2, sizeof("Feb 10"), "%b%d", tick_time);
  //upcase(bufferDate2);
  text_layer_set_text(s_date_2_layer, bufferDate2);
  text_layer_set_overflow_mode(s_date_2_layer, GTextOverflowModeWordWrap);
  text_layer_set_text_alignment(s_date_2_layer, GTextAlignmentLeft);

  
  
  
  
    //Create GFont
  s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_14));
  
    //Apply to TextLayer
  text_layer_set_font(s_date_layer, s_date_font);
    text_layer_set_font(s_date_2_layer, s_date_font);
  //text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);

  
  
  // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_time_layer));
  
    // Add it as a child layer to the Window's root layer
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_layer));
    layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_date_2_layer));


  // Create Track of the Day title layer
  s_track_title_layer = text_layer_create(GRect(0, 110, 144, 110));
  text_layer_set_background_color(s_track_title_layer, GColorClear);
  text_layer_set_text_color(s_track_title_layer, GColorWhite);
  text_layer_set_text_alignment(s_track_title_layer, GTextAlignmentCenter);
  text_layer_set_text(s_track_title_layer, "TRACK OF THE DAY:");
  
  // Create second custom font, apply it and add to Window
  s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_12));
  text_layer_set_font(s_track_title_layer, s_weather_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_track_title_layer));
  
  // Create TOTD Layer
  s_track_layer = text_layer_create(GRect(0, 126, 144, 126));
  text_layer_set_background_color(s_track_layer, GColorClear);
  text_layer_set_text_color(s_track_layer, GColorWhite);
  text_layer_set_text_alignment(s_track_layer, GTextAlignmentCenter);
  text_layer_set_text(s_track_layer, "Loading track...");
  
  // Create second custom font, apply it and add to Window
  //s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PERFECT_DOS_20));
  s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_ROBOTO_12));
  text_layer_set_font(s_track_layer, s_weather_font);
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(s_track_layer));
  
  
  // Make sure the time is displayed from the start
  update_time(tick_time);
}

static void main_window_unload(Window *window) {
  //Unload GFont
  fonts_unload_custom_font(s_time_font);
  
  //Destroy GBitmap
  gbitmap_destroy(s_background_bitmap);

  //Destroy BitmapLayer
  bitmap_layer_destroy(s_background_layer);
  
  // Destroy TextLayer
  text_layer_destroy(s_time_layer);
  text_layer_destroy(s_date_layer); 
  text_layer_destroy(s_date_2_layer); 
  
  // Destroy weather elements
  text_layer_destroy(s_track_layer);
  text_layer_destroy(s_track_title_layer);
  fonts_unload_custom_font(s_weather_font);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time(tick_time);
  
  // Get weather update every 30 minutes
  if(tick_time->tm_min % 30 == 0) {
    // Begin dictionary
    DictionaryIterator *iter;
    app_message_outbox_begin(&iter);

    // Add a key-value pair
    dict_write_uint8(iter, 0, 0);

    // Send the message!
    app_message_outbox_send();
  }
}

static void inbox_received_callback(DictionaryIterator *iterator, void *context) {
  // Store incoming information
  static char temperature_buffer[64];
  static char conditions_buffer[64];
  static char weather_layer_buffer[128];
  
  // Read first item
  Tuple *t = dict_read_first(iterator);

  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case KEY_TEMPERATURE:
      snprintf(temperature_buffer, sizeof(temperature_buffer), "%s", t->value->cstring);
      break;
    case KEY_CONDITIONS:
      snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", t->value->cstring);
      break;
    default:
      APP_LOG(APP_LOG_LEVEL_ERROR, "Key %d not recognized!", (int)t->key);
      break;
    }

    // Look for next item
    t = dict_read_next(iterator);
  }
  
  // Assemble full string and display
  snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "'%s' by %s", conditions_buffer, temperature_buffer);
  text_layer_set_text(s_track_layer, weather_layer_buffer);
}

static void inbox_dropped_callback(AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

static void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
  APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

static void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}
  
static void init() {
  // Create main Window element and assign to pointer
  s_main_window = window_create();

  // Set handlers to manage the elements inside the Window
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });

  // Show the Window on the watch, with animated=true
  window_stack_push(s_main_window, true);
  
  // Register with TickTimerService
  tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
  
  // Register callbacks
  app_message_register_inbox_received(inbox_received_callback);
  app_message_register_inbox_dropped(inbox_dropped_callback);
  app_message_register_outbox_failed(outbox_failed_callback);
  app_message_register_outbox_sent(outbox_sent_callback);
  
  // Open AppMessage
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
}

static void deinit() {
  // Destroy Window
  window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
