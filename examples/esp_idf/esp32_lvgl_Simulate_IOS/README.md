|支持的目标 |ESP32 系列 |ESP32-C2 系列 |ESP32-C3 系列 |ESP32-S2 系列 |ESP32-S3 系列 |
|----------------- |----- |-------- |-------- |-------- |-------- |

# _Sample project_

这是最简单的可构建示例。该示例由命令 'idf.py create-project' 使用
将项目复制到用户指定的路径并设置其名称。有关更多信息，请关注 [文档页面]（https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project）

## 如何使用示例
电量显示是接收其他芯片通过串口发送的电量。
首次开机联网后自动获取时间。
SD卡刷新需要存在如下文件夹
/music/
/nes/rom/

天气功能请修改components/weather/weather.c文件void weather_get_task(void *arg)函数中的key值为高德开放平台天气接口KEY值。
char *key = "1234567890abcdefghijklmnopqrstuvwxyz";

## 示例文件夹内容

项目包含一个 C 语言 [main.c]（main/main.c） 的源文件。该文件位于main文件夹。