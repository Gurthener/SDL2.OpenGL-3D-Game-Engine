//struct vector : Addable<vector>, Subabble<vector> {
//	float matrix[3][1];
//	float &X = matrix[0][0];
//	float &Y = matrix[1][0];
//	float &Z = matrix[2][0];
//
//	vector(float x = 0, float y = 0, float z = 0) : 
//		matrix {{x},{y},{z}} {
//	}
//
//	vector(const vector &Src) :
//		matrix {{Src.matrix[0][0]},
//				{Src.matrix[1][0]},
//				{Src.matrix[2][0]}} {
//	}
//
//	vector(const vector &&Src) noexcept:
//		matrix {{Src.matrix[0][0]},
//				{Src.matrix[1][0]},
//				{Src.matrix[2][0]}} {
//	}
//
//	vector &operator=(const vector &Src) {
//		X = Src.X;
//		Y = Src.Y;
//		Z = Src.Z;
//		return *this;
//	}
//
//	vector &operator=(const vector &&Src) noexcept {
//		X = Src.X;
//		Y = Src.Y;
//		Z = Src.Z;
//		return *this;
//	}
//
//	vector &operator=(float c[3]) {
//		X = c[0];
//		Y = c[1];
//		Z = c[2];
//		return *this;
//	}
//
//	vector& operator+=(const vector& a) {
//		X += a.X;
//		Y += a.Y;
//		Z += a.Z;
//		return *this;
//	}
//
//	vector &operator-=(const vector &a) {
//		X -= a.X;
//		Y -= a.Y;
//		Z -= a.Z;
//		return *this;
//	}
//
//	vector &operator/=(float a) {
//		X /= a;
//		Y /= a;
//		Z /= a;
//		return *this;
//	}
//
//	vector operator/(float a) {
//		vector b(X / a,
//				 Y / a,
//				 Z / a);
//		return b;
//	}
//
//	friend vector operator*(vector const &a, float const &b) {
//		vector c(a);
//		c *= b;
//		return c;
//	}
//
//	friend vector &&operator*(vector &&a, float const &b) {
//		a *= b;
//		return std::move(a);
//	}
//
//	friend vector operator*(vector const &a, float &&b) {
//		vector c(a);
//		c *= b;
//		return c;
//	}
//
//	friend vector &&operator*(vector &&a, float &&b) {
//		a *= b;
//		return std::move(a);
//	}
//
//	vector& operator*=(const float& a) {
//		X *= a;
//		Y *= a;
//		Z *= a;
//		return *this;
//	}
//};

/*
struct sKeyState {
	bool bPressed;
	bool bReleased;
	bool bHeld;
};
*/

/*
struct screenVector {
	int X;
	int Y;
	float Z;
};
*/

/*
void drawCube(float xrf, float yrf, float zrf) {
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -7.0f);	// Сдвинуть вглубь экрана

	glRotatef(xrf, 1.0f, 0.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(yrf, 0.0f, 1.0f, 0.0f);	// Вращение куба по X, Y, Z
	glRotatef(zrf, 0.0f, 0.0f, 1.0f);	// Вращение куба по X, Y, Z

	glBegin(GL_QUADS);		// Рисуем куб

	glColor4f(0.0f, 1.0f, 0.0f, 0.5);
	//glColor3f(0.0f, 1.0f, 0.0f);		// Синяя сторона (Верхняя)
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);		// Нижний правый

	glColor3f(1.0f, 0.5f, 0.0f);		// Оранжевая сторона (Нижняя)
	glVertex3f(1.0f, -1.0f, 1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f, 1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f(1.0f, -1.0f, -1.0f);	// Нижний правый

	glColor3f(1.0f, 0.0f, 0.0f);		// Красная сторона (Передняя)
	glVertex3f(1.0f, 1.0f, 1.0f);		// Верхний правый угол квадрата
	glVertex3f(-1.0f, 1.0f, 1.0f);		// Верхний левый
	glVertex3f(-1.0f, -1.0f, 1.0f);		// Нижний левый
	glVertex3f(1.0f, -1.0f, 1.0f);		// Нижний правый

	glColor3f(1.0f, 1.0f, 0.0f);			// Желтая сторона (Задняя)
	glVertex3f(1.0f, -1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f, 1.0f, -1.0f);	// Нижний левый
	glVertex3f(1.0f, 1.0f, -1.0f);	// Нижний правый

	glColor3f(0.0f, 0.0f, 1.0f);			// Синяя сторона (Левая)
	glVertex3f(-1.0f, 1.0f, 1.0f);	// Верхний правый угол квадрата
	glVertex3f(-1.0f, 1.0f, -1.0f);	// Верхний левый
	glVertex3f(-1.0f, -1.0f, -1.0f);	// Нижний левый
	glVertex3f(-1.0f, -1.0f, 1.0f);	// Нижний правый

	glColor3f(1.0f, 0.0f, 1.0f);			// Фиолетовая сторона (Правая)
	glVertex3f(1.0f, 1.0f, -1.0f);	// Верхний правый угол квадрата
	glVertex3f(1.0f, 1.0f, 1.0f);	// Верхний левый
	glVertex3f(1.0f, -1.0f, 1.0f);	// Нижний левый
	glVertex3f(1.0f, -1.0f, -1.0f);	// Нижний правый

	glEnd();	// Закончили квадраты

}
*/

/*	//	while (true) {
	//		//ТАЙМИНГ
	//		currentTime = SDL_GetTicks();
	//		auto timeElapsed = (currentTime - oldTime) / 1000.0f;
	//		oldTime = currentTime;
	//
	//		inputThread(currentTime, oldTime, timeElapsed);
	//
	//		for (auto rCircle = rainCircleList.begin(); rCircle != rainCircleList.end(); rCircle++) {
	//			if (currentTime - rCircle->spawnTime >= rCircle->lifeTime) {
	//				rCircle = rainCircleList.erase(rCircle);
	//				if (rCircle == rainCircleList.end()) break;
	//			}
	//
	//			for (auto &vertex : rCircle->circle.vertices) {
	//				velocity tVel {0,0,0};
	//				subMat(vertex.pos.matrix, rCircle->origin.matrix, tVel.matrix);
	//				normalizeVector(tVel, tVel);
	//				mulMatByNum(tVel.matrix, rCircle->velocity * (currentTime - rCircle->spawnTime) / 1000.0f, tVel.matrix);
	//				tVel.Y = 0;
	//				sumMat(rCircle->origin.matrix, tVel.matrix, vertex.pos.matrix);
	//			}
	//		}
	//
	//	   //ОТРИСОВКА
	//
	//		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	//		SDL_RenderClear(renderer);
	//		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//
	//		glClearColor(1, 0, 0, 0);
	//		glClear(GL_COLOR_BUFFER_BIT);
	//
	//		glPushMatrix();
	//		glBegin(GL_TRIANGLES);
	//
	//		glColor3f(1, 1, 1); glVertex2f(1, 0);
	//		glColor3f(1, 1, 1); glVertex2f(0, 1);
	//		glColor3f(1, 1, 1); glVertex2f(1, 1);
	//
	//		glEnd();
	//		glPopMatrix();
	//
	//		//РЕНДЕР ЗВЁЗД
	//		//
	//		//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	//		//std::vector<SDL_Point> starLines(starList.size());
	//		glBegin(GL_POINTS);
	//		for (auto &star : starList) {
	//			glColor3ub(star.color >> 24,
	//					   star.color >> 16,
	//					   star.color >> 8);
	//			glVertex3fv(&star.pos.matrix[0][0]);
	//			//if (culling(star.pos)) continue;
	//			//position modPos(rotateVector(star.pos));
	//			//SDL_SetRenderDrawColor(renderer,
	//			//					   star.color >> 24,
	//			//					   star.color >> 16,
	//			//					   star.color >> 8,
	//			//					   star.color);
	//			//SDL_RenderDrawPoint(renderer,
	//			//					screenDistance * modPos.X / modPos.Z + fCenterColumn,
	//			//					-screenDistance * modPos.Y / modPos.Z + fCenterLine);
	//		}
	//		glEnd();
	//		//SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
	//
	//		//РЕНДЕР ПРОЖЕКТАЙЛОВ
	//		//	if (readyToClearObjects) {
	//		//		projectileList.clear();
	//		//		readyToClearObjects = false;
	//		//	} else {
	//		//		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//		//		std::vector<SDL_Point> projectileDrawVector(projectileList.size());
	//		//		for (auto &bullet : projectileList) {
	//		//			if (culling(bullet.pos)) continue;
	//		//			scalar modVec(rotateVector(bullet.pos, camera.pos));
	//		//			projectileDrawVector.push_back({(int) (screenDistance * modVec.X / modVec.Z + fCenterColumn),
	//		//											(int) (-screenDistance * modVec.Y / modVec.Z + fCenterLine)});
	//		//		}
	//		//		SDL_RenderDrawPoints(renderer, projectileDrawVector.data(), projectileDrawVector.size());
	//		//	}
	//		//
	//		//	//РЕНДЕР ПРИДУРКОВ
	//		//	float const radius = 10.5;
	//		//	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	//		//	std::vector<SDL_Rect> preyDrawVector;
	//		//	preyDrawVector.reserve(preys.size());
	//		//	for (auto const &prey : preys) {
	//		//		if (culling(prey.pos)) continue;
	//		//		scalar const modVec(rotateVector(prey.pos, camera.pos));
	//		//		int x = screenDistance * (modVec.X - radius) / modVec.Z + fCenterColumn,
	//		//			y = -screenDistance * (modVec.Y - radius) / modVec.Z + fCenterLine;
	//		//		int w = screenDistance * (modVec.X + radius) / modVec.Z + fCenterColumn - x,
	//		//			h = -screenDistance * (modVec.Y + radius) / modVec.Z + fCenterLine - y;
	//		//		preyDrawVector.push_back({x, y, w, h});
	//		//
	//		//		scalar const modVec2 = rotateVector(prey.pos + prey.acc, camera.pos);
	//		//		SDL_RenderDrawLine(
	//		//			renderer,
	//		//			screenDistance * modVec.X / modVec.Z + fCenterColumn,
	//		//			-screenDistance * modVec.Y / modVec.Z + fCenterLine,
	//		//			screenDistance * modVec2.X / modVec2.Z + fCenterColumn,
	//		//			-screenDistance * modVec2.Y / modVec2.Z + fCenterLine
	//		//		);
	//		//	}
	//		//	SDL_RenderDrawRects(renderer, preyDrawVector.data(), preyDrawVector.size());
	//		//
	//		//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	//		//	std::vector<SDL_Rect> predDrawVector;
	//		//	predDrawVector.reserve(predators.size());
	//		//	for (auto const &prey : predators) {
	//		//		if (culling(prey.pos)) continue;
	//		//		scalar const modVec(rotateVector(prey.pos, camera.pos));
	//		//		int x = screenDistance * (modVec.X - radius) / modVec.Z + fCenterColumn,
	//		//			y = -screenDistance * (modVec.Y - radius) / modVec.Z + fCenterLine;
	//		//		int w = screenDistance * (modVec.X + radius) / modVec.Z + fCenterColumn - x,
	//		//			h = -screenDistance * (modVec.Y + radius) / modVec.Z + fCenterLine - y;
	//		//		predDrawVector.push_back({x, y, w, h});
	//		//
	//		//		scalar const modVec2 = rotateVector(prey.pos + prey.acc, camera.pos);
	//		//		SDL_RenderDrawLine(
	//		//			renderer,
	//		//			screenDistance * modVec.X / modVec.Z + fCenterColumn,
	//		//			-screenDistance * modVec.Y / modVec.Z + fCenterLine,
	//		//			screenDistance * modVec2.X / modVec2.Z + fCenterColumn,
	//		//			-screenDistance * modVec2.Y / modVec2.Z + fCenterLine
	//		//		);
	//		//	}
	//		//	SDL_RenderDrawRects(renderer, predDrawVector.data(), predDrawVector.size());
	//		//
	//		//	//РЕНДЕР ВОДЯНЫХ КРУГОВ
	//		//	SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
	//		//	for (auto &rain : rainCircleList) {
	//		//		auto &model = rain.circle;
	//		//		std::vector<screenVector> screenVertexes(model.vertices.size());
	//		//		int i = 0;
	//		//		for (auto &&vertex : model.vertices) {
	//		//			if (culling(vertex.pos)) continue;
	//		//			position modVec = rotateVector(vertex.pos);
	//		//			//if (culling(modVec)) continue;
	//		//			screenVertexes[i].Z = modVec.Z;
	//		//			if (screenVertexes[i].Z > 0) {
	//		//				screenVertexes[i].X = ((screenDistance * (modVec.X) / (modVec.Z)) + fCenterColumn);
	//		//				screenVertexes[i].Y = (-(screenDistance * (modVec.Y) / (modVec.Z)) + fCenterLine);
	//		//			} else {
	//		//				screenVertexes[i].X = screenVertexes[i - 1].X;
	//		//				screenVertexes[i].Y = screenVertexes[i - 1].Y;
	//		//			}
	//		//			//	screenVertexes[i].X = ((screenDistance * (modVec.X) / (modVec.Z) * -(modVec.Z)) + fCenterColumn);
	//		//			//	screenVertexes[i].Y = ((screenDistance * (modVec.Y) / (modVec.Z) * -(modVec.Z)) + fCenterLine);
	//		//			//}
	//		//			++i;
	//		//		}
	//		//
	//		//		for (int i = 0; i < model.lines.size() - 1; ++i) {
	//		//			if (model.lines[i + 1] < 0) {
	//		//				++i;
	//		//				continue;
	//		//			}
	//		//			screenVector &P1 = screenVertexes[model.lines[i]];
	//		//			screenVector &P2 = screenVertexes[model.lines[i + 1]];
	//		//			if (P1.Z <= 0 || P2.Z <= 0) continue;
	//		//			int X1 = screenVertexes[model.lines[i]].X;
	//		//			int X2 = screenVertexes[model.lines[i + 1]].X;
	//		//			int Y1 = screenVertexes[model.lines[i]].Y;
	//		//			int Y2 = screenVertexes[model.lines[i + 1]].Y;
	//		//			//SDL_IntersectRectAndLine(&winRect, &X1, &Y1, &X2, &Y2);
	//		//			SDL_RenderDrawLine(renderer, X1, Y1, X2, Y2);
	//		//		}
	//		//	}
	//		//
	//		//	for (auto &model : list) {
	//		//		std::vector<screenVector> screenVertexes(model.vertices.size());
	//		//		int i = 0;
	//		//		bool skip = 1;
	//		//		for (auto &vertex : model.vertices) {
	//		//			if (!culling(vertex.pos)) {
	//		//				skip = false;
	//		//				break;
	//		//			}
	//		//		}
	//		//
	//		//		if (skip) continue;
	//		//
	//		//		for (auto &vertex : model.vertices) {
	//		//			position modVec = rotateVector(vertex.pos);
	//		//			screenVertexes[i].X = screenDistance * modVec.X / modVec.Z + fCenterColumn;
	//		//			screenVertexes[i].Y = -screenDistance * modVec.Y / modVec.Z + fCenterLine;
	//		//			i++;
	//		//		}
	//		//		SDL_SetRenderDrawColor(renderer, (model.color >> 24) & 0xFF, (model.color >> 16) & 0xFF, (model.color >> 8) & 0xFF, 255);
	//		//
	//		//		std::vector<SDL_Point> polyLine;
	//		//		polyLine.reserve(model.lines.size());
	//		//		int numOfPoints = 0;
	//		//		for (int i = 0; i < model.lines.size(); ++i) {
	//		//			if (model.lines[i] < 0) {
	//		//				SDL_RenderDrawLines(renderer, polyLine.data(), numOfPoints);
	//		//				numOfPoints = 0;
	//		//				polyLine.clear();
	//		//			} else {
	//		//				polyLine.push_back({screenVertexes[model.lines[i]].X,
	//		//								   screenVertexes[model.lines[i]].Y});
	//		//				++numOfPoints;
	//		//			}
	//		//		}
	//		//		SDL_RenderDrawLines(renderer, polyLine.data(), numOfPoints);
	//		//	}
	//		//
	//		//	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 128);
	//		//	SDL_RenderDrawLine(renderer, fCenterColumn - 5, fCenterLine, fCenterColumn + 5, fCenterLine);
	//		//	SDL_RenderDrawLine(renderer, fCenterColumn, fCenterLine - 5, fCenterColumn, fCenterLine + 5);
	//		//
	//		//	SDL_RenderPresent(renderer);
	//		//	title = std::to_string((int)(1 / timeElapsed));
	//		//	SDL_SetWindowTitle(window, title.c_str());
	//	}
	*/

/*struct CullingPyramid {
	position leftUp, rightUp, rightDown, leftDown, origin;
	Plane left, up, right, down;
} pyramid;*/

/*void updateCullingPyramid() {
	pyramid.origin = camera.pos;

	pyramid.leftUp = rotateHead({-fCenterColumn,fCenterLine,screenDistance}, {0,0,0});
	pyramid.leftDown = rotateHead({-fCenterColumn,-fCenterLine,screenDistance}, {0,0,0});
	pyramid.rightDown = rotateHead({fCenterColumn,-fCenterLine,screenDistance}, {0,0,0});
	pyramid.rightUp = rotateHead({fCenterColumn,fCenterLine,screenDistance}, {0,0,0});

	pyramid.leftUp += pyramid.origin;
	pyramid.leftDown += pyramid.origin;
	pyramid.rightDown += pyramid.origin;
	pyramid.rightUp += pyramid.origin;

	pyramid.left = getEquationPlane(pyramid.origin, pyramid.leftUp, pyramid.leftDown);
	pyramid.right = getEquationPlane(pyramid.origin, pyramid.rightDown, pyramid.rightUp);
	pyramid.up = getEquationPlane(pyramid.origin, pyramid.rightUp, pyramid.leftUp);
	pyramid.down = getEquationPlane(pyramid.origin, pyramid.leftDown, pyramid.rightDown);
}*/

//scalar &&rotateVector(scalar &&vector, scalar &&rotatePoint) {
//	vector -= rotatePoint;
//	mulMatByMat(rotationMatrix, vector.matrix, vector.matrix);
//	return std::move(vector);
//}
//
//scalar&& rotateVector(scalar&& vector, const scalar& rotatePoint = camera.pos) {
//	vector -= rotatePoint;
//	mulMatByMat(rotationMatrix, vector.matrix, vector.matrix);
//	return std::move(vector);
//}
//
//scalar &&rotateVector(const scalar& vector, scalar && rotatePoint) {
//	rotatePoint = vector - rotatePoint;
//	mulMatByMat(rotationMatrix, rotatePoint.matrix, rotatePoint.matrix);
//	return std::move(rotatePoint);
//}

/*
bool culling(vector const& vec) {
	if (checkPlaneRelativity(vec, pyramid.down) < 0) return true;
	if (checkPlaneRelativity(vec, pyramid.left) < 0) return true;
	if (checkPlaneRelativity(vec, pyramid.up) < 0) return true;
	if (checkPlaneRelativity(vec, pyramid.right) < 0) return true;
	return false;
}*/

/*
#pragma once
template <typename T, int H1, int W1, int H2, int W2, int H3, int W3>
void mulMatByMat(T(&firstMatrix)[H1][W1], T(&secondMatrix)[H2][W2], T(&resultMatrix)[H3][W3]);

template <typename T1, typename T2, int H1, int W1>
void mulMatByNum(T1(&matrix)[H1][W1], T2 mul, T1(&resultMatrix)[H1][W1]);

template <typename T, int H1, int W1, int H2, int W2, int H3, int W3>
void sumMat(T(&firstMatrix)[H1][W1], T(&secondMatrix)[H2][W2], T(&resultMatrix)[H3][W3]);

template <typename T, int H1, int W1, int H2, int W2, int H3, int W3>
void subMat(T(&firstMatrix)[H1][W1], T(&secondMatrix)[H2][W2], T(&resultMatrix)[H3][W3]);

template <typename T, int H1, int W1, int H2, int W2>
void transMat(T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]);

template <typename T, int H1, int W1, int H2, int W2>
void rotMatX(float angle, T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]);

template <typename T, int H1, int W1, int H2, int W2>
void rotMatY(float angle, T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]);

template <typename T, int H1, int W1, int H2, int W2>
void rotMatZ(float angle, T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]);

#include "MatrixOperations.cpp"

#pragma once
#include <cmath>
#include <cassert>

template <typename T, int H1, int W1, int H2, int W2>
void rotMatX(float angle, T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]) {
	float xMatrix[3][3] = {{1, 0,           0         },
						   {0, cos(angle), -sin(angle)},
						   {0, sin(angle),  cos(angle)}};

	mulMatByMat(xMatrix, matrix, resultMatrix);
}

template <typename T, int H1, int W1, int H2, int W2>
void rotMatY(float angle, T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]) {
	float yMatrix[3][3] = {{ cos(angle), 0, sin(angle)},
						   { 0,          1, 0         },
						   {-sin(angle), 0, cos(angle)}};

	mulMatByMat(yMatrix, matrix, resultMatrix);
}

template <typename T, int H1, int W1, int H2, int W2>
void rotMatZ(float angle, T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]) {

	float zMatrix[3][3] = {{cos(angle), -sin(angle), 0},
						   {sin(angle),  cos(angle), 0},
						   {0,           0,          1}};

	mulMatByMat(zMatrix, matrix, resultMatrix);
}

template <typename T, int H1, int W1, int H2, int W2, int H3, int W3>
void mulMatByMat(T(&firstMatrix)[H1][W1], T(&secondMatrix)[H2][W2], T(&resultMatrix)[H3][W3]) {
	assert(W1 == H2);
	assert(H1 == H3);
	assert(W2 == W3);

	T tempMatrix[H3][W3] {};
	for (int y = 0; y < H1; ++y)
		for (int x = 0; x < W2; ++x)
			for (int i = 0; i < W1; ++i)
				tempMatrix[y][x] += firstMatrix[y][i] * secondMatrix[i][x];

	for (int y = 0; y < H3; y++)
		for (int x = 0; x < W3; x++)
			resultMatrix[y][x] = tempMatrix[y][x];
}

template <typename T1, typename T2, int H1, int W1>
void mulMatByNum(T1(&matrix)[H1][W1], T2 mul, T1(&resultMatrix)[H1][W1]) {
	for (int y = 0; y < H1; y++)
		for (int x = 0; x < W1; x++)
			resultMatrix[y][x] = matrix[y][x] * mul;
}


template <typename T, int H1, int W1, int H2, int W2, int H3, int W3>
void sumMat(T(&firstMatrix)[H1][W1], T(&secondMatrix)[H2][W2], T(&resultMatrix)[H3][W3]) {
	assert(H1 == H2);
	assert(H2 == H3);
	assert(W1 == W2);
	assert(W2 == W3);
	for (int y = 0; y < H1; y++)
		for (int x = 0; x < W1; x++)
			resultMatrix[y][x] = firstMatrix[y][x] + secondMatrix[y][x];
}

template <typename T, int H1, int W1, int H2, int W2, int H3, int W3>
void subMat(T(&firstMatrix)[H1][W1], T(&secondMatrix)[H2][W2], T(&resultMatrix)[H3][W3]) {
	assert(H1 == H2);
	assert(H1 == H3);
	assert(W1 == W2);
	assert(W2 == W3);

	for (int y = 0; y < H1; y++)
		for (int x = 0; x < W1; x++)
			resultMatrix[y][x] = firstMatrix[y][x] - secondMatrix[y][x];
}

template <typename T, int H1, int W1, int H2, int W2>
void transMat(T(&matrix)[H1][W1], T(&resultMatrix)[H2][W2]) {
	assert(H1 == W1);
	assert(W1 == H2);

	T tempMatrix[H2][W2] {};
	for (int y = 0; y < H2; y++)
		for (int x = 0; x < W2; x++)
			tempMatrix[y][x] = matrix[x][y];

	for (int y = 0; y < H2; y++)
		for (int x = 0; x < W2; x++)
			resultMatrix[y][x] = tempMatrix[y][x];
}*/

					//гравитация
					//bullet->acc = attractionPoint - bullet->pos;
					//float length = sqrt(pow(bullet->acc.X, 2) + pow(bullet->acc.Y, 2) + pow(bullet->acc.Z, 2));
					//if (length < 100) {
					//	bullet = projectileList.erase(bullet);
					//	if (bullet == projectileList.end()) break;
					//}
					//float gravity = 1000000000 / (length * length);
					//normalizeVector(bullet->acc, bullet->acc);
					//bullet->acc *= gravity;

//struct vertex {
//	glm::vec3 pos;
//
//	vertex(float x = 0, float y = 0, float z = 0) : pos(x, y, z) {
//	}
//
//	vertex(glm::vec3 v = glm::vec3()) : pos(v) {
//	}
//};