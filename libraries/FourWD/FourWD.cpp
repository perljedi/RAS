/*
 *   FourWD.cpp - Library for driving a Simple 4WD rover
 *     Created by Dave Mueller, March 2nd, 2014
 *       Released into the public domain.
 *       */
#include <Arduino.h>
#include <FourWD.h>

int _rf, _rr, lf, lr;

FourWD::FourWD(int rf, int rr, int lf, int lr){
    _rf = rf;
    _rr = rr;
    _lf = lf;
    _lr = lr;
    pinMode(_rf, OUTPUT);
    pinMode(_rr, OUTPUT);
    pinMode(_lf, OUTPUT);
    pinMode(_lr, OUTPUT);
    digitalWrite(_rf, LOW);
    digitalWrite(_rr, LOW);
    digitalWrite(_lf, LOW);
    digitalWrite(_lr, LOW);
}


void FourWD::forward(){
    digitalWrite(_lf, HIGH);
    digitalWrite(_rf, HIGH);
    digitalWrite(_lr, LOW);
    digitalWrite(_rr, LOW);
}

void FourWD::reverse(){
    digitalWrite(_lf, LOW);
    digitalWrite(_rf, LOW);
    digitalWrite(_lr, HIGH);
    digitalWrite(_rr, HIGH);
}

void FourWD::turnLeft(){
    digitalWrite(_rf, LOW);
    digitalWrite(_lf, HIGH);
    digitalWrite(_lr, LOW);
    digitalWrite(_rr, LOW);  
}

void FourWD::turnRight(){
    digitalWrite(_rf, HIGH);
    digitalWrite(_lf, LOW);
    digitalWrite(_lr, LOW);
    digitalWrite(_rr, LOW);  
}

void FourWD::rotateLeft(){
    digitalWrite(_lf, HIGH);
    digitalWrite(_rf, LOW);
    digitalWrite(_lr, LOW);
    digitalWrite(_rr, HIGH);  
}

void FourWD::rotateRight(){
    digitalWrite(_lf, LOW);
    digitalWrite(_rf, HIGH);
    digitalWrite(_lr, HIGH);
    digitalWrite(_rr, LOW);  
}

void FourWD::stop(){
    digitalWrite(_lf, LOW);
    digitalWrite(_rf, LOW);
    digitalWrite(_lr, LOW);
    digitalWrite(_rr, LOW);
}

void FourWD::brake(){
    digitalWrite(_lf, HIGH);
    digitalWrite(_rf, HIGH);
    digitalWrite(_lr, HIGH);
    digitalWrite(_rr, HIGH);
}
