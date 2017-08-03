//https://github.com/NickChungVietNam/STEP_2_PHASE_DRIVE_ARDUINO
//http://arduino.vn/tutorial/1385-dieu-khien-module-dong-co-step-2-pha-va-thu-vien




#include "STEP_2_PHASE.h"
//(A+,B+,ENABLE)
STEP_2_PHASE moto_y(8,9,10);// pha A(8), pha B(9), ENABLE 10
STEP_2_PHASE moto_x(5,6,7);//A(5) , B(6), ENABLE 7
//set pin
void setup() {
moto_x.set(5,10);
moto_y.set(10,10);
}
void loop() {

//vẽ tam giác
  TWO_MOTORS.goto_xy(moto_x, 50, moto_y, 50);
  TWO_MOTORS.goto_xy(moto_x, 100, moto_y, 0);
  TWO_MOTORS.goto_xy(moto_x, 0, moto_y, 0);
}
//điều khiển cùng lúc 2 moto
// TWO_MOTORS.goto_xy(STEP_2_PHASE &moto_x, long x_step, STEP_2_PHASE &moto_y, long y_step): 
// chú ý: truy cập phương thức với tên : " TWO_MOTORS"



