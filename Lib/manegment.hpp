#define Plant_Radius 15
#define MUNITION_RADIUS 5
#define PLANT_SIZE 40
#define ZOMBIE_SIZE 40

#include <algoviz/SVG.hpp>
#include <list>
#include <iostream>

#include "plants.hpp"
#include "zombie.hpp"
#include "ammunition.hpp"

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





class Manegment {
public:
	Manegment(SVG* pointer_to_window_in,int  target_zombies_suvived) {
		this->pointer_to_window = pointer_to_window_in;
		this->target_zombies_suvived = target_zombies_suvived;
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


		//schießen der Munition

		for (int plant_NR = 0; plant_NR < List_of_PLants.size(); plant_NR++) {
			if (List_of_PLants[plant_NR].get_shoot_needet() == true) {
				List_of_Ammunition.push_back(ammunition(List_of_PLants[plant_NR].get_position('x'), List_of_PLants[plant_NR].get_position('y'), List_of_PLants[plant_NR].get_ammunition_type(), pointer_to_window));
			}
		}


	}

	int Game_finished() {
		if (target_zombies_suvived < 0) {
			return true;
		}
		return false;
	}
	int Game_lost() {
		int zombies_smaller_zero = 0;
		for (int zombie_NR = 0; zombie_NR < List_of_Zombies.size(); zombie_NR++){
			if (List_of_Zombies[zombie_NR].get_position('x') < 0) {
				zombies_smaller_zero = zombies_smaller_zero + 1;
			}

		}
		return zombies_smaller_zero;
	}



	int Score() {
		return 0;
	}

private:

	vector<Plant> List_of_PLants = vector<Plant>();
	vector<ammunition> List_of_Ammunition = vector<ammunition>();
	vector<Zombie> List_of_Zombies = vector<Zombie>();

	SVG* pointer_to_window = nullptr;

	int target_zombies_suvived = 0;

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
			int Zombie_that_stoped[List_of_Zombies.size()];
			for (size_t i = 0; i < List_of_Zombies.size(); i++)
			{
				Zombie_that_stoped[i] = 0;
			}
			if ((List_of_PLants.empty() == false) && (List_of_Zombies.empty() == false)) {
				while (plant_NR < List_of_PLants.size()) {
					zombie_NR = 0;
					while (zombie_NR < List_of_Zombies.size()) {

						if (List_of_PLants[plant_NR].get_position('y') == List_of_Zombies[zombie_NR].get_position('y')) {
							//wenn sie eine Munition auf in der selben zeile wie ein Zombie Befindet
							int Distance = List_of_PLants[plant_NR].get_position('x') - List_of_Zombies[zombie_NR].get_position('x');
							//Betrage bilden
							if (Distance < 0) {
								Distance = Distance * (-1);
							}

							if (Distance < Plant_Radius*2) {

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
										Zombie_that_stoped[zombie_NR] = 0;
										

									}
								}
								//Festsetzen des Zombies
								Zombie_that_stoped[zombie_NR] = 1;

							}
						}
						//nächster Zombie
						zombie_NR = zombie_NR + 1;

					}
					//Nächste Munition
					plant_NR = plant_NR + 1;
				}
			}
			for (size_t i = 0; i < List_of_Zombies.size(); i++)
			{
				List_of_Zombies[i].set_collision(Zombie_that_stoped[i]);
			}
		}

	}
};