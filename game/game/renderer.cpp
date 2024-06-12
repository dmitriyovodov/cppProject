

/// \brief Функция render_background устанавливает определенный цвет заднего фона.
/// 
/// \return Ничего не возвращает.

void render_background() {
	u32* pixel = (u32*)memory;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			*pixel++ = 0xff0000;
		}
	}
}

/// \brief Функция clear_screen устанавливает указанный цвет заднего фона.
/// 
/// \param color - цвет заднего фона.
///
/// \return Ничего не возвращает.
void clear_screen(u32 color) {
	u32* pixel = (u32*)memory;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			*pixel++ = color;
		}
	}
}




/// \brief Функция draw_rect рисует прямоугольник, по указанным координатам и цвету.
/// 
/// \param x0 - начальная координата x.
/// \param y0 - начальная координата y.
/// \param x1 - конечная координата x.
/// \param y1 - конечная координата y.
/// \param color - цвет прямоугольника.
/// 
/// \return Ничего не возвращает.
void draw_rect(int x0, int y0, int x1, int y1, int color) {
	x0 = clamp(0, x0, width);
	x1 = clamp(0, x1, width);
	y0 = clamp(0, y0, height);
	y1 = clamp(0, y1, height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)memory + x0 + y * width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

/// \brief Функция draw_border рисует границы игрового пространства.
/// 
/// \return Ничего не возвращает.
void draw_border() {
	draw_rect(0,0,10,720, 0xffffff);
	draw_rect(1255, 0, 1265, 720, 0xffffff);
	draw_rect(0, 710, 1280, 720, 0xffffff);
}
