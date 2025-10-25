FreeRTOS STM32F103 – UART 2 Task Print
📌 Mô tả dự án

Project sử dụng FreeRTOS trên STM32F103C8T6 gồm 2 tác vụ gửi dữ liệu qua UART1:

✅ Task A

Gửi chuỗi "AAAAA\r\n"

Chu kỳ 50ms

✅ Task B

Gửi chuỗi "bbbbb\r\n"

Chu kỳ 70ms

Hai Task truy cập chung UART → dữ liệu sẽ xen kẽ khi hiển thị trên Serial Terminal.

🧩 Sử dụng FreeRTOS

Thành phần	Mục đích

Task	Chạy song song hai chức năng

vTaskDelay	Tạo chu kỳ gửi dữ liệu

Scheduler	Quản lý phân chia CPU cho task

📍 Sơ đồ chân UART1

Chân	Chức năng

PA9	USART1_TX

PA10	USART1_RX

GND	Chung GND với USB-TTL

Kết nối:

STM32 PA9  → RX USB-TTL

STM32 PA10 → TX USB-TTL

STM32 GND → GND USB-TTL


🔌 Yêu cầu phần cứng

STM32F103C8T6 (Blue Pill)

Bộ chuyển USB-TTL

Dây nối TX/RX


🛠️ Yêu cầu phần mềm

Keil / STM32CubeIDE / PlatformIO

FreeRTOS + STM32 Standard Peripheral Library


🚀 Nâng cấp thêm

Dùng Mutex bảo vệ UART → tránh tranh chấp tài nguyên

Đổi độ ưu tiên Task để thử thay đổi tần suất xen kẽ
