#include <windows.h>
#include "utils.cpp"
#include <cmath>
#include <vector>

/**
 * running показывает состояние программы.
 */
bool running = true;
/**
 * width и height устанавливают размер окна.
 */
int width = 1280, height = 720;
/**
 * size показывает место, которое окно занимает в памяти.
 */
int size = height*width*sizeof(u32);
/**
 * memory - указатель к ячейкам памяти.
 */
void* memory = VirtualAlloc(0, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
/**
 * bitmap_info хранит в себе настройки окна.
 */
BITMAPINFO bitmap_info;

/**
* Функция window_callback отслеживает состояние окна работающего приложения
* @param hwnd - это дескриптор окна.
* @param uMsg - это неподписанный INT, показывает состояние окна.
* @param wParam - это параметр сообщения.
* @param lParam - это параметр сообщения.
* @return Функция возвращает значение функции окна по умолчанию с указанными параметрами.
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
* current_gamemode показывает состояние игрового процесса.
*/
Gamemode current_gamemode = GM_MENU;

#include "platform_common.cpp"
#include "renderer.cpp"
#include "levels.cpp"
#include "sim.cpp"

/**
* Функция WinMain запускает в себе все события игрового процесса. Аналог main в обычных c++ программах.
* @param hInstance - это дескриптор экземпляра.
* @param uhPrevInstance - это дескриптор предыдущего экземпляра. В функции не используется.
* @param lpCmdLine - это указатель на строку, завершаемую null, из 8-разрядных символов Windows (ANSI). В функции не используется.
* @param nShowCmd - это int значение. В функции не используется.
* @return Функция возвращает 0 при успешном выполнении.
*/
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	bitmap_info.bmiHeader.biSize = sizeof(bitmap_info.bmiHeader);
	bitmap_info.bmiHeader.biWidth = width;
	bitmap_info.bmiHeader.biHeight = height;
	bitmap_info.bmiHeader.biPlanes = 1;
	bitmap_info.bmiHeader.biBitCount = 32;
	bitmap_info.bmiHeader.biCompression = BI_RGB;
	/**
	* window_class - экземпляр WNDCLASS.
	*/
	WNDCLASS window_class = {};
	window_class.style = CS_HREDRAW | CS_VREDRAW;
	window_class.lpszClassName = L"Game Window Class";
	window_class.lpfnWndProc = window_callback;

	RegisterClass(&window_class);

	/**
	* window - созданный экземпляр окна.
	*/
	HWND window = CreateWindow(window_class.lpszClassName, L"Arkanoid", WS_OVERLAPPEDWINDOW | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, width, height, 0, 0, hInstance, 0);
	HDC hdc = GetDC(window);

	/**
	* input - принимает ввод игрока.
	*/
	Input input = {};

	/**
	* delta_time - хранит в себе разницу времени между кадрами.
	*/
	float delta_time = 0.0166666f;
	/**
	* frame_begin_time - хранит в себе время начала кадра.
	*/
	LARGE_INTEGER frame_begin_time;
	QueryPerformanceCounter(&frame_begin_time);

	/**
	* performance_frequency - характеризует перформанс.
	*/
	float performance_frequency;
	{
		LARGE_INTEGER perf;
		QueryPerformanceFrequency(&perf);
		performance_frequency = (float)perf.QuadPart;
	}


	while (running) {
		/**
		* message - экземпляр MSG. Отвечает за ввод.
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
		* frame_end_time - хранит в себе время конца кадра.
		*/
		LARGE_INTEGER frame_end_time;
		QueryPerformanceCounter(&frame_end_time);
		delta_time = (float)(frame_end_time.QuadPart - frame_begin_time.QuadPart) / performance_frequency;
		frame_begin_time = frame_end_time;
	}
}
