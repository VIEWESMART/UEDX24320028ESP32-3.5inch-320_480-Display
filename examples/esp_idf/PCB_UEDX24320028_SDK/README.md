# VIEWE SPI 显示屏 SDK 使用说明

本工程面向 **VIEWE / PCB板 UEDX24320028E-WB-A 系列 ESP32-S3 带屏模组**，示例包含 LCD 初始化、触摸（CST816S）以及 LVGL Demo。

适合刚拿到板子、第一次编译烧录的初学者。**最重要的一步是：按你下单的型号，在代码里选对屏幕。**

---

## 1. 环境准备

1. 安装 [ESP-IDF](https://docs.espressif.com/projects/esp-idf/zh_CN/latest/esp32s3/get-started/index.html)（建议 **v5.1 及以上**，本工程已在 **v5.5.4** 验证）。
2. 目标芯片选择：**ESP32-S3**。
3. 推荐使用 **VS Code + Espressif IDF 插件**，或 ESP-IDF 自带终端。

确认环境可用：

```bash
idf.py --version
```

---

## 2. 根据下单型号选择屏幕（必做）

打开文件：

```text
main/board.h
```

找到下面这几行宏（只能启用其中一个）：

```c
#define VIEWE_DISPLAY_240_320_2_4    0  // 2.4inch Display
#define VIEWE_DISPLAY_240_320_2_8    0  // 2.8inch Display
#define VIEWE_DISPLAY_240_320_3_5    0  // 3.5inch low resolution Display
#define VIEWE_DISPLAY_320_480_3_5    1  // 3.5inch high resolution Display (320*480)
```

### 型号对照表

| 下单型号 | 分辨率 / 尺寸 | 需要启用的宏 |
| -------- | ------------- | ------------ |
| **UEDX24320024E-WB-A** | 240×320 / 2.4 寸 | `VIEWE_DISPLAY_240_320_2_4` |
| **UEDX24320028E-WB-A** | 240×320 / 2.8 寸 | `VIEWE_DISPLAY_240_320_2_8` |
| **UEDX24320035E-WB-A** | 240×320 / 3.5 寸（低分辨率） | `VIEWE_DISPLAY_240_320_3_5` |
| **UEDX32480035E-WB-A** | 320×480 / 3.5 寸（高分辨率） | `VIEWE_DISPLAY_320_480_3_5` |

### 修改方法

把你对应型号那一行设为 `1`，**其余全部设为 `0`**。

示例：如果你买的是 **UEDX24320028E-WB-A（2.8 寸）**，应写成：

```c
#define VIEWE_DISPLAY_240_320_2_4    0
#define VIEWE_DISPLAY_240_320_2_8    1
#define VIEWE_DISPLAY_240_320_3_5    0
#define VIEWE_DISPLAY_320_480_3_5    0
```

示例：如果你买的是 **UEDX32480035E-WB-A（3.5 寸 320×480）**，应写成：

```c
#define VIEWE_DISPLAY_240_320_2_4    0
#define VIEWE_DISPLAY_240_320_2_8    0
#define VIEWE_DISPLAY_240_320_3_5    0
#define VIEWE_DISPLAY_320_480_3_5    1
```

> 注意：
>
> - **只能选一个**，多选或一个都不选时，编译会直接报错提示。
> - 选错型号常见现象：花屏、白屏、触摸错位、画面倒置等。

---

## 3. 编译、烧录、查看串口

在工程根目录执行（把 `COMx` 换成你电脑上的串口号）：

```bash
idf.py set-target esp32s3
idf.py build
idf.py -p COMx flash monitor
```

Windows 下串口一般是 `COM3`、`COM5` 这类；可在设备管理器里查看。

退出串口监视器：`Ctrl + ]`

首次编译可能较慢，因为会下载 `managed_components` 依赖组件。

---

## 4. 工程结构（初学者快速了解）

```text
PCB_UEDX24320028_SDK/
├── main/
│   ├── board.h      # 屏幕型号选择、引脚与分辨率配置（优先改这里）
│   ├── board.c      # LCD / 触摸 / LVGL 初始化
│   └── main.c       # 应用入口（蜂鸣器、RGB、LVGL Demo 等）
├── components/      # 本地组件（如触摸驱动）
├── managed_components/  # 由组件管理器自动下载的依赖
├── CMakeLists.txt
└── README.md
```

---

## 5. 常见问题

### 编译报错：只能选择一个屏幕型号

说明 `board.h` 里同时开了多个 `VIEWE_DISPLAY_*`，或全部是 `0`。按第 2 节重新设置。

### 屏幕不显示 / 花屏

1. 确认型号与宏是否一一对应。
2. 重新完整编译并烧录：`idf.py fullclean` 后再 `idf.py build flash`。
3. 检查供电与 USB 线是否稳定。

### 触摸无效或坐标不对

先确认屏幕宏已选对；不同尺寸分辨率不同，分辨率选错会导致触摸映射异常。

### 烧录失败

- 确认串口号正确。
- 尝试按住板子 **BOOT** 再点烧录，或切换 USB 口/数据线。
- 关闭占用串口的其他软件（串口助手等）。

---

## 6. 技术支持

本 SDK 由 **Shenzhen VIEWE TECHNOLOGY Co., LTD** 提供示例代码。

如需进一步定制 UI，可在 `main/main.c` 中替换 LVGL Demo，自行调用 LVGL API 绘制界面。

祝调试顺利。
