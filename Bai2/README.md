⚙️ FreeRTOS STM32F103 – 2 Task UART
1️⃣ Giới thiệu

Dự án sử dụng FreeRTOS trên STM32F103C8T6 với 2 Task cùng gửi dữ liệu qua UART1.

✅ Mỗi Task gửi một chuỗi riêng → Quan sát dữ liệu xen kẽ trên Serial Monitor.

2️⃣ Chức năng từng Task
Task	Chuỗi gửi	Chu kỳ gửi
Task A	AAAAA\r\n	50 ms
Task B	bbbbb\r\n	70 ms
3️⃣ Sơ đồ chân UART1 sử dụng
Chân STM32	Chức năng
PA9	USART1_TX
PA10	USART1_RX
GND	GND chung với USB–TTL

Kết nối với USB–UART như sau:

STM32 PA9  ---->  RX USB-TTL
STM32 PA10 ---->  TX USB-TTL
STM32 GND ---->  GND USB-TTL


Baudrate: 9600 8N1

4️⃣ Thư viện sử dụng

stm32f10x.h

stm32f10x_usart.h

FreeRTOS.h

task.h

5️⃣ Luồng hoạt động hệ thống
+--------------+         +--------------+
|   Task A     |         |   Task B     |
| UART Print   |         | UART Print   |
| "AAAAA"      |         | "bbbbb"      |
+------+-------+         +-------+------+
       |                         |
       +-----------+-------------+
                   |
                UART1 TX
                   |
               Serial Monitor

6️⃣ Hướng phát triển

✅ Thêm Mutex bảo vệ tài nguyên UART

✅ Thêm Task đọc UART

✅ Mở rộng debug qua Queue hoặc StreamBuffer
