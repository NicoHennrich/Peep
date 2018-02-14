#ifndef PeepLib
#define PeepLib

#include "Arduino.h"
#include "MCUFRIEND_kbv.h"

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

#define MSGBOX_NONE 0
#define MSGBOX_WARNING 1
#define MSGBOX_INFORMATION 2
#define MSGBOX_QUESTION 3

#define BTN_OK 0
#define BTN_YESNO 1
#define BTN_YESNOCANCEL 2
#define BTN_OKCANCEL 3


//#define colorschemedark



#if defined colorschemedark
	#define BACKGROUND BLACK
	#define TEXTCOLOR WHITE
	#define SHADELIGHT WHITE
	#define SHADEDARK DARKGRAY
	#define LOWEREDSURFACE LIGHTGRAY
	#define RISEDSURFACE DARKGRAY
	
	
#else
	#define BACKGROUND BLUE
	#define TEXTCOLOR BLACK
	#define SHADELIGHT WHITE
	#define SHADEDARK DARKGRAY
	#define LOWEREDSURFACE WHITE
	#define RISEDSURFACE GRAY
		
#endif

class Paintable{
public:
virtual void repaint();
virtual MCUFRIEND_kbv* getDisplay();
void setZIndex(int zIndex);
int getZIndex();
private:
int zIndex;
};


class ControlElement{
  public:
    ControlElement(String id,int x,int y,int width,int height);
	
    virtual void paintElement()=0;
    virtual int handleTouch(int x,int y)=0;
	virtual bool requestsInput();
	virtual void setText(String text);
	virtual String getText();
    int getX();
    int getY();
    int getWidth();
    int getHeight();
	String getID();
	Paintable *paintable;
	int getZIndex();
	protected:
	int zIndex;
	int x;
	int y;
	int width;
	int height;
	String id;
	

};


class Peep:public Paintable{
	public:
	Peep(MCUFRIEND_kbv *tft);
	void addElement(ControlElement *controlElement);
	//void setGUI(MCUFRIEND_kbv *tft);
	String handleTouch(int x,int y);
	//MCUFRIEND_kbv* getTFT();
	MCUFRIEND_kbv* tft;
	void repaint();
	MCUFRIEND_kbv* getDisplay();
	void showKeyboard();
	void hideKeyboard();
	private:
	String keyboardText;
	bool shift;
	void refreshKeyboard();
	ControlElement* controlEditing;
	int keyButtonHeight;
	ControlElement* controlElements[20]={nullptr};
	int elementCount;
	bool keyboardVisible;
	//MCUFRIEND_kbv* tft;

};

class Button:public ControlElement{
  public:
    Button(String id,int x,int y,int width,int height,String text);
	void paintElement() override;
	virtual int handleTouch(int x,int y) override;
  //protected:
	//MCUFRIEND_kbv *tft;
  private:
	String text;
};

class Checkbox:public ControlElement{
  public:
    Checkbox(String id,int x,int y,String text);
	void paintElement() override;
	virtual int handleTouch(int x,int y) override;
	bool isChecked();
	void setChecked(bool checked);
  //protected:
	//MCUFRIEND_kbv *tft;
  private:

	String text;
	bool checked;
};

class Label:public ControlElement{
  public:
    Label(String id,int x,int y,String text);
	void paintElement() override;
	virtual int handleTouch(int x,int y) override;
	void setText(String text);
	String getText();
  //protected:
	//MCUFRIEND_kbv *tft;
  private:

	String text;
};

class MessageBox:public ControlElement{
	public:
	MessageBox(String caption,String text);
	MessageBox(String caption,String text,int style,int buttons);
	void paintElement() override;
	virtual int handleTouch(int x,int y) override;
	void setVisible(bool visible);
	private:
	int style;
	int buttons;
	String caption;
	bool visible;
	int buttonX;
	int buttonY;
	int buttonWidth;
	int buttonHeight;
	String text;
	
};

class Input:public ControlElement{
	public:
	Input(String id,int x,int y,int width);
	void paintElement() override;
	virtual int handleTouch(int x,int y) override;
	bool requestsInput() override;
	String getText();
	void setText(String text);
	private:
	String text;
};


#endif