//https://github.com/NickChungVietNam/STEP_2_PHASE_DRIVE_ARDUINO
//http://arduino.vn/tutorial/1385-dieu-khien-module-dong-co-step-2-pha-va-thu-vien




#include "STEP_2_PHASE.h"

STEP_2_PHASE moto(5,6,7);//(A+,B+,ENABLE)
//set pin
void setup() {
moto.set(10,5);
Serial.begin(9600);
moto.set_zero();
}
void loop() {
  // quay thuận kim đồng hồ (tiến về trước) 90 step
  moto.go_front(90);
  Serial.println( moto.get_step());// 
  delay(100);
  moto.go_back(90);// quay ngược 90 step
  delay(100);
  Serial.println( moto.get_step());

// tự tìm đến step(x)
  moto.goto_step(60);
  Serial.println( moto.get_step());
 delay(100);
  moto.goto_step(0);
  Serial.println( moto.get_step());
  delay(100);

}

/*
long get_step();
 Sử dụng một biến đếm là STEP khi cho moto quay thuận 1 step thì biến đếm cộng thêm 1, khi cho moto quay nghịch 1 step thì biến đếm trừ đi  1.
set_zero();
Gọi hàm này để đặt biến đếm STEP là 0. 

*/