class ButtonBase : ObjectBase
{
public:
	int lastUpdate=0,updateSpeed=50;
	ButtonBase(){get_uuid(0);}
	virtual void update(){}
	
	void destroy(){delete this;}
};

class SimpleButton : ButtonBase
{
public:

	int x,y,xStop;string Info;Func func;
	SimpleButton(int _x,int _y,string _Info,Func _func)  {xStop=x+_Info.size()-1;}
	void update(){
		
	}
	
	
};