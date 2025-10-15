#pragma once

constexpr int cardinf = 100000000;
class cmd
{
public:
	enum class type {
		addre, addim, adddeg, addr
	};
	type cmdtype;
	int value1;
	int nokori = cardinf;
	//static Font font; 

	bool MouseOver(int i)const;
	void draw(int i)const;

	
	//int value2;
	//type: addre   -> reを+value1
	//      addim   -> imを+value1
	//      adddeg  -> degを+value1
	//      adr     -> rを+value1
};


