//https://github.com/NickChungVietNam/STEP_2_PHASE_DRIVE_ARDUINO
//http://arduino.vn/tutorial/1385-dieu-khien-module-dong-co-step-2-pha-va-thu-vien


#include "STEP_2_PHASE.h"

STEP_2_PHASE moto(5,6,7);//(A+,B+,ENABLE)
//set pin
void setup() {
moto.set(10,5);
}
void loop() {
  // quay thuận kim đồng hồ (tiến về trước) 90 step
  moto.go_front(90);
  delay(100);
  moto.go_back(90);// quay ngược 90 step
  delay(100);

// tự tìm đến step(x)
  moto.goto_step(60);
 delay(100);
  moto.goto_step(0);
  delay(100);

// quay thuận 20 step
  moto.step(20);
  delay(100);
  moto.step(-20);// quay ngược 20 step
  delay(100);
}
// động cơ di chuyển 1 bước 1
// 1 bước =1/4 vòng
/*
set(time_level,time_delay);

Cài đặt thời gian xung điều khiển (momen và nhiệt độ)  và thời gian delay ( làm chậm) 
go_front(unsigned long  n_step); 
Đi về trước n step (quay cùng chiều kim đồng hồ)
 go_back (unsigned long n_step);
Đi lùi về sau  n bước (quay ngược chiều kim đồng hồ)
 
long get_step();
 Sử dụng một biến đếm là STEP khi cho moto quay thuận 1 step thì biến đếm cộng thêm 1, khi cho moto quay nghịch 1 step thì biến đếm trừ đi  1.
set_zero();
Gọi hàm này để đặt biến đếm STEP là 0. 
goto_step (step); 
Tự động đi đến STEP x, với goto_step(0) là vị trí bắt đàu khởi động. (Các bạn nên cho con trượt về vị trí ban đầu trước khi khởi động arduino)

step( long n_step);
n_step dương : tiến về phía trước n step
n_step âm: lùi về sau n_step
  TWO_MOTORS.goto_xy(STEP_2_PHASE &moto_x, long x_step, STEP_2_PHASE &moto_y, long y_step);
 Điều khiển cùng lúc 2 moto.


*/