FreeRTOS STM32F103 – UART Mutex Protection

📌 Mô tả dự án

Project sử dụng FreeRTOS trên STM32F103C8T6 gồm 2 tác vụ gửi dữ liệu qua UART1:

✅ Task A

Gửi chuỗi: "HELLO BINH\r\n"

Chu kỳ: 100ms

✅ Task B

Gửi chuỗi: "hello binh\r\n"

Chu kỳ: 150ms

Để tránh xung đột truy cập UART giữa các Task, chương trình sử dụng Mutex (Binary Semaphore kiểu Mutex) bảo vệ tài nguyên chung.

🧩 Tài nguyên FreeRTOS sử dụng

Thành phần	Chức năng

Task	Gửi dữ liệu UART song song

Mutex (SemaphoreHandle_t)	Bảo vệ tài nguyên UART

vTaskDelay	Tạo chu kỳ chạy Task

Scheduler	Lập lịch CPU cho 2 Task

📍 Sơ đồ chân UART1

Chân	Chức năng

PA9	USART1_TX

PA10	USART1_RX

GND	Chung GND với USB-TTL

Kết nối:

PA9  → RX USB-TTL

PA10 → TX USB-TTL

GND → GND


🔌 Yêu cầu phần cứng

STM32F103C8T6 (Blue Pill)

USB–TTL để Debug UART

Dây nối UART

🛠️ Yêu cầu phần mềm

STM32CubeIDE / Keil uVision / PlatformIO

FreeRTOS + STM32 Standard Peripheral Library


✅ Kết luận kỹ thuật

Giải pháp	Kết quả

Không dùng Mutex	Dữ liệu UART lẫn nhau

Dùng Mutex	Gửi tuần tự, đúng nội dung từng chuỗi

Mutex bảo đảm chỉ một Task được ghi UART tại một thời điểm → tránh xung đột tài nguyên.
