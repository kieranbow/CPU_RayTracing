#pragma once
#include <string>
#include <iostream>

#include <Windows.h>

// Logger class that outputs msg related to error, warning and standard msg with colour
class Logger
{
	public:
		// https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text

		Logger()
		{
			hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		}
		~Logger() = default;

		void PrintWarning(std::string msg)
		{
			// Sets the text "[Warn]" with a Yellow background and black text
			SetConsoleTextAttribute(hConsole, backYellow_blkText);
			std::cout << "[Warn]";

			// Sets the msg with a white text
			SetConsoleTextAttribute(hConsole, whiteText);
			std::cout << " " << msg << std::endl;
		}
		void PrintError(std::string msg)
		{
			// Sets the text "[Error]" with a Red background and black text
			SetConsoleTextAttribute(hConsole, backRed_blkText);
			std::cout << "[Error]";

			// Sets the msg with a white text
			SetConsoleTextAttribute(hConsole, whiteText);
			std::cout << " " << msg << std::endl;
		}
		void PrintMsg(std::string msg)
		{
			// Sets the msg with a white text
			SetConsoleTextAttribute(hConsole, whiteText);
			std::cout << "[Msg] " << msg << std::endl;
		}

	private:
		HANDLE hConsole;

		// Text Colour
		int redText = 12;
		int yellowText = 14;
		int whiteText = 15;

		// Background colour with Text colour
		int backRed_blkText = 192;
		int backYellow_blkText = 224;
};
