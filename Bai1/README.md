FreeRTOS STM32F103 – LED Blink & Alert

Chương trình sử dụng FreeRTOS trên STM32F103C8T6 gồm 2 nhiệm vụ:

LED nháy tại chân PA5 mỗi 1 giây

Khi nhấn nút tại chân PC13 thì LED cảnh báo tại PA6 sáng trong 2 giây

Sử dụng Queue và Semaphore để truyền tín hiệu từ ngắt sang Task xử lý.
Ngắt sử dụng EXTI13 để phát hiện nút nhấn.

Chân sử dụng:

PA5: LED nháy

PA6: LED cảnh báo

PC13: Nút nhấn

Yêu cầu phần cứng:

Blue Pill STM32F103C8T6

2 LED và điện trở hạn dòng

Nút nhấn PC13 trên board

Yêu cầu phần mềm:

Keil uVision hoặc STM32CubeIDE

FreeRTOS và thư viện Standard Peripheral Library

Cách hoạt động:

Chạy chương trình → LED PA5 nháy liên tục

Khi nhấn nút PC13 → LED PA6 sáng 2 giây rồi tắt
