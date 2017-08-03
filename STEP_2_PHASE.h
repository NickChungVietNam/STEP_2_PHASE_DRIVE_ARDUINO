



/* THƯ VIỆN ĐIỀU KHIỂN ĐỘNG CƠ 2 PHA ( động cơ step 2 cuộn dây trong máy DVD/ VCD)
/Thư viện được nghiên cứu và viết bởi tác giả:
Phùng Thái Sơn-Hà Nam. Bản quyền code thuộc Thái Sơn, code được chia sẻ với tất cả mọi người như một
nỗ lực đem đến những kiến thức bổ ích tới cộng đồng, được cộng đồng đón nhận và tiếp tục xây dựng lên 
những tầm cao mới. Vì một đất nước phát triển. 
Ngày hoàn thành : 26/12/2016
Trang web: Code được up và chia sẻ lần đầu tại trang web : arduino.vn

//https://github.com/NickChungVietNam/STEP_2_PHASE_DRIVE_ARDUINO
//http://arduino.vn/tutorial/1385-dieu-khien-module-dong-co-step-2-pha-va-thu-vien


Các bạn hãy đọc bài viết hướng dẫn của mình trên trang arduino.vn về động cơ 2 pha để biết cách sử dụng.
Thư viện đi kèm với tệp hướng dẫn WORD.


*/


class STEP_2_PHASE{
 public: 
 STEP_2_PHASE(byte pha_a1,byte  pha_a2, byte pha_b1,byte  pha_b2){
  // chọn kiểu nối dây
// 4 dây: sử dụng 4 dây điều khiển trực tiếp 4 đầu vào input
  chon_kieu_noi_day=4;// sử dụng 4 dây
  pha_A1=pha_a1;
  pha_A2=pha_a2;
  pha_B1=pha_b1;
  pha_B2=pha_b2;

  pinMode(pha_A1,OUTPUT);
  pinMode(pha_B1,OUTPUT);
  pinMode(pha_A2,OUTPUT);
  pinMode(pha_B2,OUTPUT);
  Step_Truoc_Do=1;//1,2,3,4
set_zero();
 }

 STEP_2_PHASE(byte pha_a1,byte  pha_b1, byte enable){
  // chọn kiểu nối dây
// 3 dây: 2 dây điều khiển input, 1 dây điều khiển chân EN (enable), sử dụng cổng NOT để điều khiển hai đầu input còn lại

  chon_kieu_noi_day=3;// sử dụng 3 dây
  pha_A1=pha_a1;
  pha_B1=pha_b1;
ENABLE=enable;

  pinMode(pha_A1,OUTPUT);
  pinMode(pha_B1,OUTPUT);
  pinMode(ENABLE,OUTPUT);

  Step_Truoc_Do=1;//1,2,3,4
set_zero();
 }


 STEP_2_PHASE(){
 }
void set_zero(){


  Step_hien_tai=0;
}

 void set(unsigned int time_level=5, unsigned int time_delay=0){
  TIME_LEVEL=time_level;
  TIME_DELAY=time_delay;
 }



 void go_back( unsigned long step_to_move){
  // quay ngược
// nếu step trước đó là 4 thì phải bắt đầu từ 3,
//nếu step trước đó là 3 thì bắt đầu từ 2
// nếu trước đó là 2 -> bắt đầu từ 1
// trước đó là 1->  bắt đàu từ 4 
unsigned long  step_move=0;

switch (Step_Truoc_Do){
  case 4:
  goto BAT_DAU_3_nguoc; break;
  case 3:
  goto BAT_DAU_2_nguoc; break;
  case 2:
  goto BAT_DAU_1_nguoc; break;
  case 1:
  goto BAT_DAU_4_nguoc; break;
  
  default:
  goto BAT_DAU_1_nguoc; break;
}
while (true){

// mỗi step là 1/4 vòng.  4 step=1 vòng.


BAT_DAU_4_nguoc:
  //step4
  //A-,B+
  set_step(4);
  
step_move++;

 Step_hien_tai--;
gioi_han_step();
if( step_move==step_to_move){
  
  
Step_Truoc_Do=4;// lưu lại step cũ 
break;}

BAT_DAU_3_nguoc:
  //step3
  //A-,B-
 
  set_step(3);
  
step_move++; 

 Step_hien_tai--;
gioi_han_step();
if( step_move==step_to_move){ 
  
Step_Truoc_Do=3;// lưu lại step cũ 
break;}


BAT_DAU_2_nguoc:

  //step2
  //A+,B-
  
  set_step(2);
  
step_move++;

 Step_hien_tai--;
gioi_han_step();
if( step_move==step_to_move){
  
Step_Truoc_Do=2;// lưu lại step cũ 
break;}


 
BAT_DAU_1_nguoc:
  //step1
  //A+,B+
  set_step(1);
step_move++; 

 Step_hien_tai--;
gioi_han_step();
if( step_move==step_to_move){
Step_Truoc_Do=1;// lưu lại step cũ 
break;}




}
  
 }
 
 void go_front( unsigned long step_to_move){
// nếu step trước đó là 1 thì phải bắt đầu từ 2,
//nếu step trước đó là 2 thì bắt đầu từ 3
// nếu trước đó là 3 -> bắt đầu từ 4
// trước đó là 4->  bắt đàu từ 1
unsigned long  step_move=0;

switch (Step_Truoc_Do){
  case 1:
  goto BAT_DAU_2; break;
  case 2:
  goto BAT_DAU_3; break;
  case 3:
  goto BAT_DAU_4; 
  break;
  case 4:
  goto BAT_DAU_1; break;
  default:
  goto BAT_DAU_1; break;
}
while (true){

// mỗi step là 1/4 vòng.  4 step=1 vòng.
BAT_DAU_1:
  //step1
  //A+,B+

  set_step(1);
  
step_move++;

 Step_hien_tai++;
gioi_han_step();
if( step_move==step_to_move){
Step_Truoc_Do=1;// lưu lại step cũ 
break;}

BAT_DAU_2:

  //step2
  //A+,B-

  set_step(2);
  
step_move++; 

 Step_hien_tai++;
gioi_han_step();
if( step_move==step_to_move){
  
Step_Truoc_Do=2;// lưu lại step cũ 
break;}

BAT_DAU_3:
  //step3
  //A-,B-

  set_step(3);
  
step_move++;

 Step_hien_tai++;
gioi_han_step();
if( step_move==step_to_move){ 
  
Step_Truoc_Do=3;// lưu lại step cũ 
break;}


BAT_DAU_4:
  //step4
  //A-,B+ 

  set_step(4);
  
step_move++; 

 Step_hien_tai++;
gioi_han_step();
if( step_move==step_to_move){
  
  
Step_Truoc_Do=4;// lưu lại step cũ 
break;}


}
  
 }

 void goto_step( long Step_muon_toi){
  
  long hien_tai;
 hien_tai=Step_hien_tai;// gọi lại 
 
if(Step_muon_toi<hien_tai){
while(Step_muon_toi<hien_tai){
  
  hien_tai--;
  go_back(1);
  
  if(Step_muon_toi==hien_tai){
    return;// thoát ngay
  }
}
}
  if(Step_muon_toi>hien_tai){
while(Step_muon_toi>hien_tai){
  hien_tai++;
  go_front(1);
  if(Step_muon_toi==hien_tai){
    return;// thoát ngay
  }
}

}
 }

 long get_step(){
  return Step_hien_tai;
 }

 void step( long step){

  if(step<0){
    step=(-1)*step;
    go_back(step);
    return;
  }else{
    go_front(step);
    return;
  }
 }

//////////////////////////////////////////////////////////////////////////////////////
///////////////////// VẼ cnc PHẦN CỨNG//////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
 // Thực ra, trước kia mình đã viết đoạn code này để vẽ đường thẳng cho máy CNC
 // Thấy việc điều khiển đồng bộ khá hay nên mình cũng gộp luôn vào thư viện này


void goto_xy(STEP_2_PHASE &moto_x, long x_b, STEP_2_PHASE &moto_y, long y_b){
  // vẽ đoạn thẳng AB
// x<y
//x=2, y=4
long x_a=moto_x.get_step();//Serial.print("x_cu="); Serial.println(x_cu);
long y_a=moto_y.get_step(); //Serial.print("y_cu="); Serial.println(y_cu);


// lấy lại tọa độ điểm cũ
long denta_x=x_b-x_a;
long denta_y=y_b-y_a;
// giải phương trình đường thẳng y=ax+b
float a,b;
a=(float)denta_y/denta_x;
b=float(-x_a)*a+float(y_a);
// vẽ điểm (x, Round(y));
/*
 * Khi x = xa = 5: => y = ax+b = 4;  Vẽ điểm (5,4) 
 * Khi x = 6:   => y = 23/5 = 4.6;  Vẽ điểm (6,5) 
 * Khi x = 7:  => y = 26/5 = 5.2;  Vẽ điểm (7,5) 
 * Khi x = 8:  => y = 29/5 = 5.8;  Vẽ điểm (8,6) 
 * Khi x = 9:  => y = 32/5 = 6.4;  Vẽ điểm (9,6) 
 * Khi x = 10:  => y = 7;   Vẽ điểm (10,7) 
 */

 //nếu |denta_y|<=|denta_x| 
 if( abs(denta_y)<=abs(denta_x)){
  long x_moi=x_a;
  long y_moi=0;
  while(x_moi!=x_b){
    // x_moi ban đầu = x_a
    //tìm y
    y_moi=Round( a*(float)x_moi+b);
    moto_x.goto_step(x_moi);
    moto_y.goto_step(y_moi);
    
    //tìm x
    if(x_moi<x_b){
      x_moi+=1;
    }else{
      x_moi-=1;
    }
  }

 }else{


  long y_moi=y_a;
  long x_moi=0;
  while(y_moi!=y_b){
    //tìm x
    x_moi=Round( ((float)y_moi-b)/a);
    moto_x.goto_step(x_moi);
    moto_y.goto_step(y_moi);
    
    //tìm y
    if(y_moi<y_b){
      y_moi+=1;
    }else{
      y_moi-=1;
    }
  }


  
 }
}







private:

   byte pha_A1,  pha_A2, pha_B1, pha_B2, ENABLE;

   byte Step_Truoc_Do;// 1,2,3,4 lưu lại trạng thái của step trước đó
    long Step_hien_tai;// dùng để quay về vị trí cần thiết
   unsigned int TIME_LEVEL, TIME_DELAY;
byte chon_kieu_noi_day;
// có 2 kiểu nối dây:
// 4 dây: sử dụng 4 dây điều khiển trực tiếp 4 đầu vào input
// 3 dây: 2 dây điều khiển input, 1 dây điều khiển chân EN (enable), sử dụng cổng NOT để điều khiển hai đầu input còn lại


long Round( float so_can_lam_tron){
long lay_so_nguyen=long( so_can_lam_tron);// lấy phần trước dấu phảy
// giả sử so_can_lam_tron=8.1 -> lay_so_nguyen=8;
// giả sử so_can_lam_tron=8.6 -> lay_so_nguyen=8;
 float F=so_can_lam_tron-(float)lay_so_nguyen;
 // F là số sau dấu phảy
 if(F>=0.5){
  return lay_so_nguyen+1;// làm tròn lên
 }else{
  return lay_so_nguyen;// làm tròn xuốngr
 }

// giả sử so_can_lam_tron=8.1 -> trả về 8;
// giả sử so_can_lam_tron=8.6 -> trả về 9;
  
}
void set_step( byte step){
if(this->chon_kieu_noi_day==3){
//kiểu 3 dây


  switch(step){


case 1:
set_bit_3_day(1,1);
break;

case 2:

set_bit_3_day(1,0);
break;

case 3:

set_bit_3_day(0,0);
break;

case 4:

set_bit_3_day(0,1);
break;

  }

}else if( this->chon_kieu_noi_day==4){
 switch(step){


case 1:
set_bit_4_day( 1,1);
break;

case 2:

set_bit_4_day( 1,0 );
break;

case 3:

set_bit_4_day( 0,0 );
break;

case 4:

set_bit_4_day( 0,1 );
break;

  }
}
}


void set_bit_3_day( bool bit_pha_A1, bool bit_pha_B1){
// cấp xung kích từ  
  
// cho 2 xung vào chân input trước
digitalWrite(pha_A1,bit_pha_A1);
  digitalWrite(pha_B1,bit_pha_B1);
  /*

  digitalWrite(pha_A2,!bit_pha_A1);
  digitalWrite(pha_B2,!bit_pha_B1);

  // hai cổng còn lại sử dụng cổng NOT bằng transiztor để điều khiển

  */
// kéo enable sau
  digitalWrite(ENABLE,1);
// thời gian của xung kích
  delay(TIME_LEVEL);
// tắt xung kích
  digitalWrite(ENABLE,0);
  // thời gian trễ
  delay(TIME_DELAY);
}
void set_bit_4_day(  bool bit_pha_A1, bool bit_pha_B1 ){
// cấp xung kích từ  
digitalWrite(pha_A1,bit_pha_A1);
  digitalWrite(pha_A2,!bit_pha_A1);
  digitalWrite(pha_B1,bit_pha_B1);
  digitalWrite(pha_B2,!bit_pha_B1);
// thời gian của xung kích
  delay(TIME_LEVEL);
// tắt xung kích
digitalWrite(pha_A1,0);
  digitalWrite(pha_A2,0);
  digitalWrite(pha_B1,0);
  digitalWrite(pha_B2,0);
  // thời gian trễ
  delay(TIME_DELAY);
}
void gioi_han_step(){
 
  //Serial.print("Step_hien_tai:"); Serial.println(Step_hien_tai);
  
  if(Step_hien_tai>2147483646){
    // chống tràn số
    Step_hien_tai=2147483646;
  }
  // chống tràn số
   if(Step_hien_tai<(-2147483646)){
   Step_hien_tai=(-2147483646);
  }
}
};

STEP_2_PHASE TWO_MOTORS;