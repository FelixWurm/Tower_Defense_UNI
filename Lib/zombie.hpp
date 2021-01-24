class Zombie {
public:
	Zombie() {

	}

	Zombie(int Position_y_in, int type, SVG* pointer_to_window) {
		position_x = TILE_SIZE * (TILE_COUNT_X + 1);

		this->position_y = Position_y_in;

		//Unterschiedliche Zombies
		if (type == 0) {
			SVG_Zombie = Image("img/zombie1_400x400.png", position_x, position_y, ZOMBIE_SIZE, ZOMBIE_SIZE, pointer_to_window);


			this->Speed = 0.3;
			this->Damege_to_Plant = 8;
			this->health = 80;
			this->Strenght = 10;
			//30 = 1per Sec so 1HZ
			this->hit_frequenz = 30;
		}
		if (type == 1) {
			SVG_Zombie = Image("img/zombie1_400x400.png", position_x, position_y, ZOMBIE_SIZE, ZOMBIE_SIZE, pointer_to_window);


			this->Speed = 0.3;
			this->Damege_to_Plant = 8;
			this->health = 80;
			this->Strenght = 10;
			//30 = 1per Sec so 1HZ
			this->hit_frequenz = 30;
		}
		if (type == 2) {
			SVG_Zombie = Image("img/zombie1_400x400.png", position_x, position_y, ZOMBIE_SIZE, ZOMBIE_SIZE, pointer_to_window);


			this->Speed = 0.3;
			this->Damege_to_Plant = 8;
			this->health = 80;
			this->Strenght = 10;
			//30 = 1per Sec so 1HZ
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
	int position_y;
	float position_x;
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

	Image SVG_Zombie;
};
