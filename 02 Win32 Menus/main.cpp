// When starting from scratch:
// Check project configuration. Linker->System->SubSystem should be Windows.

#include <windows.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void addMenus(HWND hWnd);

HMENU hMenu; // Variable for the menu.

// The _In_ and _In_out_ are Source-code Annotation Language (SAL). ¯\_(ツ)_/¯
// Read more here: https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-2010/ms235402(v=vs.100)?redirectedfrom=MSDN
int WINAPI WinMain(_In_ HINSTANCE hInst, _In_opt_ HINSTANCE hPrevInst, _In_ LPSTR args, _In_ int nCmdShow) {

	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"myWindowClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc)) return -1; // Return -1 if it failed to register the window.

	// If the registration was succeful, then it's possible to register the window.
	CreateWindowW(L"myWindowClass", L"My First Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, NULL, NULL, NULL, NULL);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg); // This calls the WindowProcedure for processing the message.
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
	case WM_COMMAND: // Created for every button or menu item clicked.
		switch (wp)
		{
		case 1: // Identified through the ID for the menu.
			MessageBeep(MB_OK);
			break;

		default:
			break;
		}
		break;

	case WM_CREATE: // Called once. Great to add stuff when a windows is created.
		addMenus(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0); // Makes the next GetMessage call return false.
		break;

	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}

void addMenus(HWND hWnd) {
	hMenu = CreateMenu();

	AppendMenu(hMenu, MF_STRING, 1, L"File"); // Value 1 is used in WindowProcedure for wp, to identify what to do.
	AppendMenu(hMenu, MF_STRING, NULL, L"Help");

	SetMenu(hWnd, hMenu);
}