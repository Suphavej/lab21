#include <windows.h>
#include<stdio.h>

HWND hInput1, hInput2, hAddButton, hSubButton, hMulButton, hDivButton;
void ShowResult(HWND hwnd, double result) {
	double x = result;
	char t[100];
	sprintf(t, "%.2f", x);

	MessageBox(hwnd, t, "Result",MB_OK | MB_ICONINFORMATION);

}
void CreateCalculatorComponents(HWND hwnd){
	hInput1 = CreateWindow("EDIT", "" , WS_CHILD | WS_VISIBLE | WS_BORDER, 30, 20, 80, 25, hwnd ,NULL, NULL, NULL);
	hInput2 = CreateWindow("EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 20, 80, 25, hwnd, NULL, NULL, NULL);
	hAddButton = CreateWindow("BUTTON", "+", WS_CHILD | WS_VISIBLE, 30, 70, 40, 40, hwnd, (HMENU)1, NULL, NULL);
    hSubButton = CreateWindow("BUTTON", "-", WS_CHILD | WS_VISIBLE, 80, 70, 40, 40, hwnd, (HMENU)2, NULL, NULL);
    hMulButton = CreateWindow("BUTTON", "*", WS_CHILD | WS_VISIBLE, 130, 70, 40, 40, hwnd, (HMENU)3, NULL, NULL);
    hDivButton = CreateWindow("BUTTON", "/", WS_CHILD | WS_VISIBLE, 180, 70, 40, 40, hwnd, (HMENU)4, NULL, NULL);
}	
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	switch(Message) {
		
			case WM_CREATE:
				CreateCalculatorComponents(hwnd);
				break;
	
			case WM_COMMAND:
				if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
					char buffer1[256], buffer2[256];
					GetWindowText(hInput1, buffer1, 100);
					GetWindowText(hInput2, buffer2, 100);
	
					double num1 = atof(buffer1);
					double num2 = atof(buffer2);
					double result = 0.0;
	
					switch (LOWORD(wParam)) {
						case 1: result = num1 + num2; break;  
						case 2: result = num1 - num2; break;  
						case 3: result = num1 * num2; break;  
						case 4:  
							if (num2 != 0) {
								result = num1 / num2;
							} else {
								MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
								return 0;
							}
							break;
					}
	
					ShowResult(hwnd, result);
				}
				break;
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}


/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+9);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,  
		
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
