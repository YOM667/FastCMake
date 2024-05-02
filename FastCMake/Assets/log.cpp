#include "log.h"

namespace youm::utility
{
	const char* Logger::levels[LEVEL_COUNT] = {
		"DEBUG", "INFO", "WARN", "ERROR", "FATAL"
	};

	Logger* Logger::logInstance = nullptr;

	Logger::Logger()
	{
		string filePath = "./log/";
		if (!filesystem::exists(filePath))
		{
			filesystem::create_directory(filePath);
		}
		this->localFile = filePath + "crash_" + getTime("%Y-%m-%d %H_%M_%S") + ".log";

		this->open();
	}
	Logger::~Logger()
	{
		close();
	}
	Logger* Logger::instance()
	{
		if (logInstance == nullptr)
		{
			logInstance = new Logger();
		}
		return logInstance;
	}

	void Logger::open()
	{
		try
		{
			outStream.exceptions(ofstream::failbit | ofstream::badbit);
			outStream.open(this->localFile, ios::app);
			outStream.exceptions(std::ofstream::goodbit);
		}
		catch (ofstream::failure const& exception)
		{
			cout << exception.what() << endl; 
		}
	}

	void Logger::close()
	{
		outStream.close();
	}

	void Logger::log(Level level, const char* file, int line, const char* message, ...)
	{
		const char* format = LOGGER_OUTPUT_FORMAT;
		int size = snprintf(nullptr, 0, format, utility::getTime(LOGGER_TIME_FORMAT).c_str(), levels[level], file, line);
		if (size > 0)
		{
			char* buffer = new char[size + 1];
			snprintf(buffer, static_cast<size_t>(size) + 1, format, utility::getTime(LOGGER_TIME_FORMAT).c_str(), levels[level], file, line);
			buffer[size] = 0;
			cout << buffer;
			outStream << buffer;
			delete[] buffer;
		}
		va_list argPointer;
		va_start(argPointer, message);
		size = vsnprintf(nullptr, 0, message, argPointer);
		va_end(argPointer);
		if (size > 0)
		{
			char* content = new char[size + 1];
			va_start(argPointer, message);
			vsnprintf(content, static_cast<size_t>(size) + 1, message, argPointer);
			va_end(argPointer);
			cout << content << endl;
			outStream << content;
		}
		outStream << "\n";
		outStream.flush();
	}
}