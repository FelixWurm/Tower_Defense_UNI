/*
Code zur steuerung der Pflanzen. geschriben für Aud Informatik Uni Osnabrück WS 2020/2021

*/

#define Plant_Radius 15
#define MUNITION_RADIUS 5


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
	int get_position(char Achse) {
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
};

class ammunition {
public:
	ammunition() {

	}

	ammunition(int Position_x_in, int  Position_y_in, int type, SVG *pointer_to_window) {
		this->position_x = Position_x_in;
		this->position_y = Position_y_in;

		//Different Typs:
		if (type == 0) {
			this->Speed = 1;
		}
		this->SVG_ammunition = Circle(position_x, position_y, MUNITION_RADIUS, pointer_to_window);
	}

	bool Move_ammunition() {
		//Calculate new X Position
		position_x = position_x + Speed;

		//Move Objekt
		SVG_ammunition.moveTo(position_x, position_y);

		//check if Objekt is still in view
		if (position_x > ((TILE_COUNT_X + 1) * TILE_SIZE)) {
			//Die Munition ist aus dem Bild geflogen.
			return false;
		}
		else {
			return true;
		}
	}

	int get_position(char Achse) {
		if (Achse == 'x') {
			return position_x;
		}

		if (Achse == 'y') {
			return position_y;
		}

		return -1;

	}
	

private:
	int position_x;
	int position_y;
	int type;
	int Speed; //Speed in Pixel peer Tick
	Circle SVG_ammunition;
};

class Zombie {
public:
	Zombie() {
		
	}

	Zombie(int Position_y_in, int type, SVG * pointer_to_window_in) {
		this->position_y = Position_y_in;

		//Unterschiedliche Zombies
		if (type == 0) {
			this->Speed = 1;
		}
	}
	int move_Zombie() {
		pointer_to_window = pointer_to_window + Speed;
		return -1;

	}

private:
	int position_y;
	int position_x = TILE_SIZE* (TILE_COUNT_X + 1);
	int type;
	int Speed; //Speed in Pixel peer Tick
	int live = 100; //Helth value of the Zombie
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

	void Shoot_Munition(int type) {
		//Wook true each plant
		for (int X = 0; X < List_of_PLants.size(); X++) {
			List_of_Ammunition.push_back(ammunition(List_of_PLants[X].get_position('x'), List_of_PLants[X].get_position('y'), type, pointer_to_window));
		}
	}

	//Move Zomies and amunition. First the amo then the Zombies, Zombies test if they collide with Plants or amo
	void Move_movable_Objekts() {
		
		//Move amo
		int X = 0;
		do {
			bool CASH = List_of_Ammunition[X].Move_ammunition();
			if (CASH == false) {
				vector<ammunition>::iterator it = List_of_Ammunition.begin();  // it steht auf Index 0
				it = it + X;
				List_of_Ammunition.erase(it);
			}
			else {
				X++;
			}
		} while (X <= List_of_Ammunition.size()); // solange nicht alle elemnete durchlaufen wurden
		//Move Zombies

	}

	void Add_Zombie(int Position_y_in, int type) {
		List_of_Zombies.push_back(Zombie(Position_y_in, type, pointer_to_window));
	}


private:
	vector<Plant> List_of_PLants = vector<Plant>();
	vector<ammunition> List_of_Ammunition = vector<ammunition>();
	vector<Zombie> List_of_Zombies = vector<Zombie>();

	SVG* pointer_to_window = nullptr;
};