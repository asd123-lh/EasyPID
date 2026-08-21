# mini

这是一个基于 STM32F103RCT6 的嵌入式控制工程，由 STM32CubeMX 生成基础代码，使用 HAL 库开发。项目主要实现七路循迹传感器数据读取、PID 偏差调节，以及左右 MG513 电机 PWM 控制。

## 项目简介

- 主控芯片：STM32F103RCT6
- 开发框架：STM32CubeMX + STM32 HAL
- 主要外设：GPIO、TIM2、TIM4、TIM6、USART2
- 开发环境：Keil MDK-ARM，也保留了 IAR EWARM 工程文件

## 项目架构

```text
mini/
├── Core/
│   ├── Inc/                 # 用户头文件和 CubeMX 生成的外设头文件
│   │   ├── main.h
│   │   ├── gpio.h
│   │   ├── tim.h
│   │   ├── usart.h
│   │   ├── Mg513.h          # MG513 电机控制接口
│   │   ├── pid.h            # PID 控制相关声明
│   │   └── sevenway.h       # 七路循迹传感器相关声明
│   └── Src/                 # 主程序和功能实现
│       ├── main.c           # 程序入口，初始化外设并启动控制流程
│       ├── Mg513.c          # 左右电机 PWM 输出控制
│       ├── pid.c            # TIM6 定时中断中的 PID 调节逻辑
│       ├── sevenway.c       # USART2 读取七路传感器并计算偏差
│       ├── gpio.c
│       ├── tim.c
│       └── usart.c
├── Drivers/                 # STM32 HAL 库和 CMSIS 驱动
├── MDK-ARM/                 # Keil MDK 工程文件和编译输出
├── EWARM/                   # IAR EWARM 工程文件
├── mini.ioc                 # STM32CubeMX 配置文件
└── mini.7z                  # 项目压缩包
```

## 核心逻辑

1. `main.c` 初始化 GPIO、定时器、串口等外设。
2. `SevenWay_UART_Init()` 通过 USART2 启动七路传感器通信。
3. `sevenway.c` 在串口接收回调中解析传感器数据，并计算当前偏差 `error`。
4. `pid.c` 使用 TIM6 定时中断周期性计算 PID 输出。
5. `Mg513.c` 根据 PID 输出调整左右电机 PWM，实现方向修正。

## 编译和下载

推荐使用 Keil MDK-ARM 打开工程：

```text
MDK-ARM/mini.uvprojx
```

打开后可直接编译，并通过 ST-Link 或其他调试器下载到 STM32F103RCT6 开发板。

如果需要修改引脚或外设配置，可以使用 STM32CubeMX 打开：

```text
mini.ioc
```

修改后重新生成代码，再回到 Keil 中编译。

## 主要文件说明

- `Core/Src/main.c`：程序入口和外设初始化
- `Core/Src/sevenway.c`：七路循迹传感器数据读取和偏差计算
- `Core/Src/pid.c`：PID 控制逻辑
- `Core/Src/Mg513.c`：左右电机控制
- `Core/Src/tim.c`：TIM2、TIM4 PWM 以及 TIM6 定时器配置
- `Core/Src/usart.c`：USART2 串口配置

## 注意事项

- 本工程使用 STM32Cube FW_F1 V1.8.7。
- 当前工程目标工具链为 MDK-ARM V5.32。
- `MDK-ARM/mini/` 目录中包含编译生成文件，上传代码仓库时可以按需要忽略。
