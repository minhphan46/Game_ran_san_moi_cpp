#include <iostream>
#include "ran_san_moi.h"
using namespace std;
//===========chon che do=================================
#define MAX 100
#define speed 70
int sl = 10;// do dai con ran ban dau
int diem = 0;// diem so ban dau
char qua = '@';
char dau_ran = '0';
char than_ran = 'o';
//-----------------khai bao ham--------------------------
void ve_tuong();
void khoi_tao_ran(int toadox[], int toadoy[]);
void ve_ran(int toadox[], int toadoy[]);
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int &xqua, int &yqua);
void them(int a[], int x);
void xoa(int a[], int vt);
void xoa_du_lieu_cu(int toadox[], int toadoy[]);
bool kt_ran_cham_tuong(int x0, int y0);
bool kt_ran_cham_duoi(int toadox[], int toadoy[]);
bool kt_ran(int toadox[], int toadoy[]);
void tao_qua(int &xqua,int &yqua, int toadox[], int toadoy[]);
bool kt_ran_de_qua(int toadox[], int toadoy[], int xqua, int yqua);
bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0);
void diem_so( int diem);
//----------------ham main xu ly-------------------------
int main()
{
    bool gameover = false;
    int toadox[MAX], toadoy[MAX];
    ve_tuong();
    khoi_tao_ran(toadox, toadoy);
    ve_ran(toadox, toadoy);
    int color = 1; //bien mau
    int x=50, y=13; // vi tri luc dau cua con ran
    int check = 2;
    // 0 là đi xuống
    // 1 là đi lên
    // 2 là qua phai
    // 3 là qua trai
    //tao qua
    srand(time(NULL));
    int xqua=0, yqua=0;
    tao_qua(xqua, yqua, toadox, toadoy);
    int mau_ran=0;
//========================================================
    // thuc hien di chuyen
    while( gameover == false){
        xoa_du_lieu_cu(toadox, toadoy);
        ShowCur( false);
        // điều khiển
        if(_kbhit()){
            char kitu = _getch();
            if( kitu == -32){
                kitu = _getch();
                if( kitu == 72 && check != 0) check = 1;//di len
                if( kitu == 80 && check != 1) check = 0;//di xuong
                if( kitu == 75 && check != 2) check = 3;//qua trai
                if( kitu == 77 && check != 3) check = 2;//qua phai
            }
            if( kitu == 'w' && check != 0) check = 1;
            if( kitu == 's' && check != 1) check = 0;
            if( kitu == 'd' && check != 3) check = 2;
            if( kitu == 'a' && check != 2) check = 3;
        }
        if( check == 0 ) y++;
        if( check == 1 ) y--;
        if( check == 2 ) x++;
        if( check == 3 ) x--;
        //con ran chay
        SetColor(mau_ran);
        xu_ly_ran(toadox, toadoy, x, y, xqua, yqua);
        mau_ran++;
        if(mau_ran == 15) mau_ran = 0;
        SetColor(7);
        //=====kiem tra=======
        gameover = kt_ran(toadox, toadoy);
        //=====điểm=========
        diem_so(diem);
        Sleep(speed);
    }
    gotoXY(50,13);
    cout << "GAME OVER";
    _getch();
    return 0;
}
//=====================================================
void ve_tuong_tren()
{
    int x=10, y=1;
    while( x <= 100){
        gotoXY( x, y);
        cout << "=";
        x++;
    }
}
void ve_tuong_duoi()
{
    int x=10, y=26;
    while( x <= 100){
        gotoXY( x, y);
        cout << "=";
        x++;
    }
}
void ve_tuong_trai()
{
    int x=10, y=1;
    while( y <= 26){
        gotoXY( x, y);
        cout << "|";
        y++;
    }
}
void ve_tuong_phai()
{
    int x=100, y=1;
    while( y <= 26){
        gotoXY( x, y);
        cout << "|";
        y++;
    }
}
void ve_tuong()
{
    SetColor(11);
    ve_tuong_tren();
    ve_tuong_duoi();
    ve_tuong_trai();
    ve_tuong_phai();
    SetColor(7);
}
void khoi_tao_ran(int toadox[], int toadoy[])
{
    int x = 50, y = 13;
    for( int i=0; i<sl; i++){
        toadox[i] = x;
        toadoy[i] = y;
        x--;
    }
}
void ve_ran(int toadox[], int toadoy[])
{
    for( int i=0; i<sl; i++){
        gotoXY( toadox[i], toadoy[i]);
        if( i == 0){
          cout << dau_ran;
        }
        else cout << than_ran;
    }
}
void xoa_du_lieu_cu(int toadox[], int toadoy[])
{
    for( int i=0; i<sl; i++){
        gotoXY( toadox[i], toadoy[i]);
          cout << " ";
    }
}
void xu_ly_ran(int toadox[], int toadoy[], int x, int y, int &xqua, int &yqua)
{
    // b1: thêm tọa độ mới vào đầu mảng
    them(toadox, x);
    them(toadoy, y);
    // b2: kiem tra ran an qua
    if( kt_ran_an_qua(xqua, yqua, toadox[0], toadoy[0]) == false){
        // b3: xoa toa do cuoi mang
        xoa(toadox, sl - 1);
        xoa(toadoy, sl - 1);
    }
    else{
      //b5:toa qua moi
        tao_qua(xqua, yqua, toadox, toadoy);
        diem++;
    }
    //b4: ve ran
    ve_ran(toadox, toadoy);

}
void them(int a[], int x)
{
    for( int i=sl; i>0; i--){
        a[i] = a[i-1];
    }
    a[0] = x;
    sl++;
}
void xoa(int a[], int vt)
{
    for( int i=vt; i<sl; i++){
        a[i] = a[i+1];
    }
    sl--;
}
bool kt_ran_cham_tuong(int x0, int y0)
{
    // ran cham tuong tren
    if( y0 == 1 && ( x0 >= 10 && y0 <=100)){
        return true;
    }
    // ran cham tuong duoi
    if( y0 == 26 && ( x0 >= 10 && y0 <=100)){
        return true;
    }
    // ran cham tuong trai
    if( x0 == 10 && ( y0 >= 1 && y0 <= 26)){
        return true;
    }
    // ran cham tuong phai
    if( x0 == 100 && ( y0 >= 1 && y0 <= 26)){
        return true;
    }
    return false;
}
bool kt_ran_cham_duoi(int toadox[], int toadoy[])
{
    for(int i = 1; i < sl; i++){
        if( (toadox[0] == toadox[i]) && ( toadoy[0] == toadoy[i])){
            return true;
        }
    }
    return false;
}
bool kt_ran(int toadox[], int toadoy[])
{
    bool kt1 = kt_ran_cham_duoi(toadox, toadoy);
    bool kt2 = kt_ran_cham_tuong(toadox[0], toadoy[0]);
    if( kt1 == true || kt2 == true ){
      return true;
    }
    return false;
}
void tao_qua(int &xqua,int &yqua, int toadox[], int toadoy[])
{

    do{
        xqua = rand()%(99-11+1)+11;
        yqua = rand()%(25-2+1)+2;
    }while (kt_ran_de_qua(toadox,toadoy,xqua,yqua) == true);
    gotoXY(xqua, yqua);
    int i=rand()%(15-1+1) +1;
    SetColor(i);
    cout << qua;
    SetColor(7);
}
bool kt_ran_de_qua(int toadox[], int toadoy[], int xqua, int yqua)
{
    for(int i = 0; i < sl; i++){
        if( (xqua == toadox[i]) && ( yqua == toadoy[i])){
            return true;
        }
    }
    return false;
}
bool kt_ran_an_qua(int xqua, int yqua, int x0, int y0)
{
    if( xqua == x0 && yqua == y0){
        return true;
    }
    return false;
}
void diem_so( int diem)
{
    gotoXY(105, 2);
    cout << "SOCCER";
    gotoXY(104,3);
    cout << "========";
    gotoXY(107,4);
    cout << diem;
}


