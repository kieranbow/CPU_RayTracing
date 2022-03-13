#pragma once
#include <string>
#include <iostream>

#include <Windows.h>

// Logger class that outputs msg related to error, warning and standard msg with colour
class Logger
{
	public:
		// https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text

		Logger() = default;
		~Logger() = default;

		static void PrintWarning(std::string msg)
		{
			// Sets the text "[Warn]" with a Yellow background and black text
			SetConsoleTextAttribute(hConsole, backYellow_blkText);
			std::cout << "[Warn]";

			// Sets the msg with a white text
			SetConsoleTextAttribute(hConsole, whiteText);
			std::cout << " " << msg << std::endl;
		}
		static void PrintError(std::string msg)
		{
			// Sets the text "[Error]" with a Red background and black text
			SetConsoleTextAttribute(hConsole, backRed_blkText);
			std::cout << "[Error]";

			// Sets the msg with a white text
			SetConsoleTextAttribute(hConsole, whiteText);
			std::cout << " " << msg << std::endl;
		}
		static void PrintDebug(std::string msg)
		{
			// Sets the text "[Debug]" with a Red background and black text
			SetConsoleTextAttribute(hConsole, backcyan_blkText);
			std::cout << "[Debug]";

			// Sets the msg with a white text
			SetConsoleTextAttribute(hConsole, whiteText);
			std::cout << " " << msg << std::endl;
		}
		static void PrintMsg(std::string msg)
		{
			// Sets the msg with a white text
			SetConsoleTextAttribute(hConsole, whiteText);
			std::cout << "[Msg] " << msg << std::endl;
		}

	private:
		static inline HANDLE hConsole { GetStdHandle(STD_OUTPUT_HANDLE) };

		// Text Colour
		static inline int redText { 12 };
		static inline int yellowText { 14 };
		static inline int whiteText { 15 };

		// Background colour with Text colour
		static inline int backcyan_blkText{ 176 };
		static inline int backRed_blkText { 192 };
		static inline int backYellow_blkText { 224 };
};
