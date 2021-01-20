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
		SVG_PLANT = Circle(Position_x, Position_y, Plant_Radius, pointer_to_window);
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
		return false;
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
	int Speed = 1; //Speed in Pixel peer Tick
	Circle SVG_ammunition;
};

class Zombie {
public:
	Zombie() {
		
	}

	Zombie(int Position_y_in, int type, SVG *pointer_to_window) {
		position_x = TILE_SIZE * (TILE_COUNT_X + 1);

		this->position_y = Position_y_in;
		this->SVG_Zombie = Circle(position_x, position_y, Plant_Radius, pointer_to_window);
		SVG_Zombie.setFill(50, 50, 50);

		//Unterschiedliche Zombies
		if (type == 0) {
			this->Speed = 1;
			this->Damege_to_Plant = 10;
			this->live = 80;
		}


	}
	
	int Move_Zombie() {
		position_x = position_x - Speed;

		//Move Objekt
		SVG_Zombie.moveTo(position_x, position_y);
		return 1;
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
	int position_y;
	int position_x = 0;
	int type;
	
	//Zombie / Game Values
	int Speed = 0; //Speed in Pixel peer Tick
	int live = 100; //Helth value of the Zombie
	int Damege_to_Plant;
	Circle SVG_Zombie;
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

	void Add_Zombie(int Position_y_in, int type) {
		List_of_Zombies.push_back(Zombie(Position_y_in, type, pointer_to_window));
	}

	void Move_movable_Objekts() {
		//Move amo
		//NUR WENN MINDESTENS 1 Objekt da ist!!!!! sonst crasht das system
		if (!List_of_Ammunition.empty()) {
			int X = 0;
			do {
				int CASH = List_of_Ammunition[X].Move_ammunition();
				if (CASH == false) {
					vector<ammunition>::iterator it = List_of_Ammunition.begin();  // it steht auf Index 0
					it = it + X;
					List_of_Ammunition.erase(it);
				}
				else {
					X++;
				}
			} while (X < List_of_Ammunition.size()); // solange nicht alle elemnete durchlaufen wurden
		}


		//Move Zombies
		if (!List_of_Zombies.empty()) {
			for (size_t i = 0; i < List_of_Zombies.size(); i++){
				int Zombie_Status = List_of_Zombies[i].Move_Zombie();
			}
		}


	}




private:

	vector<Plant> List_of_PLants = vector<Plant>();
	vector<ammunition> List_of_Ammunition = vector<ammunition>();
	vector<Zombie> List_of_Zombies = vector<Zombie>();

	SVG* pointer_to_window = nullptr;


	void Check_Collision(bool Collision_Plants) {
		//Check if any amo colids with any Zombie
		for (int amo_NR = 0; amo_NR < List_of_Ammunition.size(); amo_NR++) {
			for (int zombie_NR = 0; zombie_NR < List_of_Zombies.size(); zombie_NR++) {
				if (List_of_Ammunition[amo_NR].get_position('y') == List_of_Zombies[amo_NR].get_position('y')) {
					//wenn sie eine Munition auf in der selben zeile wie ein Zombie Befindet
					if (List_of_Ammunition[amo_NR].get_position('x') == List_of_Zombies[amo_NR].get_position('x')) {
						//Objekte sind Kolidirt

						//Abzihen der Lebenspunkte vom Zombie

						//Löschen der Amo

						//Testen ob der Zombie Gestorben ist?, dann aus liste Löschen.
					}
				}
			}
		}
		if (Collision_Plants == true) {

		}

	}
};