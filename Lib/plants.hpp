/*
Code zur steuerung der Pflanzen. geschriben für Aud Informatik Uni Osnabrück WS 2020/2021

*/




class Plant {
public:
	Plant() {

	}

	//Constructor
	Plant(int Position_x_in, int  Position_y_in, int  type, SVG* pointer_to_window) {
		this->Position_x = Position_x_in;
		this->Position_y = Position_y_in;
		this->type = type;
		//SVG_PLANT = Circle(Position_x, Position_y, Plant_Radius, pointer_to_window);
		//SVG_PLANT = Image("/img/plant1_400x400", (Position_x-(TILE_SIZE/2))+((TILE_SIZE - PLANT_SIZE)/2), (Position_y - (TILE_SIZE / 2)) + ((TILE_SIZE - PLANT_SIZE) / 2), PLANT_SIZE, PLANT_SIZE, pointer_to_window);
		if (type == 0) {
			//set correct Image
			SVG_PLANT = Image("img/plant1_400x400.png", Position_x,Position_y, PLANT_SIZE, PLANT_SIZE, pointer_to_window);
			frequency = 150;
			frequency = shoot_delay_counter;
			health = 100;
			ammunition_type = 0;

		}
		if (type == 1) {
			//set correct Image
			SVG_PLANT = Image("img/plant2_400x400.png", Position_x, Position_y, PLANT_SIZE, PLANT_SIZE, pointer_to_window);
			frequency = 150;
			frequency = shoot_delay_counter;
			health = 100;
			ammunition_type = 0;

		}
		if (type == 2) {
			//set correct Image
			SVG_PLANT = Image("img/plant3_400x400.png", Position_x, Position_y, PLANT_SIZE, PLANT_SIZE, pointer_to_window);
			frequency = 150;
			frequency = shoot_delay_counter;
			health = 100;
			ammunition_type = 0;

		}
		if (type == 3) {
			//set correct Image
			SVG_PLANT = Image("img/plant4_400x400.png", Position_x, Position_y, PLANT_SIZE, PLANT_SIZE, pointer_to_window);
			frequency = 150;
			frequency = shoot_delay_counter;
			health = 100;
			ammunition_type = 0;

		}
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

	int get_shoot_needet() {
		shoot_delay_counter++;
		if (shoot_delay_counter > frequency) {
			shoot_delay_counter = 0;
			return true;
		}
		else {
			return false;
		}
	}

	int get_ammunition_type() {
		return ammunition_type;
	}

private:
	int Position_x;
	int Position_y;
	int type;
	int health = 100;
	int frequency = 30;
	int shoot_delay_counter = frequency;
	int ammunition_type;
	Image SVG_PLANT;
};

