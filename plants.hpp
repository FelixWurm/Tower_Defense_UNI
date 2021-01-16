/*
Code zur steuerung der Pflanzen. geschriben für Aud Informatik Uni Osnabrück WS 2020/2021

*/

#define Data_Type  c++
#define Plant_Radius 15
#define MUNITION_RADIUS 3;


#include <algoviz/SVG.hpp>
#include <list>

#ifndef  TILE_SIZE
#define TILE_SIZE 40
#endif

#ifndef TILE_COUNT_X
#define TILE_COUNT_X 9
#endif

#ifndef TILE_COUNT_Y
#define TILE_COUNT_Y 5
#endif



class Plant {
public:
	Plant() {

	}

	//Constructor
	Plant(int Position_x_in, int  Position_y_in, int  type, SVG* pointer_to_window) {
		this->Position_x = Position_x_in;
		this->Position_y = Position_y_in;
		this->Type_of_plant = type;
		this->SVG_PLANT = Circle(Position_x, Position_y, Plant_Radius, pointer_to_window);
		SVG_PLANT.setFill(200, 0, 0);

	}

	//wo ist die Pflanze?
	int Plant_Position(char Achse) {
		if (Achse == 'x') {
			return Position_x;
		}
		if (Achse == 'y') {
			return Position_y;
		}
		return -1;
	}
private:
	int Position_x;
	int Position_y;
	int Type_of_plant;
	Circle SVG_PLANT;
	SVG* Tagrget_Playyground;
};



class ammunition {
public:
	ammunition() {

	}

	ammunition(int Position_x_in,int  Position_y_in,int type, SVG *pointer_to_window_in) {
		this->position_x = Position_x_in;
		this->position_y = Position_x_in;
		this->pointer_to_window = pointer_to_window_in;
	}

	//this class also serves as a colision Detection System.
	int Move_ammunition(int Direction, int lenght) {

		//Chek if there are Zombies in the row
		if (false) {
			//Check if a Colision has hapend?
		}
		return -1;
	}

private:
	int position_x;
	int position_y;
	int type;
	int Speed; //Speed in Pixel peer Tick
	Circle SVG_ammunition;
	SVG *pointer_to_window;
};

class Zombie {
public:
	Zombie() {

	}
	Zombie(int Position_y_in, int type, int Speed, SVG * pointer_to_window_in) {
		this->position_y = Position_y_in;
	}
private:
	int position_x = TILE_SIZE* (TILE_COUNT_X + 1);
	int position_y;
	int type;
	int Speed; //Speed in Pixel peer Tick
	SVG* pointer_to_window;
};


class Manegment {
public:
	Manegment(SVG *pointer_to_window_in) {
		this->pointer_to_window = pointer_to_window_in;
	}

	//Add stuff
	void Add_Plant(int Posiiton_x, int Posiiton_y,int type){
		List_of_PLants.push_back(Plant(Posiiton_x, Posiiton_y, type, pointer_to_window));
	}

	void Shoot_Munition() {
		//Wook true each plant
		for (int X = 0; X < List_of_PLants.size(); X++) {
			
		}
	}

	void Move_movable_Objekts() {

	}

	void Add_Zombie() {

	}


private:
	list<Plant> List_of_PLants = list<Plant>();
	list<ammunition> List_of_Munition = list<ammunition>();

	SVG* pointer_to_window = nullptr;
};