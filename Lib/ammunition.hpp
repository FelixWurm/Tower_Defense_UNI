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


