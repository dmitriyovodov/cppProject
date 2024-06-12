#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

/// player_pos_x - ������� ������; ball_p_x � ball_p_y - ������� ����; ball_speed_y, ball_speed_x � ball_size - �������������� ����
float player_pos_x = 565, ball_p_x = 630, ball_p_y = 240, ball_speed_y = -400, ball_speed_x = 0, ball_size = 20;

/// p_width � p_height - ������� ������

int p_width = 150, p_height = 20;

/// speed - ����� �������� ��������.

float speed = 1200.f;

/// dif - ������� ����� �������� ���� � ������ ��� ������������. ������ �� ��������� �������� ���� �� x.

float dif;

/// bl_w � bl_h - ������� ����.

int bl_w = 130, bl_h = 30;

/// bl_color - ���� ����.

u32 bl_color = 0;

/// blocks - ������ ��������� ������ �������.

std::vector<std::vector<int>> blocks;

///hot_button - ��������� ����.

int hot_button = 0;

/// \brief ������� simulate_game ��������� ��� ������� �������� ��������.
/// 
/// \param input - ��������� �� ������ input main.cpp.
/// \param dt - ������� ������� ����� �������. ������ �� �������� ��������.
/// 
/// \return ������ �� ����������.
void simulate_game(Input* input, float dt) {
	clear_screen(0x000000);
	draw_border();
	if (current_gamemode == GM_GAMEPLAY) {
		if (is_down(BUTTON_LEFT)) player_pos_x -= speed * dt;
		if (is_down(BUTTON_RIGHT)) player_pos_x += speed * dt;
		if (player_pos_x <= 10) player_pos_x = 10;
		if (player_pos_x >= 1265 - p_width) player_pos_x = 1265 - p_width;
		draw_rect(player_pos_x, 60, player_pos_x + p_width, 60 + p_height, 0xffffff);

		ball_p_y += ball_speed_y * dt;
		ball_p_x += ball_speed_x * dt;

		if (60 <= ball_p_y && ball_p_y <= 60 + p_height && ball_p_x + ball_size > player_pos_x && ball_p_x < player_pos_x + p_width) {
			dif = (ball_p_x + ball_size - (player_pos_x + p_width / 2)) * 2;
			if (is_down(BUTTON_RIGHT) || is_down(BUTTON_LEFT)) dif *= 2;
			if (ball_speed_x + dif < speed) {
				ball_speed_x += dif;
			}
			ball_speed_y *= -1;
		}
		if (ball_p_y + ball_size >= 720) {
			ball_speed_y *= -1;
		}

		if (ball_p_x + ball_size >= 1265 || ball_p_x <= 10) {
			ball_speed_x *= -1;
		}


		draw_rect(ball_p_x, ball_p_y, ball_p_x + ball_size, ball_p_y + ball_size, 0xffffff);

		for (int i = 0; i < blocks.size(); i++) {
			draw_rect(blocks[i][0], blocks[i][1], blocks[i][0] + bl_w, blocks[i][1] + bl_h, bl_color);
			if ((ball_p_x <= blocks[i][0] + bl_w && ball_p_x + ball_size >= blocks[i][0]) &&
				(ball_p_y <= blocks[i][1] + bl_h && ball_p_y + ball_size >= blocks[i][1])) {
				if (ball_p_x >= blocks[i][0] + bl_w * 0.98 || ball_p_x + ball_size <= blocks[i][0] + bl_w * 0.02)
					ball_speed_x *= -1;
				else {
					ball_speed_y *= -1;
				}
				blocks.erase(blocks.begin() + i);
			}
		}
		if (blocks.empty() || ball_p_y <= 0) {
			current_gamemode = GM_MENU;
			blocks.clear();
			player_pos_x = 565, ball_p_x = 630, ball_p_y = 240, ball_speed_y = -400, ball_speed_x = 0, ball_size = 20;
			p_width = 150, p_height = 20;
		}
	}
	else if (current_gamemode == GM_MENU) {
		if (pressed(BUTTON_LEFT)) {
			hot_button = hot_button - 1;
			if (hot_button == -1) hot_button = 2;
		}
		if (pressed(BUTTON_RIGHT)) hot_button = (hot_button + 1) % 3;



		if (hot_button == 0) {
			draw_rect(250, 300, 450, 400, 0xffff00);
			draw_rect(500, 300, 700, 400, 0x550055);
			draw_rect(750, 300, 950, 400, 0x005555);
		}
		else if (hot_button == 1) {
			draw_rect(250, 300, 450, 400, 0x555500);
			draw_rect(500, 300, 700, 400, 0xff00ff);
			draw_rect(750, 300, 950, 400, 0x005555);
		}
		else if (hot_button == 2) {
			draw_rect(250, 300, 450, 400, 0x555500);
			draw_rect(500, 300, 700, 400, 0x550055);
			draw_rect(750, 300, 950, 400, 0x00ffff);
		}
		if (pressed(BUTTON_ENTER)) {
			if (hot_button == 0) {
				blocks = initialize_level1();
				bl_color = 0xffff00;
			}
			if (hot_button == 1) {
				blocks = initialize_level2();
				bl_color = 0xff00ff;
			}
			if (hot_button == 2) {
				blocks = initialize_level3();
				bl_color = 0x00ffff;
			}
			current_gamemode = GM_GAMEPLAY;
		}
		
	}
	
}
