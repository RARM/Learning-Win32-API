#include <windows.h>
#include <stdlib.h>
#include <gl/GL.h>

void draw();
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

int WINAPI WinMain(
	_In_ HINSTANCE hInst, 
	_In_opt_ HINSTANCE hPrevInst, 
	_In_ LPSTR args, 
	_In_ int nCmdShow) {
	
	// Register Class
	WNDCLASSW wc = { 0 };

	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // IDC_ARROW
	wc.hInstance = hInst;
	wc.lpszClassName = L"OpenGLClass";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc)) exit(EXIT_FAILURE);

	// Create Window
	HWND hWnd = CreateWindowW(L"OpenGLClass", L"Hello OpenGL", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 800, 600, NULL, NULL, NULL, NULL);

	// Setting the OpenGL Context
	HDC hdc = GetDC(hWnd);

	{
		// Setting Pixel Format
		int pixelFormat;
		PIXELFORMATDESCRIPTOR pixelFormatDesc;

		/* initialize bits to 0 */
		memset(&pixelFormatDesc, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pixelFormatDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pixelFormatDesc.nVersion = 1;
		pixelFormatDesc.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
		pixelFormatDesc.iPixelType = PFD_TYPE_RGBA;
		pixelFormatDesc.cColorBits = 32;
		pixelFormatDesc.cAlphaBits = 8;
		pixelFormatDesc.cDepthBits = 24;

		pixelFormat = ChoosePixelFormat(hdc, &pixelFormatDesc);
		SetPixelFormat(hdc, pixelFormat, &pixelFormatDesc);
	}

	HGLRC renderContext = wglCreateContext(hdc);

	wglMakeCurrent(hdc, renderContext);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg = { 0 };

	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	LRESULT result = 0;
	PAINTSTRUCT ps;
	
	switch (msg)
	{
	case WM_PAINT:
		result = 0; // Return -1 to exit (if it fails creation for WM_CREATE).
		draw();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break; 

	case WM_DESTROY:
		PostQuitMessage(0);
		result = 0; // Is this right?
		break;

	default:
		result = DefWindowProcW(hWnd, msg, wp, lp);
	}

	return result;
}

// OpenGL
void draw() {
	glClearColor(0.0F, 0.0F, 0.0F, 0.0F);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}