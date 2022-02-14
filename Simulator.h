#pragma once
#include <thread>
#include <chrono>
#include <iostream>
#include <windows.h>

#include <GL/GLU.h>
#include <gtc/matrix_transform.hpp>
#include <SDL.h>

#include "ObjectCreation.h"
#include "Globals.h"
#include "UtilityFunctions.h"
#include "Entity.h"
#include "LifeCell.h"
#include "Projectile.h"

void fillGameWorld();

void inputThread(clock_t const& currentTime,
				 clock_t const& oldTime,
				 float const& timeElapsed);

void initial();

int main(int argc, char* args[]);