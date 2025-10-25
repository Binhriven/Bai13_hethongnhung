FreeRTOS STM32F103 – LED Blink & Alert Button Interrupt

 📌 Mô tả dự án
Project sử dụng *FreeRTOS** trên **STM32F103C8T6** gồm 2 tác vụ chính:
✅ LED Blink Task
- Nhấp nháy LED (PA5) mỗi 1 giây

🚨 Alert Task
- Khi nhấn nút (PC13 - nút User trên board Blue Pill)
- Gửi tín hiệu qua **Queue** và **Semaphore**
- LED cảnh báo (PA6) sáng 2 giây rồi tắt

Ngoài ra sử dụng **External Interrupt (EXTI13)** để bắt sự kiện nhấn nút.

🧩 Sử dụng tài nguyên FreeRTOS
| Thành phần | Mục đích |
|----------|----------|
| Task | LED Blink Task & Alert Task |
| Queue | Truyền lệnh từ ISR → Task xử lý |
| Binary Semaphore | Đồng bộ hóa ISR → Task |
| ISR | Xử lý ngắt nút nhấn |

 📍 Sơ đồ chân
| Chân | Chức năng |
|------|-----------|
| PA5 | LED blink |
| PA6 | LED alert |
| PC13 | Button input |

✅ Yêu cầu phần cứng
- STM32F103C8T6 (Blue Pill)
- 2 LED 
- Nút nhấn nối PC13

✅ Yêu cầu phần mềm
- Keil uVision / STM32CubeIDE / PlatformIO
- FreeRTOS + Standard Peripheral Library (SPL)

## 🛠 Hướng dẫn build
1. Clone project
2. Import vào IDE
3. Compile và flash lên MCU
4. Quan sát:
   - ✅ PA5 nháy định kỳ
   - ✅ Nhấn nút → PA6 sáng 2 giây rồi tắt
