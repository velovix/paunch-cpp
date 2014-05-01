#include "paunch.h"

namespace paunch {

Physics::Physics() {

	this->accel = this->maxAccel = this->minAccel = this->friction = Double2(0, 0);
	this->movers = new std::vector<Mover*>;
}

void Physics::SetMovers(std::vector<Mover*> *movers) {

	this->movers = movers;
}

std::vector<Mover*> *Physics::GetMovers() {

	return this->movers;
}

void Physics::AddForce(std::string name, double forceX, double forceY) {

	if(this->forces.count(name) <= 0) {
		this->forces[name] = force{Double2(forceX, forceY), false};
	} else {
		this->forces[name].magnitude = Double2(forceX, forceY);
	}
}

void Physics::EnableForce(std::string name) {

	if(this->forces.count(name) > 0) {
		this->forces[name].active = true;
	}
}

void Physics::DisableForce(std::string name) {

	if(this->forces.count(name) > 0) {
		this->forces[name].active = false;
	}
}

void Physics::DeleteForce(std::string name) {

	if(this->forces.count(name) > 0) {
		this->forces.erase(name);
	}
}

void Physics::Accelerate(double forceX, double forceY) {

	this->accel.x += forceX;
	this->accel.y += forceY;
}

void Physics::SetAcceleration(double force, int axis) {

	if(axis == X) {
		this->accel.x = force;
	} else if(axis == Y) {
		this->accel.y = force;
	} else {
		throw Error("Invalid axis value");
	}
}

void Physics::SetAcceleration(double forceX, double forceY) {

	this->accel = Double2(forceX, forceY);
}

void Physics::SetMaxAcceleration(double force, int axis) {

	if(axis == X) {
		this->usingMaxAccel[axis] = true;
		this->maxAccel.x = force;
	} else if(axis == Y) {
		this->usingMaxAccel[axis] = true;
		this->maxAccel.y = force;
	} else {
		throw Error("Invalid axis value");
	}
}

void Physics::SetMaxAcceleration(double forceX, double forceY) {

	this->usingMaxAccel[X] = true;
	this->usingMaxAccel[Y] = true;
	this->maxAccel = Double2(forceX, forceY);
}

void Physics::SetMinAcceleration(double force, int axis) {

	if(axis == X) {
		this->usingMinAccel[axis] = true;
		this->minAccel.x = force;
	} else if(axis == Y) {
		this->usingMinAccel[axis] = true;
		this->minAccel.y = force;
	} else {
		throw Error("Invalid axis value");
	}
}

void Physics::SetMinAcceleration(double forceX, double forceY) {

	this->usingMinAccel[X] = true;
	this->usingMinAccel[Y] = true;
	this->minAccel = Double2(forceX, forceY);
}

void Physics::SetFriction(double force, int axis) {

	if(axis == X) {
		this->friction.x = force;
	} else if(axis == Y) {
		this->friction.y = force;
	} else {
		throw Error("Invalid axis value");
	}
}

void Physics::SetFriction(double forceX, double forceY) {

	this->friction = Double2(forceX, forceY);
}

void Physics::Calculate() {

	for(auto &val: this->forces) {
		if(val.second.active) {
			this->accel.x += val.second.magnitude.x;
			this->accel.y += val.second.magnitude.y;
		}
	}

	if(this->accel.x > this->maxAccel.x && this->usingMaxAccel[X]) {
		this->accel.x = this->maxAccel.x;
	} else if(this->accel.x < this->minAccel.x && this->usingMinAccel[X]) {
		this->accel.x = this->minAccel.x;
	}

	if(this->accel.y > this->maxAccel.y && this->usingMaxAccel[Y]) {
		this->accel.y = this->maxAccel.y;
	} else if(this->accel.y < this->minAccel.y && this->usingMinAccel[Y]) {
		this->accel.y = this->minAccel.y;
	}

	for(auto &val: *this->movers) {
		val->Move(this->accel.x, this->accel.y);
	}

	if(std::abs(this->accel.x) >= std::abs(this->friction.x)) {
		if(this->accel.x > 0) {
			this->accel.x -= this->friction.x;
		} else {
			this->accel.x += this->friction.x;
		}
	} else if(std::abs(this->friction.x != 0)) {
		this->accel.x = 0;
	}

	if(std::abs(this->accel.y) >= std::abs(this->friction.y)) {
		if(this->accel.y > 0) {
			this->accel.y -= this->friction.y;
		} else {
			this->accel.y += this->friction.y;
		}
	} else if(std::abs(this->friction.y != 0)) {
		this->accel.y = 0;
	}
}

void Physics::Move(double x, double y) {

	for(auto &val: *this->movers) {
		val->Move(x, y);
	}
}

void Physics::SetPosition(double x, double y) {

	if(this->movers->size() == 0) {
		return;
	}

	Double2 disp = this->movers->at(0)->GetPosition();
	disp.x = x - disp.x;
	disp.y = y - disp.y;

	for(auto &val: *this->movers) {
		val->Move(disp.x, disp.y);
	}
}

Double2 Physics::GetAcceleration() {

	return this->accel;
}

double Physics::GetAcceleration(int axis) {

	switch(axis) {
	case X:
		return this->accel.x;
	case Y:
		return this->accel.y;
	default:
		throw Error("Invalid axis value");
	}
}

Double2 Physics::GetPosition() {

	if(this->movers->size() == 0) {
		return Double2(INFINITY, INFINITY);
	}

	return this->movers->at(0)->GetPosition();
}

}
