#include "scrollbarUI.h"
#include "buttonUI.h"
#include "textureUI.h"

void scrollbarProcessClick(frame *f,int id)
{
	((scrollbarUI *)(f->parent))->clickReturn(id);
}

scrollbarUI::scrollbarUI(float xpos, float ypos, float h, int n)
{
	x=xpos;
	y=ypos;
	width=16;
	height=h;
  
	buttonUI* ScrollUp=new buttonUI(-6.0f,-8.0f,32.0f,32.0f,"Interface\\Buttons\\UI-ScrollBar-ScrollUpButton-Up.blp","Interface\\Buttons\\UI-ScrollBar-ScrollUpButton-Down.blp");
	ScrollUp->setClickFunc(scrollbarProcessClick,0);
	addChild(ScrollUp);

	buttonUI* ScrollDown=new buttonUI(-6.0f,height-24.0f,32.0f,32.0f,"Interface\\Buttons\\UI-ScrollBar-ScrollDownButton-Up.blp","Interface\\Buttons\\UI-ScrollBar-ScrollDownButton-Down.blp");
	ScrollDown->setClickFunc(scrollbarProcessClick,1);
	addChild(ScrollDown);
	ScrollKnob=new textureUI(-6.0f,10.0f,32.0f,32.0f,"Interface\\Buttons\\UI-ScrollBar-Knob.blp");
	ScrollKnob->setClickFunc(scrollbarProcessClick,2);
	addChild(ScrollKnob);
	value=0;
	num=n;
	changeFunc=0;
}

void scrollbarUI::clickReturn(int id)
{
	if(id==0)//Scroll Up
	{
		if(value!=0)
			value--;
	}
	else if(id==1)//Scroll Down
	{
		if(value!=num-1)
			value++;
	}
	else//ScrollKnob
	{
	}
	//Update ScrollKnob Position
	if(num>0)
		ScrollKnob->y=10.0f+(height-40.0f)*value/num;
	if(changeFunc)
		changeFunc(value);
}

void scrollbarUI::setChangeFunc(void (*f)(int))
{
	changeFunc=f;
}

int	 scrollbarUI::getValue()
{
  return value;
}
void scrollbarUI::setValue(int i)
{
  value=i;
  if(value>=num)
    value=num-1;
  if(value<0)
    value=0;
  if(num>0)
    ScrollKnob->y=14.0f+(height-48.0f)*value/num;
}
void scrollbarUI::setNum(int i)
{
  num=i;
  if(value>=num)
    value=num-1;
}
