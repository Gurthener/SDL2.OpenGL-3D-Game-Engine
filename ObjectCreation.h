#pragma once
#include <glm.hpp>

#include "UtilityFunctions.h"
#include "Globals.h"

void createCube(glm::vec3 mul = {1,1,1}, glm::vec3 offset = {0,0,0}, glm::vec4 color = {1,1,1,1});

void createCube(float mul = 1, glm::vec3 offset = {0,0,0}, glm::vec4 color = {1,1,1,1});

void createCube();

void createPoint(glm::vec3 offset, glm::vec4 color = {1,1,1,1});

void createHorizon();

void createRainCircle(glm::vec3& o, float v, long s, long l);

extern glm::vec3 attractionPoint;

void createLandscape();