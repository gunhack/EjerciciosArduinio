#ifndef DISP7S4D_H_
#define DISP7S4D_H_

class Disp7S4D {

public:

  Disp7S4D(const int PIN_SEGS[8], const int PIN_DIGITS[4]);
  ~Disp7S4D(){}
  void printNum(const int& number);
  void printTime(const int& hour, const int& min);

private:

	int* segs;
	int* digits;
	static const String numbers[];
};

#endif // DISP7S4D_H_
