#pragma once
#include "main.h"
#include <iostream>

int wmain(int argc, wchar_t* argv[])
{
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);
	stdErrorHandle	= GetStdHandle(STD_ERROR_HANDLE);
	stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	stdInputHandle	= GetStdHandle(STD_INPUT_HANDLE);
	ConsoleWindow = GetConsoleWindow();
	if (GetConsoleScreenBufferInfoEx(stdOutputHandle, &consoleScreenBufferInfoEx) != 0)
	{
		consoleScreenBufferInfoEx.dwSize.X = 25;
		consoleScreenBufferInfoEx.dwSize.Y = 80;
		consoleScreenBufferInfoEx.srWindow.Left = 0;									//The x-coordinate of the upper left corner of the rectangle.
		consoleScreenBufferInfoEx.srWindow.Top = 0;										//The y-coordinate of the upper left corner of the rectangle.
		consoleScreenBufferInfoEx.srWindow.Right = consoleScreenBufferInfoEx.dwSize.X;  //The x-coordinate of the lower right corner of the rectangle.
		consoleScreenBufferInfoEx.srWindow.Bottom = consoleScreenBufferInfoEx.dwSize.Y; //The y-coordinate of the lower right corner of the rectangle.
		if (!SetConsoleScreenBufferInfoEx(stdOutputHandle, &consoleScreenBufferInfoEx))
		{
			std::cout << "Error: " << GetLastError() << std::endl;
		}
		else
		{
			std::cout << "Sucessful: " << GetLastError() << std::endl;
		}
	}
	else
	{
		DWORD dwDesiredAccess = GENERIC_READ | GENERIC_WRITE;
		DWORD dwShareMode = 0;
		if ((stdOutputHandle = CreateConsoleScreenBuffer(dwDesiredAccess, dwShareMode, NULL, CONSOLE_TEXTMODE_BUFFER, NULL)) != INVALID_HANDLE_VALUE)
		{
			if (!SetConsoleActiveScreenBuffer(stdOutputHandle))
			{
				std::cout << "Coudldn't Activate new screen buffer." << std::endl;
			}
		}
		else
		{
			std::cout << "Error: " << GetLastError() << std::endl;
		}
		stdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		consoleScreenBufferSize.X = 160;
		consoleScreenBufferSize.Y = 50;
		consoleScreenBufferRect.Left = 0;							//The x-coordinate of the upper left corner of the rectangle.
		consoleScreenBufferRect.Top = 0;							//The y-coordinate of the upper left corner of the rectangle.
		consoleScreenBufferRect.Right = (consoleScreenBufferSize.X - 1);  //The x-coordinate of the lower right corner of the rectangle.
		consoleScreenBufferRect.Bottom = (consoleScreenBufferSize.Y - 1); //The y-coordinate of the lower right corner of the rectangle.
		if (SetConsoleScreenBufferSize(stdOutputHandle, consoleScreenBufferSize) == 0)
		{
			std::cout << "Failed to set new screen buffer size. " << GetLastError() << std::endl;
		}

		//SetConsoleScreenBufferInfoEx()
		if (SetConsoleWindowInfo(stdOutputHandle, TRUE, &consoleScreenBufferRect) == 0)
		{
			std::cout << "Failed to set new window size." << GetLastError() << std::endl;
		}
		if (!SetConsoleActiveScreenBuffer(stdOutputHandle))
		{
			std::cout << "Coudldn't Activate new screen buffer." << std::endl;
		}
		GetConsoleScreenBufferInfo(stdOutputHandle, &consoleScreenBufferInfo);
		
		//int positionX = (screenWidth + consoleScreenBufferSize.X) / 2;
		//int positionY = (screenHeight + consoleScreenBufferSize.Y) / 2;
		//COORD screen = GetLargestConsoleWindowSize(stdOutputHandle);
		//int height = (screenHeight / 2) - screen.Y ;
		//MoveWindow(ConsoleWindow, positionX, height, screenWidth, screenHeight, TRUE);
		//COORD lpNewScreenBufferDimensions;
		//SetConsoleDisplayMode(stdOutputHandle, CONSOLE_FULLSCREEN_HARDWARE, &lpNewScreenBufferDimensions);
		RECT windowSize;
		RECT DesktopResolutionRect;
		HWND DesktopScreen = GetDesktopWindow();
		ConsoleWindow = GetConsoleWindow();
		GetWindowRect(DesktopScreen, &DesktopResolutionRect);
		GetWindowRect(ConsoleWindow, &windowSize);
		int width = windowSize.right - windowSize.left;
		int height = windowSize.bottom - windowSize.top;
		int PositionX = ((DesktopResolutionRect.right - DesktopResolutionRect.left) / 2 - width / 2);
		int PositionY = ((DesktopResolutionRect.bottom - DesktopResolutionRect.top) / 2 - height / 2);

		SetWindowPos(ConsoleWindow, NULL, PositionX, PositionY, width, height, SWP_NOZORDER | SWP_NOSIZE);
		int a = 0;
	}	
	lpBuffer.resize((consoleScreenBufferSize.X * consoleScreenBufferSize.Y));
	Render();
	int a = 0;
	std::cin >> a;
	return 0;
}

void Render()
{
	COORD firstCell = { 0, 0 };
	for (CHAR_INFO& itr : lpBuffer)
	{
		itr.Attributes = BACKGROUND_BLUE + FOREGROUND_GREEN;
		itr.Char.UnicodeChar = 'F';
		itr.Char.AsciiChar = 'F';
	}
	WriteConsoleOutput(stdOutputHandle, lpBuffer.data(), consoleScreenBufferSize, firstCell, &consoleScreenBufferRect);
}

void Update()
{

}