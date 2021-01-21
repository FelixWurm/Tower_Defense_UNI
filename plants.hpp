/*
Code zur steuerung der Pflanzen. geschriben für Aud Informatik Uni Osnabrück WS 2020/2021

*/

#define Plant_Radius 15
#define MUNITION_RADIUS 5


#include <algoviz/SVG.hpp>
#include <list>
#include <iostream>

#ifndef  TILE_SIZE
#define TILE_SIZE 40
#endif

#ifndef TILE_COUNT_X
#define TILE_COUNT_X 9
#endif

#ifndef TILE_COUNT_Y
#define TILE_COUNT_Y 5
#endif

#define PLAYGROUND_LENGHT TILE_COUNT_X * TILE_SIZE


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
	int get_health() {
		return health;
	}
	int set_health(int health) {
		this->health = health;
		if (health < 0) {
			return 1;
		}
		else {
			return 0;
		}
	}


private:
	int Position_x;
	int Position_y;
	int Type_of_plant;
	int health = 100;
	Circle SVG_PLANT;
};

class ammunition {
public:
	ammunition() {

	}

	ammunition(int Position_x_in, int  Position_y_in, int type, SVG* pointer_to_window) {
		this->position_x = Position_x_in + MUNITION_RADIUS + Plant_Radius;
		this->position_y = Position_y_in;

		//Different Typs:
		if (type == 0) {
			this->Speed = 6;
			this->strengh = 20;
		}
		this->SVG_ammunition = Circle(position_x, position_y, MUNITION_RADIUS, pointer_to_window);
	}

	int Move_ammunition(int loops_passed) {
		//Calculate new X Position
		position_x = position_x + (Speed * loops_passed);

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

	int get_strengh() {
		return strengh;
	}

private:
	int position_x;
	float position_y;
	int type;
	float Speed = 3; //Speed in Pixel peer Tick
	int strengh = 0;
	Circle SVG_ammunition;
};

class Zombie {
public:
	Zombie() {

	}

	Zombie(int Position_y_in, int type, SVG* pointer_to_window) {
		position_x = TILE_SIZE * (TILE_COUNT_X + 1);

		this->position_y = Position_y_in;
		this->SVG_Zombie = Circle(position_x, position_y, Plant_Radius, pointer_to_window);
		SVG_Zombie.setFill(50, 50, 50);

		//Unterschiedliche Zombies
		if (type == 0) {
			this->Speed = 3;
			this->Damege_to_Plant = 10;
			this->health = 80;
			this->Strenght = 10;
			this->hit_frequenz = 30;
		}


	}

	int Move_Zombie(int loops_passed) {
		if (flag_collision_plant == 0) {
			//Nur wenn sich der Zombie noch bewegen soll
			position_x = position_x - (Speed * loops_passed);
		}

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

	int get_health() {
		return health;
	}

	//set the health of the Zombie, return 0 if zombie is dead.
	int set_health(int health) {
		this->health = health;
		if (health < 0) {
			return 1;
		}
		else {
			return 0;
		}
	}

	void set_collision(int type) {
		this->flag_collision_plant = type;
		//to signal when not to move
	}
	int get_collision() {
		return flag_collision_plant;
	}
	int get_strengh() {
		return Strenght;
	}

	//Counting system to determen wenn to hit a Plant

	int get_atack_needet() {
		hit_delay_counter = hit_delay_counter + 1;
		if (hit_delay_counter > hit_frequenz) {
			hit_delay_counter = 0;
			return true;
		}
		else {
			return false;
		}
	}

private:
	float position_y;
	int position_x;
	int type;

	//Zombie / Game Values
	float Speed = 0.0; //Speed in Pixel peer Tick
	int health = 100; //Helth value of the Zombie
	int Damege_to_Plant;
	int flag_collision_plant = 0;
	int Strenght = 0;

	//angriff von Pflanzen
	int hit_delay_counter = 0;
	int hit_frequenz = 30;

	Circle SVG_Zombie;
};


class Manegment {
public:
	Manegment(SVG* pointer_to_window_in) {
		this->pointer_to_window = pointer_to_window_in;
	}

	//Add stuff
	void Add_Plant(int Posiiton_x, int Posiiton_y, int type) {
		List_of_PLants.push_back(Plant(Posiiton_x, Posiiton_y, type, pointer_to_window));
	}

	void Shoot_Munition(int type) {
		//Wook thrue each plant
		for (int X = 0; X < List_of_PLants.size(); X++) {
			List_of_Ammunition.push_back(ammunition(List_of_PLants[X].get_position('x'), List_of_PLants[X].get_position('y'), type, pointer_to_window));
		}
	}

	void Add_Zombie(int Position_y_in, int type) {
		List_of_Zombies.push_back(Zombie(Position_y_in, type, pointer_to_window));
	}

	void Move_movable_Objekts(int loops_passed) {
		//Move amo
		//NUR WENN MINDESTENS 1 Objekt da ist!!!!! sonst crasht das system
		if (!List_of_Ammunition.empty()) {
			int X = 0;
			do {
				int CASH = List_of_Ammunition[X].Move_ammunition(loops_passed);
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

		Check_Collision(0);

		//Move Zombies
		if (!List_of_Zombies.empty()) {
			for (size_t i = 0; i < List_of_Zombies.size(); i++) {
				int Zombie_Status = List_of_Zombies[i].Move_Zombie(loops_passed);
			}
		}
		Check_Collision(1);
	}



private:

	vector<Plant> List_of_PLants = vector<Plant>();
	vector<ammunition> List_of_Ammunition = vector<ammunition>();
	vector<Zombie> List_of_Zombies = vector<Zombie>();

	SVG* pointer_to_window = nullptr;


	void Check_Collision(int PLANTS_TEST) {
		//Check if any amo colids with any Zombie
		int amo_NR = 0;
		int zombie_NR = 0;
		int plant_NR = 0;
		if ((List_of_Ammunition.empty() == false) && (List_of_Zombies.empty() == false)) {
			while (amo_NR < List_of_Ammunition.size()) {
				zombie_NR = 0;
				while (zombie_NR < List_of_Zombies.size()) {

					if (List_of_Ammunition[amo_NR].get_position('y') == List_of_Zombies[zombie_NR].get_position('y')) {
						//wenn sie eine Munition auf in der selben zeile wie ein Zombie Befindet
						int Distance = List_of_Ammunition[amo_NR].get_position('x') - List_of_Zombies[zombie_NR].get_position('x');
						//Betrage bilden
						if (Distance < 0) {
							Distance = Distance * -1;
						}

						if (Distance < 10) {
							//sind die Objekte beide Hinter vor dem letzten Block?

							if ((List_of_Ammunition[amo_NR].get_position('x') < PLAYGROUND_LENGHT) && (List_of_Zombies[zombie_NR].get_position('x') < PLAYGROUND_LENGHT)) {
								//Objekte sind im Spielfeld Kolidirt

								//Abzihen der Lebenspunkte vom Zombie
								int remainig_Live = List_of_Zombies[zombie_NR].get_health() - List_of_Ammunition[amo_NR].get_strengh();
								int Dead = List_of_Zombies[zombie_NR].set_health(remainig_Live);

								//Löschen der Amo
								vector<ammunition>::iterator it1 = List_of_Ammunition.begin();  // it steht auf Index 0
								it1 = it1 + amo_NR;
								List_of_Ammunition.erase(it1);
								if (List_of_Ammunition.empty() == true) {
									return;
								}
								//Testen ob der Zombie Gestorben ist?, dann aus liste Löschen.
								if (Dead == 1) {
									vector<Zombie>::iterator it2 = List_of_Zombies.begin();  // it steht auf Index 0
									it2 = it2 + zombie_NR;
									List_of_Zombies.erase(it2);
									if (List_of_Zombies.empty() == true) {
										return;
									}
								}
								//amo_NR = amo_NR - 1;
							}
						}
					}
					//nächster Zombie
					zombie_NR = zombie_NR + 1;

				}
				//Nächste Munition
				amo_NR = amo_NR + 1;
			}
		}
		if (PLANTS_TEST == 1) {
			//Teat also if a collision with plants heppend
			if ((List_of_PLants.empty() == false) && (List_of_Zombies.empty() == false)) {
				while (plant_NR < List_of_PLants.size()) {
					zombie_NR = 0;
					while (zombie_NR < List_of_Zombies.size()) {

						if (List_of_PLants[plant_NR].get_position('y') == List_of_Zombies[zombie_NR].get_position('y')) {
							//wenn sie eine Munition auf in der selben zeile wie ein Zombie Befindet
							int Distance = List_of_PLants[plant_NR].get_position('x') - List_of_Zombies[zombie_NR].get_position('x');
							//Betrage bilden
							if (Distance < 0) {
								Distance = Distance * -1;
							}

							if (Distance < Plant_Radius) {

								//Objekte sind im Spielfeld Kolidirt

								//muss die pflanze angegriffen werden?
								if (List_of_Zombies[zombie_NR].get_atack_needet() == true) {
									//Abzihen der Lebenspunkte vom der Pflanze
									int remainig_Live = List_of_PLants[plant_NR].get_health() - List_of_Zombies[zombie_NR].get_strengh();
									int Dead = List_of_PLants[plant_NR].set_health(remainig_Live);

									//Pflanze Tot?
									if (Dead == 1) {
										vector<Plant>::iterator it = List_of_PLants.begin();  // it steht auf Index 0
										it = it + plant_NR;
										List_of_PLants.erase(it);
										if (List_of_PLants.empty() == true) {
											return;
										}
										//Zombie wieder Mobiel machen
										List_of_Zombies[zombie_NR].set_collision(0);

									}
								}
								//Festsetzen des Zombies
								List_of_Zombies[zombie_NR].set_collision(1);



							}
						}
						//nächster Zombie
						zombie_NR = zombie_NR + 1;

					}
					//Nächste Munition
					plant_NR = plant_NR + 1;
				}
			}
		}

	}
};