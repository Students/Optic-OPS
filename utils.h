
#ifndef __UTILS_HEADER__
#define __UTILS_HEADER__

#include <cstdlib>
#include <cmath>
#include <cstring>

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <stack>
#include <stdexcept>
#include <sstream>

#include "al.h"
#include "alc.h"

#ifdef _WIN32
	#include <windows.h>
#endif

typedef int32_t   int32;
typedef uint32_t  uint32;
typedef int16_t   int16;
typedef uint16_t  uint16;
typedef int8_t    int8;
typedef uint8_t   uint8;

extern bool UTILS_DEBUG;

const float UTILS_QUARTER_PI = 0.785398163f;
const float UTILS_HALF_PI    = 1.570796326f;
const float UTILS_PI         = 3.141592653f;
const float UTILS_2PI        = 6.283185307f;

uint32 RoundUpPow2(uint32 x);

bool IsPowerOfTwo(uint32 x);

bool IsOddNumber(uint32 x);

bool IsFloatInRange(float value, float lower, float upper);

bool IsFloatEqual(float value, float base, float delta = 0.001f);

class Exception
{
public:
    Exception(const std::string & message, const std::string & file="", const int line=-1, const std::string & function="") throw();

    virtual ~Exception() throw();

    virtual std::string ToString() const throw();

    virtual std::string GetMessage() const throw();

    virtual std::string GetFile() const throw();

    virtual int GetLine() const throw();

    virtual std::string GetFunction() const throw();

private:
    const std::string _message;
    const std::string _file;
    const int _line;
    const std::string _function;
};

template<typename T> class Singleton {
protected:
	static T* _singleton_reference;

	Singleton()
		{}

	virtual ~Singleton()
		{}

public:
	static T* SingletonCreate() {
		if (_singleton_reference == NULL) {
			_singleton_reference = new T();
		}
		else {
			if (UTILS_DEBUG)
				std::cerr << "UTILS WARNING: Singleton::SingletonCreate() was invoked when the class object was already instantiated" << std::endl;
		}
		return _singleton_reference;
	}

	static void SingletonDestroy() {
		if (_singleton_reference != NULL) {
			delete _singleton_reference;
		}
		else {
			if (UTILS_DEBUG)
				std::cerr << "UTILS WARNING: Singleton::SingletonDestroy() was invoked when the class object was not instantiated" << std::endl;
		}
		_singleton_reference = NULL;
	}

	static const T* SingletonGetReference()
		{ return _singleton_reference; }

	virtual bool SingletonInitialize() = 0;

private:
	Singleton(const Singleton &s);
	Singleton& operator=(const Singleton &s);
};

template <typename T>
std::string NumberToString(const T t)
{
	std::ostringstream text("");
	text << static_cast<int32>(t);
	return text.str();
}

std::string MakeStandardString(const hoa_utils::ustring& text);

float RandomFloat();

float RandomFloat(float a, float b);

int32 RandomBoundedInteger(int32 lower_bound, int32 upper_bound);

int32 GaussianRandomValue(int32 mean, float std_dev = 10.0f, bool positive_value = true);

bool Probability(uint32 chance);

template <typename T>
void InsertionSort(std::vector<T>& swap_vec) {
	int32 i, j;
	T value;
	for (i = 1; i < swap_vec.size(); i++) {
		value = swap_vec[i];
		for (j = i - 1; j >= 0 && swap_vec[j] > value; j--) {
			swap_vec[j+1] = swap_vec[j];
		}
		swap_vec[j+1] = value;
	}
}

bool DoesFileExist(const std::string& file_name);

bool MoveFile(const std::string& source_name, const std::string& destination_name);

void CopyFile(const std::string& source, const std::string& destination);

bool CleanDirectory(const std::string& dir_name);

bool MakeDirectory(const std::string& dir_name);

bool RemoveDirectory(const std::string& dir_name);

std::vector<std::string> ListDirectory(const std::string& dir_name, const std::string& filter);

bool DeleteFile(const std::string& filename);

const std::string GetUserDataPath(bool user_files = true);

const std::string GetUserProfilePath();

const std::string GetSettingsFilename();

#endif
