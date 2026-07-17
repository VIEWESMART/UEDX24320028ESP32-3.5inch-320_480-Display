/*
 *November 2024
 *Author: LiuLong
 *Shenzhen VIEWE TECHNOLOGY Co., LTD
 */

#include <stdio.h>
#include "lv_demos.h"
#include "board.h"
#include "driver/ledc.h"
#include "driver/rmt.h"
#include "esp_log.h"

static const char *TAG = "EXAMPLE";

// 硬件定义
#define BUZZER_GPIO         38      // 蜂鸣器引脚
#define RGB_GPIO            0       // RGB数据引脚
#define BUZZER_LEDC_CHANNEL LEDC_CHANNEL_0
#define BUZZER_LEDC_TIMER   LEDC_TIMER_0
#define BUZZER_LEDC_MODE    LEDC_LOW_SPEED_MODE
#define RMT_CHANNEL         RMT_CHANNEL_0

// RGB灯配置（WS2812）
#define NUM_LEDS            1       // LED数量
#define RMT_RESOLUTION      10000000 // 10MHz分辨率

// 全局定时器句柄
static esp_timer_handle_t shutdown_timer;

/* PWM蜂鸣器初始化 */
static void buzzer_init(void)
{
    // 1. 定时器配置
    ledc_timer_config_t timer_conf = {
        .speed_mode = BUZZER_LEDC_MODE,
        .duty_resolution = LEDC_TIMER_10_BIT,
        .timer_num = BUZZER_LEDC_TIMER,
        .freq_hz = 2000,           // 2kHz频率
        .clk_cfg = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&timer_conf));

    // 2. 通道配置
    ledc_channel_config_t channel_conf = {
        .gpio_num = BUZZER_GPIO,
        .speed_mode = BUZZER_LEDC_MODE,
        .channel = BUZZER_LEDC_CHANNEL,
        .intr_type = LEDC_INTR_DISABLE,
        .timer_sel = BUZZER_LEDC_TIMER,
        .duty = 512,              // 50%占空比（10bit分辨率）
        .hpoint = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&channel_conf));
}

/* RGB灯初始化（WS2812） */
static void rgb_init(void)
{
    // RMT传输配置
    rmt_config_t config = {
        .rmt_mode = RMT_MODE_TX,
        .channel = RMT_CHANNEL,
        .gpio_num = RGB_GPIO,
        .clk_div = 80,            // 80MHz/80 = 1MHz
        .mem_block_num = 1,
        .flags = 0
    };
    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));
}

/* 设置RGB颜色 */
static void set_rgb_color(uint8_t red, uint8_t green, uint8_t blue)
{
    rmt_item32_t items[NUM_LEDS * 24];
    uint32_t color = (green << 16) | (red << 8) | blue;

    for (int i = 0; i < 24; i++) {
        items[i].level0 = 1;
        items[i].duration0 = ((color << i) & 0x800000) ? 8 : 4;
        items[i].level1 = 0;
        items[i].duration1 = 4;
    }

    ESP_ERROR_CHECK(rmt_write_items(RMT_CHANNEL, items, NUM_LEDS * 24, true));
}

/* 定时器回调（5秒后关闭设备） */
static void shutdown_devices(void* arg)
{
    // 关闭蜂鸣器
    ESP_ERROR_CHECK(ledc_set_duty(BUZZER_LEDC_MODE, BUZZER_LEDC_CHANNEL, 0));
    ESP_ERROR_CHECK(ledc_update_duty(BUZZER_LEDC_MODE, BUZZER_LEDC_CHANNEL));

    // 关闭RGB灯
    set_rgb_color(0, 0, 0);

    ESP_LOGI(TAG, "Devices shutdown after 5s");
}

void display_coordinates(int x, int y) {
    // 显示触摸坐标
    static lv_obj_t *label = NULL;
    if (label == NULL) {
        label = lv_label_create(lv_scr_act());
        lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 10, -10); // 设置标签位置
    }
    char buf[32];
    snprintf(buf, sizeof(buf), "Touch: (%d, %d)", x, y);
    lv_label_set_text(label, buf); // 更新标签文本
}

static lv_point_t last_touch_point = {-1, -1}; // 用于存储上一个触摸点
static void touch_event_handler(lv_event_t *e) {
    lv_indev_t *indev = lv_indev_get_act();
    lv_point_t touch_point;

    // 获取触摸点
    lv_indev_get_point(indev, &touch_point);
    
    if (touch_point.x >= 0 && touch_point.y >= 0) {
        display_coordinates(touch_point.x, touch_point.y); // 显示坐标
    } else {
        // 如果触摸点无效，重置上一个触摸点
        last_touch_point.x = -1;
        last_touch_point.y = -1;
    }
}

void create_touch_test_screen() {
    // 清除当前界面
    lv_obj_clean(lv_scr_act());

    // 创建触摸测试界面
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Touch the screen!");
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    // 设置字体为 24pt 的 Montserrat 字体
    // lv_obj_set_style_text_font(label, &lv_font_montserrat_24, LV_PART_MAIN);

    // 注册触摸事件
    lv_obj_add_event_cb(lv_scr_act(), touch_event_handler, LV_EVENT_PRESSING, NULL);

}

void app_main(void)
{
    /* LCD HW initialization */
    ESP_ERROR_CHECK(app_lcd_init());

    /* Touch initialization */
    ESP_ERROR_CHECK(app_touch_init());

    /* LVGL initialization */
    ESP_ERROR_CHECK(app_lvgl_init());

    // /* 初始化蜂鸣器 */
    // buzzer_init();
    
    // /* 初始化RGB灯 */
    // rgb_init();

    // /* 启动设备 */
    // set_rgb_color(255, 0, 0);  // 红色
    // ESP_ERROR_CHECK(ledc_set_duty(BUZZER_LEDC_MODE, BUZZER_LEDC_CHANNEL, 512));
    // ESP_ERROR_CHECK(ledc_update_duty(BUZZER_LEDC_MODE, BUZZER_LEDC_CHANNEL));

    // /* 创建关闭定时器 */
    // const esp_timer_create_args_t shutdown_timer_args = {
    //     .callback = &shutdown_devices,
    //     .name = "shutdown_timer"
    // };
    // ESP_ERROR_CHECK(esp_timer_create(&shutdown_timer_args, &shutdown_timer));
    // ESP_ERROR_CHECK(esp_timer_start_once(shutdown_timer, 5000000)); // 5秒


    /* Show LVGL objects */
    // app_main_display();
    lvgl_port_lock(0);
    // lv_demo_stress();
    lv_demo_widgets();
    // lv_demo_music();
    // create_touch_test_screen();

    lvgl_port_unlock();
    ESP_ERROR_CHECK(gpio_set_level(EXAMPLE_LCD_GPIO_BL, EXAMPLE_LCD_BL_ON_LEVEL));
}
