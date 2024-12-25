# Squareline Simple Wi-Fi Clock Example

This example implements a simple Wi-Fi clock demo, which UI is created by Squareline Studio.

This example can run on various LCD resolutions, but since the UI itself is designed based on a 320x240 resolution, it will look very uncoordinated if the actual resolution is too large.

## How to Use

To use this example, please firstly install the following libraries:

- lvgl (v8.3.x)
- ESP32_Display_Panel (> 0.2.1)
- ESP32_IO_Expander (>= 0.1.0 && < 0.2.0)
- NTPClient (v3.2.1)
- ArduinoJson (v6.21.3)

Then follow the steps below to configure the example.

1. For **ESP32_Display_Panel**:

   `Note`:Since the latest version is still being updated and has not been released, please temporarily use the test version in this repository: `Libraries`->[`ESP32_Display_Panel`](https://github.com/VIEWESMART/UEDX24320028ESP32-3.5inch-320_480-Display/tree/main/Libraries/ESP32_Display_Panel).
   
    - Follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/How_To_Use.md#configuring-drivers) to configure drivers if needed.
    - If using a supported development board, follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/How_To_Use.md#using-supported-development-boards) to configure it.
    - If using a custom board, follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/How_To_Use.md#using-custom-development-boards) to configure it.

2. For **ESP32_IO_Expander**:
   - Just install it directly.

3. Copy the [ui](./libraries/ui/) folder from `libraries` to [Arduino Library directory](../../../../README.md#where-is-the-directory-for-arduino-libraries).Here I have put ui into the libraries.

4. For **lvgl**:

   - Follow the [steps](https://github.com/VIEWESMART/VIEWE-FAQ/blob/main/Arduino-FAQ/English/FAQ.md#how-to-add-an-lvgl-library-and-how-to-configure) to add *lv_conf.h* file and change the configurations. Additionally, set the following configurations to `1`:

      - `LV_FONT_MONTSERRAT_12`
      - `LV_FONT_MONTSERRAT_14`
      - `LV_FONT_MONTSERRAT_16`
      - `LV_FONT_MONTSERRAT_32`
      - `LV_FONT_MONTSERRAT_48`
      - `LV_USE_LARGE_COORD`

   - Modify the macros in the [lvgl_port_v8.h](./lvgl_port_v8.h) file to configure the LVGL porting parameters.

5. Modify the macros in the [lvgl_port_v8.h](./lvgl_port_v8.h) file to configure the LVGL porting parameters.
6. To obtain weather information after connecting to Wi-Fi, please follow these steps to configure the example:

   - Register an account on [OpenWeather](https://openweathermap.org/) and obtain an **API KEY**.
   - Fill the obtained API KEY in the macro definition `WEATHER_API_KEY`.
   - Fill the name of the city for which need to obtain weather information (such as `Shanghai`) in the macro definition `WEATHER_CITY`.

7. To obtain and calibrate time information after connecting to Wi-Fi, Please correctly fill in your time zone within the macro `TIMEZONE_OFFSET` (such as `CST-8`).
8. Navigate to the `Tools` menu in the Arduino IDE to choose a ESP board and configure its parameters.
    | Setting                               | Value                                 |
    | :-------------------------------: | :-------------------------------: |
    | Board                                 | ESP32S3 Dev Module           |
    | CPU Frequency                   | 240MHz (WiFi)                    |
    | Core Debug Level                | None                                 |
    | USB CDC On Boot                | Disabled                              |
    | USB DFU On Boot                | Disabled                             |
    | Events Run On                     | Core 1                               |  
    | Flash Mode                         | QIO 80MHz                         |
    | Flash Size                           | 16MB (128Mb)                    |
    | Arduino Runs On                  | Core 1                               |
    | USB Firmware MSC On Boot | Disabled                             |
    | Partition Scheme                | 16M Flash (3MB APP/9.9MB FATFS) |
    | PSRAM                                | OPI PSRAM                         |
    | Upload Mode                     |     UART0/Hardware CDC            |
    | Upload Speed                     | 921600                               |
    | USB Mode                           | Hardware CDC and JTAG     |
9. Verify and upload the example to your ESP board.
10. If burning fails Please hold down the "BOOT" button and try downloading the program again.

## Serial Output

```bash
...
Squareline WiFi clock example start
Initialize panel device
Initialize LVGL
Create UI
wifi_connected_flag: false
Squareline WiFi clock example end
Scan done
wifi_list_switch: false
Wifi list show:
wifi_list_switch: false
...
```

## Troubleshooting

Please check the [FAQ](https://github.com/VIEWESMART/VIEWE-FAQ/tree/main/Arduino-FAQ/English/FAQ.md) first to see if the same question exists. If not, please create a [Github issue](https://github.com/VIEWESMART/VIEWE-FAQ/issues). We will get back to you as soon as possible.
