#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
#define LCD_RESET A4 

#define SWAP(a, b) {uint16_t tmp = a; a = b; b = tmp;}


#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <PeepLib.h>
#include <TouchScreen.h>

#define     RGB(r, g, b)                (((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3))
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define     DARKGRAY                      RGB(0x40, 0x40, 0x40)
#define     GRAY                        RGB(0x80, 0x80, 0x80)
#define     LIGHTGRAY                        RGB(0x120, 0x1200, 0x120)

uint8_t SwapXY = 0;
uint16_t TS_LEFT = 920;
uint16_t TS_RT  = 150;
uint16_t TS_TOP = 940;
uint16_t TS_BOT = 120;

String name = "Unknown controller";

uint16_t identifier;

uint8_t YP = A1;  
uint8_t XM = A2;  
uint8_t YM = 7;   
uint8_t XP = 6;   
uint16_t g_identifier;
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
TSPoint tp;
uint8_t Orientation = 0;

Peep *peep;

#define MINPRESSURE 20
#define MAXPRESSURE 1000
Button button1=Button("Button1",10,10,70,70,"MsgBox");
Button button2=Button("Button2",30,90,70,70,"Label");
Checkbox check=Checkbox("Check1",110,20,"Check");
Label label=Label("Label1",110,90,"Label");
MessageBox mb=MessageBox("Title","Hallo Welt",MSGBOX_WARNING,BTN_OK);
Input input=Input("Input",110,160,100);
void setup(void) {
  uint16_t tmp;
  Serial.begin(9600);
  Serial.println("Start");
    tft.reset();
     g_identifier = tft.readID();
if (0) {
    } else if (identifier == 0x0154) {
        name = "S6D0154";
        TS_LEFT = 914; TS_RT = 181; TS_TOP = 957; TS_BOT = 208;
    } else if (identifier == 0x7783) {
        name = "ST7781";
        TS_LEFT = 865; TS_RT = 155; TS_TOP = 942; TS_BOT = 153;
        SwapXY = 1;
    } else if (identifier == 0x7789) {
        name = "ST7789V";
        YP = A2; XM = A1; YM = 7; XP = 6;
        TS_LEFT = 906; TS_RT = 169; TS_TOP = 161; TS_BOT = 919;
    } else if (identifier == 0x9320) {
        name = "ILI9320";
        YP = A3; XM = A2; YM = 9; XP = 8;
        TS_LEFT = 902; TS_RT = 137; TS_TOP = 941; TS_BOT = 134;
    } else if (identifier == 0x9325) {
        name = "ILI9325";
        TS_LEFT = 900; TS_RT = 103; TS_TOP = 96; TS_BOT = 904;
    } else if (identifier == 0x9325) {
        name = "ILI9325 Green Dog";
        TS_LEFT = 900; TS_RT = 130; TS_TOP = 940; TS_BOT = 130;
    } else if (identifier == 0x9327) {
        name = "ILI9327";
        TS_LEFT = 899; TS_RT = 135; TS_TOP = 935; TS_BOT = 79;
        SwapXY = 1;
    } else if (identifier == 0x9329) {
        name = "ILI9329";
        TS_LEFT = 143; TS_RT = 885; TS_TOP = 941; TS_BOT = 131;
        SwapXY = 1;
    } else if (identifier == 0x9341) {
        name = "ILI9341 BLUE";
        TS_LEFT = 920; TS_RT = 139; TS_TOP = 944; TS_BOT = 150;
        SwapXY = 0;
    } else if (identifier == 0) {
        name = "ILI9341 DealExtreme";
        TS_LEFT = 893; TS_RT = 145; TS_TOP = 930; TS_BOT = 135;
        SwapXY = 1;
    } else if (identifier == 0 || identifier == 0x9341) {
        name = "ILI9341";
        TS_LEFT = 128; TS_RT = 911; TS_TOP = 105; TS_BOT = 908;
        SwapXY = 1;
    } else if (identifier == 0x9486) {
        name = "ILI9486";
        TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
    } else if (identifier == 0x9488) {
        name = "ILI9488";
        TS_LEFT = 904; TS_RT = 170; TS_TOP = 950; TS_BOT = 158;
    } else if (identifier == 0xB509) {
        name = "R61509V";
        TS_LEFT = 889; TS_RT = 149; TS_TOP = 106; TS_BOT = 975;
        SwapXY = 1;
    } else {
        name = "unknown";
    }
    Serial.println(name);
    switch (Orientation) {      // adjust for different aspects
        case 0:   break;        //no change,  calibrated for PORTRAIT
        case 1:   tmp = TS_LEFT, TS_LEFT = TS_BOT, TS_BOT = TS_RT, TS_RT = TS_TOP, TS_TOP = tmp;  break;
        case 2:   SWAP(TS_LEFT, TS_RT);  SWAP(TS_TOP, TS_BOT); break;
        case 3:   tmp = TS_LEFT, TS_LEFT = TS_TOP, TS_TOP = TS_RT, TS_RT = TS_BOT, TS_BOT = tmp;  break;
    }

     
    Serial.println(g_identifier);
    tft.begin(g_identifier);
    tft.setRotation(1);
    tft.fillScreen(BLUE); 
  peep=new Peep(&tft);
  Serial.println("Start2");
  peep->addElement(&button1);
  peep->addElement(&button2);
  peep->addElement(&check);
  peep->addElement(&label);
  peep->addElement(&mb);
  peep->addElement(&input);

}



bool touchUp=true;

void loop(void) 
{
 
 uint16_t xpos, ypos;  
    tp = ts.getPoint();   

    
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
    pinMode(XP, OUTPUT);
    pinMode(YM, OUTPUT);
    if (tp.z > MINPRESSURE && tp.z < MAXPRESSURE && touchUp) {
      Serial.println("Press");
      touchUp=false;
      if (SwapXY != (Orientation & 1)) SWAP(tp.x, tp.y);

        xpos = map(tp.x, TS_LEFT, TS_RT, 0, tft.width());
        ypos = map(tp.y, TS_TOP, TS_BOT, 0, tft.height());

     
        String elem=peep->handleTouch(xpos,ypos);
        if(elem=="Button1"){
          mb.setVisible(true);
        }
        if(elem=="Button2"){
          label.setText("Pressed");
        } 
    }else{
      touchUp=true;
    }
}







