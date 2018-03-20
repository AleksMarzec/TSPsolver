#pragma once

//Singleton - https://rosettacode.org/wiki/Singleton#Thread_safe_.28since_C.2B.2B11.29
//http://stackoverflow.com/q/41328038, http://stackoverflow.com/a/2143606
template <typename T>
class Singleton
{
protected:
	Singleton() {};
	~Singleton() {};

public:
	static T & Instance()
	{
		// Since it's a static variable, if the class has already been created,
		// It won't be created again.
		// And it **is** thread-safe in C++11.
		static T myInstance;

		// Return a reference to our instance.
		return myInstance;
	}

	//Usuwanie konstruktora kopiuj¹cego (copy constructor) i przenosz¹cego (move constructor) oraz operatorów przypisania (assign operators).
	Singleton(Singleton const&) = delete;             // Copy construct
	Singleton(Singleton&&) = delete;                  // Move construct
	Singleton& operator=(Singleton const&) = delete;  // Copy assign
	Singleton& operator=(Singleton &&) = delete;      // Move assign
};