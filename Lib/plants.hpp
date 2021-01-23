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
		this->Type_of_plant = type;
		//SVG_PLANT = Circle(Position_x, Position_y, Plant_Radius, pointer_to_window);
		//SVG_PLANT = Image("/img/plant1_400x400", (Position_x-(TILE_SIZE/2))+((TILE_SIZE - PLANT_SIZE)/2), (Position_y - (TILE_SIZE / 2)) + ((TILE_SIZE - PLANT_SIZE) / 2), PLANT_SIZE, PLANT_SIZE, pointer_to_window);
		SVG_PLANT = Image("img/plant1_400x400.png", Position_x,Position_y, PLANT_SIZE, PLANT_SIZE, pointer_to_window);

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
	Image SVG_PLANT;
};

