#include <windows.h>
#include "utils.cpp"
#include <cmath>
#include <vector>

/**
 * running ���������� ��������� ���������.
 */
bool running = true;
/**
 * width � height ������������� ������ ����.
 */
int width = 1280, height = 720;
/**
 * size ���������� �����, ������� ���� �������� � ������.
 */
int size = height*width*sizeof(u32);
/**
 * memory - ��������� � ������� ������.
 */
void* memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
/**
 * bitmap_info ������ � ���� ��������� ����.
 */
BITMAPINFO bitmap_info;

/**
* ������� window_callback ����������� ��������� ���� ����������� ����������
* @param hwnd - ��� ���������� ����.
* @param uMsg - ��� ������������� INT, ���������� ��������� ����.
* @param wParam - ��� �������� ���������.
* @param lParam - ��� �������� ���������.
* @return ������� ���������� �������� ������� ���� �� ��������� � ���������� �����������.
*/
LRESULT CALLBACK window_callback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	LRESULT result = 0;
	switch (uMsg) {
		case WM_CLOSE:
		case WM_DESTROY: {
			running = false;
		} break;
		default: {
			result = DefWindowProc(hwnd, uMsg, wParam, lParam); break;
		}
	}
	return result;
}

enum Gamemode {
	GM_MENU,
	GM_GAMEPLAY,
};

/**
* current_gamemode ���������� ��������� �������� ��������.
*/
Gamemode current_gamemode = GM_MENU;

#include "platform_common.cpp"
#include "renderer.cpp"
#include "levels.cpp"
#include "sim.cpp"

/**
* ������� WinMain ��������� � ���� ��� ������� �������� ��������. ������ main � ������� c++ ����������.
* @param hInstance - ��� ���������� ����������.
* @param uhPrevInstance - ��� ���������� ����������� ����������. � ������� �� ������������.
* @param lpCmdLine - ��� ��������� �� ������, ����������� null, �� 8-��������� �������� Windows (ANSI). � ������� �� ������������.
* @param nShowCmd - ��� int ��������. � ������� �� ������������.
* @return ������� ���������� 0 ��� �������� ����������.
*/
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
	bitmap_info.bmiHeader.biWidth = width;
	bitmap_info.bmiHeader.biHeight = height;
	bitmap_info.bmiHeader.biPlanes = 1;
	bitmap_info.bmiHeader.biBitCount = 32;
	bitmap_info.bmiHeader.biCompression = BI_RGB;
	/**
	* window_class - ��������� WNDCLASS.
	*/
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;

	RegisterClass(&window_class);

	/**
	* window - ��������� ��������� ����.
	*/
	HWND window = CreateWindow(window_class.lpszClassName, L"Arkanoid", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	/**
	* input - ��������� ���� ������.
	*/
	Input input = {};

	/**
	* delta_time - ������ � ���� ������� ������� ����� �������.
	*/
	float delta_time = 0.0166666f;
	/**
	* frame_begin_time - ������ � ���� ����� ������ �����.
	*/
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	/**
	* performance_frequency - ������������� ����������.
	*/
	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}


	while (running) {
		/**
		* message - ��������� MSG. �������� �� ����.
		*/
		MSG message;

		for (int i = 0; i < BUTTON_COUNT; i++) {
			input.buttons[i].changed = false;
		}

		while (PeekMessage(&message, window, 0, 0, PM_REMOVE)) {

			switch (message.message) {
			case WM_KEYUP:
			case WM_KEYDOWN: {
				u32 vk_code = (u32)message.wParam;
				bool is_down = ((message.lParam & (1 << 31)) == 0);

#define process_button(b, vk)\
case vk: {\
	input.buttons[b].is_down = is_down;\
	input.buttons[b].changed = true;\
} break;

				switch (vk_code) {
					process_button(BUTTON_LEFT, VK_LEFT);
					process_button(BUTTON_RIGHT, VK_RIGHT);
					process_button(BUTTON_ENTER, VK_RETURN);
				}
			}break;

			default: {
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
			}
		}

		simulate_game(&input, delta_time);

		StretchDIBits(hdc, 0, 0, width, height, 0, 0, width, height, memory, &bitmap_info, DIB_RGB_COLORS,SRCCOPY);

		/**
		* frame_end_time - ������ � ���� ����� ����� �����.
		*/
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}
}
