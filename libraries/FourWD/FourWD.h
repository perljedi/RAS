#ifndef FourWD_h
#define FourWD_h

#include "Arduino.h"

class FourWD
{
    public:
        FourWD(int rf, int rr, int lf, int lr);
        void forward();
        void reverse();
        void turnLeft();
        void turnRight();
        void rotateLeft();
        void rotateRight();
        void stop();
	void brake();

    private:
        int _rf, _rr, _lf, _lr;

};

#endif
