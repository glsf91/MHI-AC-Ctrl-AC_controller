
// LVGL
// https://github.com/lvgl/lvgl
#include <lvgl.h>

#include "wt32setup.h"
#include "ui.h"
#include <WiFi.h>
#include <PubSubClient.h>       // https://github.com/knolleary/pubsubclient

/*Change to your screen resolution*/
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 10];

#define WIFI_SSID "<SSID>"
#define WIFI_PASSWORD "<password>"

// Copy values from mhi-ac-ctrl support.h
#define HOSTNAME "MHI-AC-Ctrl"            // hostname of MHI-AC-Ctrl controller
#define MQTT_SERVER "<ip MQTTserver>"                 // broker name or IP address of the broker
#define MQTT_PORT 1883                              // port number used by the broker
#define MQTT_USER ""                                // if authentication is not used, leave it empty
#define MQTT_PASSWORD ""                            // if authentication is not used, leave it empty
#define MQTT_PREFIX HOSTNAME "/"                    // basic prefix used for publishing AC data (e.g. for status),
#define MQTT_SET_PREFIX MQTT_PREFIX "set/"          // prefix for subscribing set commands, must end with a "/"
#define MQTT_OP_PREFIX MQTT_PREFIX "OpData/"        // prefix for publishing operating data, must end with a "/"
#define ENHANCED_RESOLUTION true                    // when using Tsetpoint with x.5 degrees, airco will use (x+1).0 setpoint
                                                    // uncomment this to compensatie (offset) Troom for this.

// Copy values from mhi-ac-ctrl mhi-ac-ctrl.h
#define TOPIC_TROOM "Troom"
#define TOPIC_TSETPOINT "Tsetpoint"
#define TOPIC_POWER "Power"
#define TOPIC_MODE "Mode"
#define TOPIC_FAN "Fan"
#define TOPIC_DEFROST "DEFROST"
#define TOPIC_VANES "Vanes"
#define TOPIC_VANESLR "VanesLR"
#define TOPIC_IU_FANSPEED "IU-FANSPEED"
#define TOPIC_OUTDOOR "OUTDOOR"
#define TOPIC_3DAUTO "3Dauto"
#define TOPIC_CT "CT"
#define TOPIC_COMP "COMP"
#define TOPIC_KWH "KWH"
#define TOPIC_REQUEST_RESET "reset"

// Copy values from mhi-ac-ctrl mhi-ac-ctrl.h
#define PAYLOAD_POWER_ON "On"
#define PAYLOAD_POWER_OFF "Off"
#define PAYLOAD_MODE_AUTO "Auto"
#define PAYLOAD_MODE_STOP "Stop"
#define PAYLOAD_MODE_DRY "Dry"
#define PAYLOAD_MODE_COOL "Cool"
#define PAYLOAD_MODE_FAN "Fan"
#define PAYLOAD_MODE_HEAT "Heat"
#define PAYLOAD_FAN_AUTO "Auto"
#define PAYLOAD_OP_DEFROST_ON "On"
#define PAYLOAD_OP_DEFROST_OFF "Off"
#define PAYLOAD_VANES_UNKNOWN "?"
#define PAYLOAD_VANES_SWING "Swing"
#define PAYLOAD_VANESLR_SWING "Swing"
#define PAYLOAD_3DAUTO_ON "On"
#define PAYLOAD_3DAUTO_OFF "Off"
#define PAYLOAD_REQUEST_RESET "reset"


// custom values
#define TOPIC_AUTO_CONTROL_EXTRAS "AutoControl"
#define PAYLOAD_AUTO_CONTROL_ON "On"
#define PAYLOAD_AUTO_CONTROL_OFF "Off"
#define CLIENTNAME "AC-controller"                  // Name of display controller
#define MQTT_PREFIX_CLIENT CLIENTNAME "/"           // basic prefix used for storing settings display
#define TOPIC_BRIGHTNESS "brightness"
#define TOPIC_SNOOZE "snooze"
#define PAYLOAD_SNOOZE_ON "On"
#define PAYLOAD_SNOOZE_OFF "Off"

#define VOLTAGE 230                                 // voltage to use to calculate Wattage
#define SNOOZE_TIME_SEC 120                         // Time in sec when display will snooze when snooze is on

#define WIFI_CONNECT_TIMEOUT 2
#define WIFI_CONNECT_ONGOING 1
#define WIFI_CONNECT_OK 0

#define MQTT_NOT_CONNECTED 2
#define MQTT_RECONNECTED 1
#define MQTT_CONNECT_OK 0


static LGFX tft;

lv_chart_series_t* ui_ChartCurrentTemp_series_1;    // for chart
lv_chart_series_t* ui_ChartCompressor_series_1;     // for chart
lv_chart_series_t* ui_ChartWatt_series_1;           // for chart
lv_chart_series_t* ui_ChartFanIU_series_1;          // for chart

float CurrentTemperature =0.0;
int PowerUsage = 0;
float CompressorHz = 0.0;
int FanIU = 0;
int Brightness = 140;
int Snooze = 0;
int ScreenSnoozed = false;
unsigned long snooze_Millis = millis();
float offsetTroom = 0.0;

WiFiClient espClient;
PubSubClient MQTTclient(espClient);

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft.startWrite();
  tft.setAddrWindow(area->x1, area->y1, w, h);
  tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  tft.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data) {

  uint16_t x, y;
  if (tft.getTouch(&x, &y)) {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;

  } else {
    data->state = LV_INDEV_STATE_REL;
  }
}

// Connect to MQTT server and sunscribe if not connected. Otherwise process MQTT loop
int MQTTreconnect() {
  char strtmp[50];
  static int reconnect_trials=0;
  //Serial.printf("MQTTreconnect(): (MQTTclient.state=%i), WiFi.status()=%i networksFound=%i ...\n", MQTTclient.state(), WiFi.status(), networksFound);
  if(!MQTTclient.connected()) {
    Serial.printf("MQTTreconnect(): Attempting MQTT connection (MQTTclient.state=%i), WiFi.status()=%i ...\n", MQTTclient.state(), WiFi.status());  
    if(reconnect_trials++>9){                                                                                                                       
      Serial.printf("MQTTreconnect(): reconnect_trials=%i\n", reconnect_trials);
      reconnect_trials=0;
    }

    if (MQTTclient.connect(CLIENTNAME, MQTT_USER, MQTT_PASSWORD )) {
      Serial.println(F(" connected"));
      Serial.printf("MQTTclient.connected=%i\n", MQTTclient.connected());
      reconnect_trials=0;

      MQTTclient.subscribe(MQTT_PREFIX "#" );         // subscribe mhi-ac-ctrl controller 
      MQTTclient.subscribe(MQTT_PREFIX_CLIENT "#" );  // subscribe display controller
      return MQTT_RECONNECTED;
    }
    else {
      Serial.print(F(" reconnect failed, reason "));
      itoa(MQTTclient.state(), strtmp, 10);
      Serial.print(strtmp);
      Serial.print(", WiFi status: ");
      Serial.println(WiFi.status());
      return MQTT_NOT_CONNECTED;
    }
  }
  MQTTclient.loop();
  return MQTT_CONNECTED;
}

void updateCurrentTemperature() {
    int i = CurrentTemperature * 100;
    lv_label_set_text_fmt(ui_CurrentTempCelsius, "%d,%d", i / 100, i % 100);
    
    if (CurrentTemperature < 18.0 ){
      lv_img_set_angle(ui_CurrentTempNeedle, -1300);
      return;
    }
    if (CurrentTemperature > 30.0 ){
      lv_img_set_angle(ui_CurrentTempNeedle, 1300);
      return;
    }
    
    int angle = (CurrentTemperature - 24.0) * 200.0;
    Serial.printf("Troom topic: Angle: %i\n", angle);     
    lv_img_set_angle(ui_CurrentTempNeedle,angle);
}

// Process MQTT sunscribed messages
void MQTT_subscribe_callback(const char* topic, byte* payload, unsigned int length) {
  static int firstTimeSetpoint = true;

  payload[length] = 0;  // we need a string
  Serial.printf_P(PSTR("MQTT_subscribe_callback, topic=%s payload=%s payload_length=%i\n"), topic, (char*)payload, length);
  if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_TROOM)) == 0) {
    float f=atof((char*)payload);
#ifdef ENHANCED_RESOLUTION
    f = f - offsetTroom;
#endif    
    CurrentTemperature = f;
    updateCurrentTemperature();    

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_TSETPOINT)) == 0) {
    //int f=atof((char*)payload) + 0.5;
    int value=atof((char*)payload) * 10;
    lv_label_set_text_fmt(ui_SetpointCelsius, "%d,%d", value / 10, value %10);
    lv_arc_set_value(ui_SetpointArc, (value*2)/10 );
#ifdef ENHANCED_RESOLUTION
    float f = atof((char*)payload);
    offsetTroom = round(f) - f;  // Calculate offset when setpoint is changed
    Serial.printf("Tsetpoint topic: offsetTroom: %f\n", offsetTroom);    
    if (firstTimeSetpoint) {
      CurrentTemperature = CurrentTemperature - offsetTroom;
      updateCurrentTemperature();
      firstTimeSetpoint = false;
    }
#endif

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_POWER)) == 0) {

    if (strcmp_P((char*)payload, PSTR(PAYLOAD_POWER_ON)) == 0) {
      lv_obj_add_state(ui_AcSwitchOnOff, LV_STATE_CHECKED);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_POWER_OFF)) == 0) {
      lv_obj_clear_state(ui_AcSwitchOnOff, LV_STATE_CHECKED);
    }

  
  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_MODE)) == 0) {

    if (strcmp_P((char*)payload, PSTR(PAYLOAD_MODE_AUTO)) == 0) {
      lv_obj_set_style_arc_color(ui_SetpointArc, lv_color_hex(0xC1CA1E), LV_PART_INDICATOR | LV_STATE_DEFAULT );  // yellow
      lv_dropdown_set_selected(ui_ModeSelect, 0);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_MODE_DRY)) == 0) {
      lv_obj_set_style_arc_color(ui_SetpointArc, lv_color_hex(0xC1CA1E), LV_PART_INDICATOR | LV_STATE_DEFAULT );  // yellow
      lv_dropdown_set_selected(ui_ModeSelect, 3);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_MODE_COOL)) == 0) {
      lv_obj_set_style_arc_color(ui_SetpointArc, lv_color_hex(0x1E6FCA), LV_PART_INDICATOR | LV_STATE_DEFAULT );  // blue
      lv_dropdown_set_selected(ui_ModeSelect, 1);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_MODE_FAN)) == 0) {
      lv_obj_set_style_arc_color(ui_SetpointArc, lv_color_hex(0xC1CA1E), LV_PART_INDICATOR | LV_STATE_DEFAULT );  // yellow
      lv_dropdown_set_selected(ui_ModeSelect, 4);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_MODE_HEAT)) == 0) {
      lv_obj_set_style_arc_color(ui_SetpointArc, lv_color_hex(0xF7052A), LV_PART_INDICATOR | LV_STATE_DEFAULT ); // red
      lv_dropdown_set_selected(ui_ModeSelect, 2);
    }

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_FAN)) == 0) {
      
    if (strcmp_P((char*)payload, PAYLOAD_FAN_AUTO) == 0){
      lv_dropdown_set_selected(ui_FanSelect, 0);
    }
    else if (strcmp_P((char*)payload, "1") == 0){
      lv_dropdown_set_selected(ui_FanSelect, 1);
    }
    else if (strcmp_P((char*)payload, "2") == 0){
      lv_dropdown_set_selected(ui_FanSelect, 2);
    }
    else if (strcmp_P((char*)payload, "3") == 0){
      lv_dropdown_set_selected(ui_FanSelect, 3);
    }
    else if (strcmp_P((char*)payload, "4") == 0){
      lv_dropdown_set_selected(ui_FanSelect, 4);
    }

  } else if (strcmp_P(topic, PSTR(MQTT_OP_PREFIX TOPIC_DEFROST)) == 0) {

    if (strcmp_P((char*)payload, PSTR(PAYLOAD_OP_DEFROST_ON)) == 0) {
      lv_obj_clear_flag(ui_Defrost, LV_OBJ_FLAG_HIDDEN);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_OP_DEFROST_OFF)) == 0) {
      lv_obj_add_flag(ui_Defrost, LV_OBJ_FLAG_HIDDEN);
    }

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_VANESLR)) == 0) {
      
    if (strcmp_P((char*)payload, PSTR(PAYLOAD_VANESLR_SWING)) == 0) {
      lv_img_set_src(ui_Vanes, &ui_img_vaneslrswing_png);
      lv_dropdown_set_selected(ui_VaneLRSelect1, 7);
    }
    else {
      int value = atoi((char*)payload);
      switch (value) {
        case 1:
          lv_img_set_src(ui_Vanes, &ui_img_vanesll_png);
          lv_dropdown_set_selected(ui_VaneLRSelect1, 0);
          break;
        case 2:
          lv_img_set_src(ui_Vanes, &ui_img_vaneslm_png);
          lv_dropdown_set_selected(ui_VaneLRSelect1, 1);
          break;
        case 3:
          lv_img_set_src(ui_Vanes, &ui_img_vanesmm_png);
          lv_dropdown_set_selected(ui_VaneLRSelect1, 2);
          break;
        case 4:
          lv_img_set_src(ui_Vanes, &ui_img_vanesmr_png);
          lv_dropdown_set_selected(ui_VaneLRSelect1, 3);
          break;
        case 5:
          lv_img_set_src(ui_Vanes, &ui_img_vanesrr_png);
          lv_dropdown_set_selected(ui_VaneLRSelect1, 4);
          break;
        case 6:
          lv_img_set_src(ui_Vanes, &ui_img_vaneslr_png);
          lv_dropdown_set_selected(ui_VaneLRSelect1, 5);
          break;
        case 7:
          lv_dropdown_set_selected(ui_VaneLRSelect1, 6);
          lv_img_set_src(ui_Vanes, &ui_img_vanesrl_png);
          break;
      }
    }

  } else if (strcmp_P(topic, PSTR(MQTT_OP_PREFIX TOPIC_IU_FANSPEED)) == 0) {
    FanIU = atoi((char*)payload);
    lv_label_set_text_fmt(ui_FanIULabel, "%d", FanIU);

  } else if (strcmp_P(topic, PSTR(MQTT_OP_PREFIX TOPIC_OUTDOOR)) == 0) {
    int f=atof((char*)payload) * 10;
    lv_label_set_text_fmt(ui_OutdoorTemperatureLabel, "%d,%d", f / 10, f %10);

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_VANES)) == 0) {
      
    if (strcmp_P((char*)payload, PSTR(PAYLOAD_VANES_SWING)) == 0) {
      lv_img_set_src(ui_VanesUD, &ui_img_vanesswing_png);
      lv_dropdown_set_selected(ui_VaneSelect1, 4);
    } else if (strcmp_P((char*)payload, PSTR(PAYLOAD_VANES_UNKNOWN)) == 0) {
      lv_img_set_src(ui_VanesUD, &ui_img_vanesunknown_png);
      lv_dropdown_set_selected(ui_VaneSelect1, 5);
    }
    else {
      int value = atoi((char*)payload);
      switch (value) {
        case 1:
          lv_img_set_src(ui_VanesUD, &ui_img_vaneshigh_png);
          lv_dropdown_set_selected(ui_VaneSelect1, 0);
          break;
        case 2:
          lv_img_set_src(ui_VanesUD, &ui_img_vanesmiddle_png);
          lv_dropdown_set_selected(ui_VaneSelect1, 1);
          break;
        case 3:
          lv_img_set_src(ui_VanesUD, &ui_img_vanesdeep_png);
          lv_dropdown_set_selected(ui_VaneSelect1, 2);
          break;
        case 4:
          lv_img_set_src(ui_VanesUD, &ui_img_vanesdeepest_png);
          lv_dropdown_set_selected(ui_VaneSelect1, 3);
          break;
      }
    }
  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_3DAUTO)) == 0) {

    if (strcmp_P((char*)payload, PSTR(PAYLOAD_3DAUTO_ON)) == 0) {
      lv_obj_clear_flag(ui_Label3Dauto, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_VanesLRPanel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_flag(ui_VanesUDPanel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_add_state(ui_Auto3DOnOff1, LV_STATE_CHECKED);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_3DAUTO_OFF)) == 0) {
      lv_obj_add_flag(ui_Label3Dauto, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_VanesLRPanel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_flag(ui_VanesUDPanel, LV_OBJ_FLAG_HIDDEN);
      lv_obj_clear_state(ui_Auto3DOnOff1, LV_STATE_CHECKED);
    }

  } else if (strcmp_P(topic, PSTR(MQTT_OP_PREFIX TOPIC_CT)) == 0) {
    int i=atof((char*)payload) * VOLTAGE;
    PowerUsage = i;
    lv_label_set_text_fmt(ui_LabelWatt, "%d W", i );

  } else if (strcmp_P(topic, PSTR(MQTT_OP_PREFIX TOPIC_KWH)) == 0) {
    int f=atof((char*)payload) * 100;
    lv_label_set_text_fmt(ui_LabelkWh, "%d,%d kWh", f/100, f%100 );

  } else if (strcmp_P(topic, PSTR(MQTT_OP_PREFIX TOPIC_COMP)) == 0) {

    float f=atof((char*)payload);
    CompressorHz = f;
    int i = f * 100;

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX TOPIC_AUTO_CONTROL_EXTRAS)) == 0) {

    if (strcmp_P((char*)payload, PSTR(PAYLOAD_AUTO_CONTROL_ON)) == 0) {
      lv_obj_add_state(ui_AutoControlOnOff, LV_STATE_CHECKED);
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_AUTO_CONTROL_OFF)) == 0) {
      lv_obj_clear_state(ui_AutoControlOnOff, LV_STATE_CHECKED);
    }

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX_CLIENT TOPIC_BRIGHTNESS)) == 0) {

    int i=atof((char*)payload);
    if ( i>= 1 && i<=255 ) {
      Brightness = i;
      tft.setBrightness(Brightness);
      lv_slider_set_value( ui_SliderBrightness, Brightness, LV_ANIM_OFF);
    }

  } else if (strcmp_P(topic, PSTR(MQTT_PREFIX_CLIENT TOPIC_SNOOZE)) == 0) {

    if (strcmp_P((char*)payload, PSTR(PAYLOAD_SNOOZE_ON)) == 0) {
      lv_obj_add_state(ui_SnoozeOnOff, LV_STATE_CHECKED);
      Snooze = true;
    }
    else if (strcmp_P((char*)payload, PSTR(PAYLOAD_SNOOZE_OFF)) == 0) {
      lv_obj_clear_state(ui_SnoozeOnOff, LV_STATE_CHECKED);
      Snooze = false;
    }
  }
}

// Adjust x axis labes charts. 
static void draw_event_cb_chart_x_axis(lv_event_t * e)
{
  lv_obj_draw_part_dsc_t * dsc = lv_event_get_draw_part_dsc(e);
  if(!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL)) return;

  const char *x_axis[] = {"-10m", "-8m", "-6m", "-4m", "-2m", "0"};

  if(dsc->id == LV_CHART_AXIS_PRIMARY_X && dsc->text) {
    //Serial.printf("draw_event_cb_chart_x_axis(): dsc->value %d\n", dsc->value);
    lv_snprintf(dsc->text, dsc->text_length, "%s", x_axis[dsc->value]);
  }
  //lv_chart_set_axis_tick(chart_values, LV_CHART_AXIS_PRIMARY_X, 10, 5, 7, 2, true, 40);
}

static void DrawCallbackEvent(lv_event_t* e)
{
    // https://forum.lvgl.io/t/what-is-the-logic-behind-lv-chart-set-axis-tick/13622/3

    //Get the event descriptor
    lv_obj_draw_part_dsc_t* dsc = lv_event_get_draw_part_dsc(e);

    //Check what part we are updating. Only proceed if we are updating one of the tick label(s)
    if (!lv_obj_draw_part_check_type(dsc, &lv_chart_class, LV_CHART_DRAW_PART_TICK_LABEL))
        return;

    //Check this is a callback for a major tick (minor ticks have 0 here)
    if (dsc->text == NULL)
        return;

    //Get the multiplier from the user data
    //EventData_t *eventData = (EventData_t*)lv_event_get_user_data(e);

    //If we are editing the Y axis
    if (dsc->id == LV_CHART_AXIS_PRIMARY_Y)
    {
        //update the label with the modified multiplier
        lv_snprintf(dsc->text, dsc->text_length, "%d,%d", dsc->value / 100, dsc->value % 100);
        //lv_snprintf(dsc->text, dsc->text_length, "%.2f", (float)dsc->value / 10);
        //Serial.printf("DrawCallbackEvent(): dsc->value %.2f dsc->text_length: %d\n", (float)dsc->value / 10, dsc->text_length);
    }
}

void updateCurrentTemperatureChartRefresh() 
{
    int max = 0;
    int min = 10000;
    int value;
    int i = CurrentTemperature * 100;
    lv_chart_set_next_value(ui_ChartCurrentTemp, ui_ChartCurrentTemp_series_1, i ); // update chart
    //Serial.printf("Update_CurrentTemperatureChartRefresh() CurrentTemperature: %f chart temp: %d\n", CurrentTemperature, i);

    size_t count = lv_chart_get_point_count(ui_ChartCurrentTemp);
    //Serial.printf("Update_CurrentTemperatureChartRefresh() Count: %d\n", count);
    for (size_t i = 0; i < count; i++) {
      value = ui_ChartCurrentTemp_series_1->y_points[i];
      //Serial.printf("%d, ", value);  

      if ( value == 32767 ) continue;
      if (value > max) max = value;
      if (value < min) min = value;
    }

    max = ((max + 100) / 100) * 100;
    min = (min / 100) * 100;

    //Serial.printf("\nUpdate_CurrentTemperatureChartRefresh() min: %d max: %d\n", min, max);
    lv_chart_set_range(ui_ChartCurrentTemp, LV_CHART_AXIS_PRIMARY_Y , min, max);
}

void updateCompressorHzChartRefresh() 
{
  int i = CompressorHz * 100;
  lv_chart_set_next_value(ui_ChartCompressor, ui_ChartCompressor_series_1, i/100); // update chart
}

void updateFanIUChartRefresh() 
{
  lv_chart_set_next_value(ui_ChartFanIU, ui_ChartFanIU_series_1, FanIU); // update chart
}

void updatePowerUsageChartRefresh() 
{
  lv_chart_set_next_value(ui_ChartWatt, ui_ChartWatt_series_1, PowerUsage); // update chart
}


void WiFiSymbolOn() {
  lv_obj_set_style_img_recolor_opa(ui_Wifi1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi4, 255, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi5, 255, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
}

void WiFiSymbolOff() {
  lv_obj_set_style_img_recolor_opa(ui_Wifi1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi4, 0, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
  lv_obj_set_style_img_recolor_opa(ui_Wifi5, 0, LV_PART_MAIN| LV_STATE_DEFAULT);  // enable wifi symbol
}

void initWiFi(){
  WiFi.persistent(false);
  WiFi.disconnect(true);    // Delete SDK wifi config
  delay(200);
  WiFi.mode(WIFI_STA);
  WiFi.hostname(CLIENTNAME); 
  WiFi.setAutoReconnect(false);
}

void setupWiFi(int& WiFiStatus) {
  int max_rssi = -999;
  int strongest_AP = -1;
  static unsigned long WiFiTimeoutMillis;

  if(WiFiStatus != WIFI_CONNECT_ONGOING) {
    WiFi.scanDelete();
    uint networksFound = WiFi.scanNetworks();
    Serial.printf("setupWiFi:%i access points available\n", networksFound);
    for (uint i = 0; i < networksFound; i++)
    {
      Serial.printf("%2d %25s %2d %ddBm %s %s %02x\n", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.BSSIDstr(i).c_str(), WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "open" : "secured"), (uint)WiFi.encryptionType(i);
      if((strcmp(WiFi.SSID(i).c_str(), WIFI_SSID) == 0) && (WiFi.RSSI(i)>max_rssi)){
          max_rssi = WiFi.RSSI(i);
          strongest_AP = i;
      }
    }
    Serial.printf("setupWiFi2:%i access points available\n", networksFound);
    //Serial.printf_P("current BSSID: %s, strongest BSSID: %s\n", WiFi.BSSIDstr().c_str(), WiFi.BSSIDstr(strongest_AP).c_str());
    if((WiFi.status() != WL_CONNECTED) || ((max_rssi > WiFi.RSSI() + 10) && (strcmp(WiFi.BSSIDstr().c_str(), WiFi.BSSIDstr(strongest_AP).c_str()) != 0))) {
      if(strongest_AP != -1) {
        Serial.printf("Connecting from bssid:%s to bssid:%s, channel:%i\n", WiFi.BSSIDstr().c_str(), WiFi.BSSIDstr(strongest_AP).c_str(), WiFi.channel(strongest_AP));
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD, WiFi.channel(strongest_AP), WiFi.BSSID(strongest_AP), true);
      }
      else {
        Serial.println("No matching AP found (maybe hidden SSID), however try to connect.");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
      }
      WiFiStatus = WIFI_CONNECT_ONGOING;
      Serial.println("WIFI_CONNECT_ONGOING");
      WiFiTimeoutMillis = millis();
    }
    //Serial.printf("setupWiFi3:%i access points available\n", networksFound);
  }
  else { // WiFiStatus == WIFI_CONNECT_ONGOING
    if(WiFi.status() == WL_CONNECTED){
      Serial.printf_P(PSTR(" connected to %s, IP address: %s (%ddBm)\n"), WIFI_SSID, WiFi.localIP().toString().c_str(), WiFi.RSSI());
      WiFiStatus = WIFI_CONNECT_OK;
      Serial.println("WIFI_CONNECT_OK");
      WiFiSymbolOn();
    }
    else if(millis() - WiFiTimeoutMillis > 10*1000) {  // timeout after 10 seconds
      WiFiStatus = WIFI_CONNECT_TIMEOUT;
      Serial.println(PSTR("WIFI_CONNECT_TIMEOUT"));
    }
    //Serial.printf("setupWiFi4:%i access points available\n", networksFound);
  }
  //Serial.printf("setupWiFi E:%i access points available\n", networksFound);
}

void setup() {
  Serial.begin(115200);
  
  tft.begin();
  tft.setRotation(2);
  tft.setBrightness(Brightness);
  tft.fillScreen(TFT_BLACK); 

  lv_init();
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 10);

   /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);

  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  ui_init();

  initWiFi();

  lv_slider_set_value( ui_SliderBrightness, Brightness, LV_ANIM_OFF);

  Serial.println("Setup MQTT");

  MQTTclient.setServer(MQTT_SERVER, MQTT_PORT);
  MQTTclient.setCallback(MQTT_subscribe_callback);

  lv_chart_set_update_mode(ui_ChartCurrentTemp, LV_CHART_UPDATE_MODE_SHIFT);  // update mode chart
  ui_ChartCurrentTemp_series_1 = lv_chart_add_series(ui_ChartCurrentTemp, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);

  lv_obj_add_event_cb(ui_ChartCurrentTemp, draw_event_cb_chart_x_axis, LV_EVENT_DRAW_PART_BEGIN, NULL);
  lv_obj_add_event_cb(ui_ChartCurrentTemp, DrawCallbackEvent, LV_EVENT_DRAW_PART_BEGIN, NULL);
  
/*
  static lv_coord_t ui_ChartCurrentTemp_series_1_array[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
  lv_chart_set_ext_y_array(ui_ChartCurrentTemp, ui_ChartCurrentTemp_series_1, ui_ChartCurrentTemp_series_1_array);
*/
  lv_chart_set_update_mode(ui_ChartCompressor, LV_CHART_UPDATE_MODE_SHIFT);  // update mode chart
  ui_ChartCompressor_series_1 = lv_chart_add_series(ui_ChartCompressor, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
  lv_obj_add_event_cb(ui_ChartCompressor, draw_event_cb_chart_x_axis, LV_EVENT_DRAW_PART_BEGIN, NULL);

  lv_chart_set_update_mode(ui_ChartFanIU, LV_CHART_UPDATE_MODE_SHIFT);  // update mode chart
  ui_ChartFanIU_series_1 = lv_chart_add_series(ui_ChartFanIU, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
  lv_obj_add_event_cb(ui_ChartFanIU, draw_event_cb_chart_x_axis, LV_EVENT_DRAW_PART_BEGIN, NULL);

  lv_chart_set_update_mode(ui_ChartWatt, LV_CHART_UPDATE_MODE_SHIFT);  // update mode chart
  ui_ChartWatt_series_1 = lv_chart_add_series(ui_ChartWatt, lv_color_hex(0x808080), LV_CHART_AXIS_PRIMARY_Y);
  lv_obj_add_event_cb(ui_ChartWatt, draw_event_cb_chart_x_axis, LV_EVENT_DRAW_PART_BEGIN, NULL);

  Serial.println("setup done");
}




void loop() {
  static int WiFiStatus = WIFI_CONNECT_TIMEOUT;   // start connecting to WiFi
  static int MQTTStatus = MQTT_NOT_CONNECTED;
  static unsigned long refresh_timestamp = millis();

  if (((WiFi.status() != WL_CONNECTED)  || 
       (WiFiStatus != WIFI_CONNECT_OK))) {
    //Serial.printf("loop: call setupWiFi(WiFiStatus)\n");
    WiFiSymbolOff();
    setupWiFi(WiFiStatus);
    //Serial.println(WiFiStatus);
  }
  else {
    //Serial.printf("loop: WiFi.status()=%i\n", WiFi.status()); // see https://realglitch.com/2018/07/arduino-wifi-status-codes/
    MQTTStatus=MQTTreconnect();
  }

  lv_timer_handler();
  //MQTTreconnect();
  if( millis() - refresh_timestamp > 1000*30 )
  {
    refresh_timestamp = millis();
   // Refresh Chart, this part will be executed every 30 seconds
    updateCurrentTemperatureChartRefresh();
    updateCompressorHzChartRefresh();
    updatePowerUsageChartRefresh();
    updateFanIUChartRefresh();
  }

  if(Snooze && !ScreenSnoozed) {
    if(millis() - snooze_Millis >= SNOOZE_TIME_SEC*1000) {
      tft.setBrightness(10);
      _ui_screen_change( &ui_SnoozeScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_SnoozeScreen_screen_init);
      ScreenSnoozed = true;
    } 
  } else {
    snooze_Millis = millis();
  }
  
  delay(5);
}


//SquareLine functions to add manually if "dont export function" checked

void SwitchACOnOff(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int AC_OnOff = lv_obj_has_state(obj, LV_STATE_CHECKED);
  Serial.printf("clicked SwitchACOnOff state: %s\n", AC_OnOff ? "On" : "Off");

  if (AC_OnOff) {
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_POWER, PAYLOAD_POWER_ON, false);
  } else {
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_POWER, PAYLOAD_POWER_OFF, false);
  }

}

void Switch3DautoOnOff(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int Auto3D_OnOff = lv_obj_has_state(obj, LV_STATE_CHECKED);
  Serial.printf("clicked Switch3DautoOnOff state: %s\n", Auto3D_OnOff ? "On" : "Off");

  if (Auto3D_OnOff) {
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_3DAUTO, PAYLOAD_3DAUTO_ON, false);
  } else {
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_3DAUTO, PAYLOAD_3DAUTO_OFF, false);
  }

}

void SwitchAutocontrolOnOff(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int AutoControl_OnOff = lv_obj_has_state(obj, LV_STATE_CHECKED);
  Serial.printf("clicked SwitchAutocontrolOnOff state: %s\n", AutoControl_OnOff ? "On" : "Off");

  if (AutoControl_OnOff) {
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_AUTO_CONTROL_EXTRAS, PAYLOAD_AUTO_CONTROL_ON, false);
  } else {
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_AUTO_CONTROL_EXTRAS, PAYLOAD_AUTO_CONTROL_OFF, false);
  }

}

void RestartESP(lv_event_t * e)
{
	// Your code here
  Serial.printf("clicked RestartESP\n");

  MQTTclient.publish(MQTT_SET_PREFIX TOPIC_REQUEST_RESET, PAYLOAD_REQUEST_RESET, false);
}

void SetModeAC(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int mode = lv_dropdown_get_selected(obj);
  Serial.printf("clicked SetModeAC, index selected: %d\n", mode);

  switch (mode) {
    case 0:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_MODE, PAYLOAD_MODE_AUTO, false);
      break;
    case 1:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_MODE, PAYLOAD_MODE_COOL, false);
      break;
    case 2:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_MODE, PAYLOAD_MODE_HEAT, false);
      break;
    case 3:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_MODE, PAYLOAD_MODE_DRY, false);
      break;
    case 4: 
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_MODE, PAYLOAD_MODE_FAN, false);
      break;
  }

}

void SetFanAC(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int fan = lv_dropdown_get_selected(obj);
  Serial.printf("clicked SetFanAC, index selected %d\n", fan);

  switch (fan) {
    case 0:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_FAN, PAYLOAD_FAN_AUTO, false);
      break;
    case 1:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_FAN, "1", false);
      break;
    case 2:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_FAN, "2", false);
      break;
    case 3:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_FAN, "3", false);
      break;
    case 4: 
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_FAN, "4", false);
      break;
  }
}

void SetVaneAC(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int vane = lv_dropdown_get_selected(obj);
  Serial.printf("clicked SetVaneAC, index selected %d\n", vane);

  switch (vane) {
    case 0:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANES, "1", false);
      break;
    case 1:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANES, "2", false);
      break;
    case 2:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANES, "3", false);
      break;
    case 3: 
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANES, "4", false);
      break;
    case 4:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANES, PAYLOAD_VANES_SWING, false);
      break;
  }
}

void SetVaneLRAC(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int vaneLR = lv_dropdown_get_selected(obj);
  Serial.printf("clicked SetVaneLRAC, index selected %d\n", vaneLR);

  switch (vaneLR) {
    case 0:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, "1", false);
      break;
    case 1:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, "2", false);
      break;
    case 2:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, "3", false);
      break;
    case 3: 
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, "4", false);
      break;
    case 4: 
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, "5", false);
      break;
    case 5: 
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, "6", false);
      break;
    case 6: 
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, "7", false);
      break;
    case 7:
      MQTTclient.publish(MQTT_SET_PREFIX TOPIC_VANESLR, PAYLOAD_VANESLR_SWING, false);
      break;
  }
}


void setSetpointUp(lv_event_t * e)
{
	// Your code here
  Serial.println("clicked setSetpointUp");

  int value = lv_arc_get_value(ui_SetpointArc);
  Serial.printf("setSetpointUp(): Value: %i\n", value);         
  float setpoint = value / 2.0;
  if (setpoint < 30.0) {
    setpoint = setpoint + 0.5;
    Serial.printf("setSetpointUp(): setpoint: %f\n", setpoint);         
    value = setpoint * 10 ;
    Serial.printf("setSetpointUp(): value2: %i\n", value);         
    lv_label_set_text_fmt(ui_SetpointCelsius, "%d,%d", value / 10, value % 10);
    value = setpoint * 2;
    lv_arc_set_value(ui_SetpointArc, (value) );

    char strtmp[10];
    dtostrf(setpoint, 0, 2, strtmp);
    MQTTclient.publish(MQTT_SET_PREFIX TOPIC_TSETPOINT, strtmp, false);
  }

}

void setSetpointDown(lv_event_t * e)
{
	// Your code here
  Serial.println("clicked setSetpointDown");

  int value = lv_arc_get_value(ui_SetpointArc);
  Serial.printf("setSetpointUp(): Value: %i\n", value);         
  float setpoint = value / 2.0;
  if (setpoint > 18.0) {
    setpoint = setpoint - 0.5;
    Serial.printf("setSetpointUp(): setpoint: %f\n", setpoint);         
    value = setpoint * 10 ;
    Serial.printf("setSetpointUp(): value2: %i\n", value);         
    lv_label_set_text_fmt(ui_SetpointCelsius, "%d,%d", value / 10, value % 10);
    value = setpoint * 2;
    lv_arc_set_value(ui_SetpointArc, (value) );

    char strtmp[10];
    dtostrf(setpoint, 0, 2, strtmp);
    MQTTclient.publish(MQTT_SET_PREFIX TOPIC_TSETPOINT, strtmp, false);
  }

}

void setBrightness(lv_event_t * e)
{
  char strtmp[10];

	// Your code here
  lv_obj_t * slider = lv_event_get_target(e);
  Brightness = lv_slider_get_value(slider);
  Serial.printf("setBrightness(): Value: %i\n", Brightness);    

    // Store brightness in MQTT topic
  itoa(Brightness, strtmp, 10);
  MQTTclient.publish(MQTT_PREFIX_CLIENT TOPIC_BRIGHTNESS, strtmp, true);
  // Brightness is changed after receiving from MQTT

}

void SwitchSnoozeOnOff(lv_event_t * e)
{
	// Your code here
  lv_obj_t * obj = lv_event_get_target(e);
  int Snooze_OnOff = lv_obj_has_state(obj, LV_STATE_CHECKED);
  Serial.printf("clicked SwitchSnoozeOnOff state: %s\n", Snooze_OnOff ? "On" : "Off");

  if (Snooze_OnOff) {
      MQTTclient.publish(MQTT_PREFIX_CLIENT TOPIC_SNOOZE, PAYLOAD_SNOOZE_ON, true);
  } else {
      MQTTclient.publish(MQTT_PREFIX_CLIENT TOPIC_SNOOZE, PAYLOAD_SNOOZE_OFF, true);
  }

}

void SnoozeScreenClicked(lv_event_t * e)
{
  Serial.printf("clicked SnoozeScreenClicked\n");
  tft.setBrightness(Brightness);
  ScreenSnoozed = false;
}

void StopAnimation(lv_event_t * e)
{
  Serial.printf("StopAnimation\n");
  lv_anim_del( NULL,  (lv_anim_exec_xcb_t) _ui_anim_callback_set_x );   // https://forum.squareline.io/t/temporary-screen-with-an-infinite-loop-animation-crashes-when-deleted/2039/5

}

void ResetSnooze(lv_event_t * e)
{
  Serial.printf("ResetSnooze\n");
  snooze_Millis = millis();
}
