#include <windows.h>

// Procedure (message handling) for the window being created.
LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int nCmdShow) {
	// MessageBox(NULL, L"HELLO!", L"My First Win32 API", MB_OK);

	// Structure used for creating a new windows.
	WNDCLASSW wc = { 0 };

	// Read more on: https://docs.microsoft.com/en-us/windows/win32/api/winuser/ns-winuser-wndclassw
	// Definitions (basic attributes for creating a class)
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // IDC_ARROW
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;
	
	// Registering the application (and checking if it failed).
	if (!RegisterClassW(&wc)) return -1; // Return -1 if it failed to register the window.

	// If the registration was succeful, then it's possible to register the window.
	CreateWindowW(L"myWindowClass", L"My First Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, NULL, NULL, NULL, NULL);
		// The second argument is the title on the top of the window.
		// The third argument is the style of window.

	MSG msg = { 0 };


	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg); // Thiw calls the WindowProcedure for processing the message.
	}

	return 0;
}

/*
* hWnd - Window for whom this function is being called.
* msg  - The message received for this functions.
*/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0); // Makes the next GetMessage call return false.
		break;

	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

// When starting from scratch:
// Check project configuration. Linker->System->SubSystem should be Windows.