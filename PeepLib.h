#ifndef PeepLib
#define PeepLib

#if ARDUINO < 101
#define USE_GFX_KBV
#include "ADA_GFX_kbv.h"
#else
#include "Adafruit_GFX.h"
#endif

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

#define RESULT_OK 0
#define RESULT_YES 1
#define RESULT_NO 2
#define RESULT_CANCEL 3


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

#define EVT_NONE 0
#define EVT_CLICK 1
#define EVT_KEYBOARDSHOW 2
#define EVT_KEYBOARDHIDE 3

struct Event{
	String id;
	int eventType;
	int customType;
	
};




class Paintable{
public:
virtual void repaint();
virtual Adafruit_GFX* getDisplay();
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
	virtual void setPaintable(Paintable *paintable);
    int getX();
    int getY();
    int getWidth();
    int getHeight();
	String getID();
	
	int getZIndex();
	protected:
	Paintable *paintable;
	int zIndex;
	int x;
	int y;
	int width;
	int height;
	String id;
	

};


class Peep:public Paintable{
	public:
	Peep(Adafruit_GFX *tft);
	void addElement(ControlElement *controlElement);
	Event handleTouch(int x,int y);
	Adafruit_GFX* tft;
	void repaint();
	Adafruit_GFX* getDisplay();
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


};

class Button:public ControlElement{
  public:
    Button(String id,int x,int y,int width,int height,String text);
	void paintElement() override;
	virtual int handleTouch(int x,int y) override;
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
  private:

	String text;
};

class MessageBox:public ControlElement{
	public:
	MessageBox(String caption,String text);
	MessageBox(String caption,String text,int style,int buttonStyle);
	void paintElement() override;
	virtual int handleTouch(int x,int y) override;
	virtual void setPaintable(Paintable *paintable) override;
	void setVisible(bool visible);
	private:
Button* buttons[3]={nullptr};
	int buttonCount;
	int style;
	int buttonStyle;
	String caption;
	bool visible;

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