#include <windows.h>
#include <cstdio>

HWND textfield, add, min, mul, divide, TextBox1, TextBox2;
char numchar1[20], numchar2[20];

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
        case WM_CREATE:
            textfield = CreateWindow("STATIC", "Plase input two numbers",WS_VISIBLE|WS_CHILD,
                                      40, 10, 160, 17, hwnd, NULL, NULL, NULL);
            TextBox1 = CreateWindow("EDIT", "", WS_VISIBLE|WS_CHILD|WS_BORDER,
                                      40, 40, 160, 25, hwnd, NULL, NULL, NULL);
            TextBox2 = CreateWindow("EDIT", "", WS_VISIBLE|WS_CHILD|WS_BORDER,
                                      40, 70, 160, 25, hwnd, NULL, NULL, NULL);
            add = CreateWindow("BUTTON", "+",WS_VISIBLE|WS_CHILD|WS_BORDER,
                                      63, 125, 25, 25, hwnd, (HMENU) 1, NULL, NULL);
            min = CreateWindow("BUTTON", "-",WS_VISIBLE|WS_CHILD|WS_BORDER,
                                      93, 125, 25, 25, hwnd, (HMENU) 2, NULL, NULL);
            mul = CreateWindow("BUTTON", "*",WS_VISIBLE|WS_CHILD|WS_BORDER,
                                      123, 125, 25, 25, hwnd, (HMENU) 3, NULL, NULL);
            divide = CreateWindow("BUTTON", "/",WS_VISIBLE|WS_CHILD|WS_BORDER,
                                      153, 125, 25, 25, hwnd, (HMENU) 4, NULL, NULL);
            break;

        case WM_COMMAND:
            double Result, num1, num2;
            GetWindowText(TextBox1, numchar1, 20);
            GetWindowText(TextBox2, numchar2, 20);
            num1 = atof(numchar1);
            num2 = atof(numchar2);
            char t[20];
            switch(LOWORD(wParam)){
                case 0:
                    break;
                case 1:
                    Result = num1 + num2;
                    sprintf(t, "%f", Result);
                    ::MessageBox(hwnd, t, "Result", MB_OK);
                    break;
                case 2:                              
                    Result = num1 - num2;
                    sprintf(t, "%f", Result);
                    ::MessageBox(hwnd, t, "Result", MB_OK);
                    break;
                case 3:            
                    Result = num1 * num2;
                    sprintf(t, "%f", Result);
                    ::MessageBox(hwnd, t, "Result", MB_OK);
                    break;
                case 4:              
                    Result = num1 / num2;
                    sprintf(t, "%f", Result);
                    ::MessageBox(hwnd, t, "Result", MB_OK);
                    break;
            }

            break;

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
	wc.hbrBackground = (HBRUSH)(14);
	wc.lpszClassName = "WindowClass";
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","My Calculator",WS_VISIBLE|WS_SYSMENU,
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