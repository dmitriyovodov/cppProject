

/// \brief ������� render_background ������������� ������������ ���� ������� ����.
/// 
/// \return ������ �� ����������.

void render_background() {
	u32* pixel = (u32*)memory;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			*pixel++ = 0xff0000;
		}
	}
}

/// \brief ������� clear_screen ������������� ��������� ���� ������� ����.
/// 
/// \param color - ���� ������� ����.
///
/// \return ������ �� ����������.
void clear_screen(u32 color) {
	u32* pixel = (u32*)memory;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			*pixel++ = color;
		}
	}
}




/// \brief ������� draw_rect ������ �������������, �� ��������� ����������� � �����.
/// 
/// \param x0 - ��������� ���������� x.
/// \param y0 - ��������� ���������� y.
/// \param x1 - �������� ���������� x.
/// \param y1 - �������� ���������� y.
/// \param color - ���� ��������������.
/// 
/// \return ������ �� ����������.
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

/// \brief ������� draw_border ������ ������� �������� ������������.
/// 
/// \return ������ �� ����������.
void draw_border() {
	draw_rect(0,0,10,720, 0xffffff);
	draw_rect(1255, 0, 1265, 720, 0xffffff);
	draw_rect(0, 710, 1280, 720, 0xffffff);
}
