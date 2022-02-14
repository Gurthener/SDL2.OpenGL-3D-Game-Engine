#include "Simulator.h"

void fillGameWorld() {
	createHorizon();

	float multiplier = 1. / 32.;
	for (float countX = 0; countX < 32; ++countX)
		for (float countY = 0; countY < 32; ++countY)
			for (float countZ = 0; countZ < 32; ++countZ)
				createCube(1,
						   {countX * 2.f, countY * 2.f, countZ * 2.f},
						   glm::vec4(countX * multiplier,
									 countY * multiplier,
									 countZ * multiplier,
									 1));

	int constexpr starCount = 2048;
	starList.reserve(starCount);
	for (int i = 0; i < starCount; ++i) {
		glm::vec3 starPosition(randRange(-1, 1), randRange(0, 1), randRange(-1, 1));
		//float length = sqrt(vec.X * vec.X + vec.Y * vec.Y + vec.Z * vec.Z);
		//glm::length(vec);
		if (glm::length(starPosition) > 1) {
			[[unlikely]];
			--i;
			continue;
		}
		normalizeVector(starPosition, starPosition);
		starPosition *= 625000;
		starList.push_back({starPosition,
						   glm::vec4(randRange(0.8, 1),
									 randRange(0.8, 1),
									 randRange(0.8, 1),
									 randRange(0, 1))});
	}

	createRotationMatrix();
	createHeadRotationMatrix();

	for (int i = 0; i < 200; ++i) {
		predators.push_back(Entity({randRange(-2000, 0),
								   randRange(-2000, 0),
								   randRange(-2000, 0)},

								   {randRange(-20, 20),
								   randRange(-20, 20),
								   randRange(-20, 20)},
								   3,
								   false));
	}

	for (int i = 0; i < 200; ++i) {
		preys.push_back(Entity({randRange(-2000, 0),
							   randRange(-2000, 0),
							   randRange(-2000, 0)},

							   {randRange(-20, 20),
							   randRange(-20, 20),
							   randRange(-20, 20)},
							   3,
							   false));
	}

	for (int i = 0; i < 200; ++i) {
		blues.push_back(Entity({randRange(-2000, 0),
							   randRange(-2000, 0),
							   randRange(-2000, 0)},

							   {randRange(-20, 20),
							   randRange(-20, 20),
							   randRange(-20, 20)},
							   3,
							   false));
	}


	//for (int i = -1000000; i <= 1000000; i += 1000) {
	//	landLines.push_back(glm::vec3(i, 0, 1000000));
	//	landLines.push_back(glm::vec3(i, 0, -1000000));
	//	landLines.push_back(glm::vec3(1000000, 0, i));
	//	landLines.push_back(glm::vec3(-1000000, 0, i));
	//}
	//
	//createLandscape();

	LifeCell::fillMap(500, 30);
}

void inputThread(clock_t const& currentTime,
				 clock_t const& oldTime,
				 float const& timeElapsed) {
	int x = 0, y = 0;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEMOTION:
			x += event.motion.xrel;
			y += event.motion.yrel;
			continue;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == 1) {
				BallisticProjectile::addToList(camera.pos, camera.vel, camera.headForward, 600, currentTime, 4000, 100);
			}
			continue;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == 1)
				firing = false;
			continue;

		case SDL_QUIT: // если произошло событие закрытия окна, то завершаем работу программы
			running = false;
			break;

		case SDL_KEYDOWN: // если нажата клавиша
			switch (event.key.keysym.sym) { // смотрим какая
			case SDLK_ESCAPE: // клавиша ESC
				running = false; // завершаем работу программы
				break;

			case SDLK_w: // клавиша ESC
				state.set(MOVE_FORWARD); // завершаем работу программы
				continue;

			case SDLK_a: // клавиша ESC
				state.set(MOVE_LEFT); // завершаем работу программы
				continue;

			case SDLK_s: // клавиша ESC
				state.set(MOVE_BACKWARD); // завершаем работу программы
				continue;

			case SDLK_d: // клавиша ESC
				state.set(MOVE_RIGHT); // завершаем работу программы
				continue;

			case SDLK_LCTRL:
				state.set(MOVE_DOWN);  // завершаем работу программы
				continue;

			case SDLK_SPACE: // клавиша ESC
				state.set(MOVE_UP); // завершаем работу программы
				continue;

			case SDLK_LSHIFT: // клавиша ESC
				state.set(BOOST); // завершаем работу программы
				continue;

			case SDLK_KP_PLUS:
				state.set(FOV_PLUS);
				continue;

			case SDLK_KP_MINUS:
				state.set(FOV_MINUS);
				continue;

			case SDLK_v:
				state.flip(PAUSE);
				continue;

			case SDLK_c:
				state.set(CLEAR);
				continue;

			case SDLK_t:
				state.set(LIFE_EVOLVE);
				continue;
			}

		case SDL_KEYUP: // если нажата клавиша
			switch (event.key.keysym.sym) { // смотрим какая
			case SDLK_ESCAPE: // клавиша ESC
				running = true; // завершаем работу программы
				break;

			case SDLK_w: // клавиша ESC
				state.reset(MOVE_FORWARD); // завершаем работу программы
				continue;

			case SDLK_a: // клавиша ESC
				state.reset(MOVE_LEFT); // завершаем работу программы
				continue;

			case SDLK_s: // клавиша ESC
				state.reset(MOVE_BACKWARD); // завершаем работу программы
				continue;

			case SDLK_d: // клавиша ESC
				state.reset(MOVE_RIGHT);// завершаем работу программы
				continue;

			case SDLK_LCTRL:
				state.reset(MOVE_DOWN); // завершаем работу программы
				continue;

			case SDLK_SPACE: // клавиша ESC
				state.reset(MOVE_UP); // завершаем работу программы
				continue;

			case SDLK_LSHIFT: // клавиша ESC
				state.reset(BOOST); // завершаем работу программы
				continue;

			case SDLK_KP_PLUS:
				state.reset(FOV_PLUS);
				continue;

			case SDLK_KP_MINUS:
				state.reset(FOV_MINUS);
				continue;
			}
		}
	}

	if (state.test(MOVE_FORWARD)) { //W
		camera.vel += camera.headForward;
	}

	if (state.test(MOVE_LEFT)) { //A
		camera.vel -= camera.headRight;
	}

	if (state.test(MOVE_RIGHT)) { //D
		camera.vel += camera.headRight;
	}

	if (state.test(MOVE_BACKWARD)) { //S
		camera.vel -= camera.headForward;
	}

	if (state.test(MOVE_UP)) { //SPA
		camera.vel += camera.headUp;
	}

	if (state.test(MOVE_DOWN)) { //ctr
		camera.vel -= camera.headUp;
	}

	if (camera.vel != glm::vec3(0, 0, 0)) {

		camera.vel = glm::normalize(camera.vel) * timeElapsed * SPEED *
			(state.test(BOOST) ? 100.f : 1.f);

		camera.pos += camera.vel;
		if (camera.pos.y < 0) camera.pos.y = 0;
		camera.vel = {0,0,0};
	}

	if (state.test(FOV_PLUS)) { //+
		if (g_fov < 179) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(++g_fov, (float) width / (float) height, 0.1, 10000000);
			glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
		}
	}

	if (state.test(FOV_MINUS)) { //-
		if (g_fov > 1) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(--g_fov, (float) width / (float) height, 0.1, 10000000);
			glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
		}
	}

	if (x)
		angleY += (float) x / 360.f * g_fov / 90;

	if (y) {
		angleX += (float) y / 360.f * g_fov / 90;
		if (angleX > PI / 2 - 0.001) angleX = PI / 2 - 0.001;
		if (angleX < -PI / 2 + 0.001) angleX = -PI / 2 + 0.001;
	}

	createRotationMatrix();
	createHeadRotationMatrix();
	updateCameraHeading();
	//updateCullingPyramid();


	//if (state.test(PAUSE)) { //v
	//	pause = true;
	//} else {
	//	pause = false;
	//}

	//SDL_Delay(10);


}

void initial() {
	// Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Unable to init SDL, error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 1);
	SDL_GL_SetAttribute(SDL_GL_RETAINED_BACKING, 1);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 1);
	//SDL_GL_SetAttribute(SDL_GL_STEREO, 0);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	//SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 1);
	//SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 1);
	//SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 1);
	//SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 1);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	// Создаем окно с заголовком "Cube", размером 640х480 и расположенным по центру экрана.

	gameWindow = SDL_CreateWindow("Cube", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_GLContext glcontext = SDL_GL_CreateContext(gameWindow); // создаем контекст OpenGL

	if (gameWindow == NULL) {	// если не получилось создать окно, то выходим
		exit(1);
	}

	// Инициализация OpenGL
	SDL_GL_SetSwapInterval(0);

	glClearColor(0, 0, 0, 1); // устанавливаем фоновый цвет на черный

	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST); // включаем тест глубины
	glDepthFunc(GL_LESS);

	//glEnable(GL_BLEND);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHTING);
	//glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(g_fov, (float) width / (float) height, 0.1, 10000000);
	//perspectiveGL(g_fov, (float) width / (float) height, 0.5, 10000000);
	//gluPerspective(45.0f, (float) width / (float) height, 0.1f, 100.0f); // настраиваем трехмерную перспективу
	glMatrixMode(GL_MODELVIEW); // переходим в трехмерный режим
	SDL_SetRelativeMouseMode(SDL_TRUE);
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ZERO);
}


int main(int argc, char* args[]) {
	initial(); // инициализация

	fillGameWorld();

	std::thread lifeEvolve(LifeCell::basicLoop);
	std::thread projPhyz(BallisticProjectile::projectilePhysics);
	std::thread entPreyMov(entityPreyMoving);
	std::thread entPredMov(entityPredMoving);
	std::thread entBlueMov(entityBlueMoving);

	auto oldTime = SDL_GetTicks();
	auto currentTime = oldTime;
	std::string title;

	while (running) {
		[[likely]] currentTime = SDL_GetTicks();
		auto timeElapsed = (currentTime - oldTime) / 1000.0f;
		oldTime = currentTime;

		inputThread(currentTime, oldTime, timeElapsed);
		//continue;

		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		//glEnable(GL_DEPTH_TEST | GL_ALPHA_TEST); // включаем тест глубины
		//glDepthFunc(GL_LESS);
		glLoadIdentity();

		glm::vec3 lookPoint = camera.headForward + camera.pos;
		gluLookAt(camera.pos.x, camera.pos.y, camera.pos.z,
				  lookPoint.x, lookPoint.y, lookPoint.z,
				  camera.headUp.x, camera.headUp.y, camera.headUp.z);

		//GLfloat lightpos[] = {0.5, 0., 1., 0.};
		//glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

		glPointSize(1);
		glBegin(GL_POINTS);
		for (auto& star : starList) {
			//glMaterialfv(GL_FRONT, GL_DIFFUSE, &star.color.r);
			glColor4fv(&star.color.r);
			glVertex3fv(&star.pos.x);
		}

		//if (readyToClearObjects) {
		//	[[unlikely]]
		//	projectileList.clear();
		//	readyToClearObjects = false;
		//	state.reset(CLEAR);
		//} //else {
		glColor4ub(0xFF,
				   0xFF,
				   0,
				   0x88);
		for (auto& bullet : BallisticProjectile::projectileList) {
			glm::vec3 posi = bullet.getPos();
			glVertex3fv(&posi.x);
	//	}
		//SDL_RenderDrawPoints(renderer, projectileDrawVector.data(), projectileDrawVector.size());
		}
		glEnd();

		glBegin(GL_QUADS);
		for (auto const& cube : cubesArray) {
			//glMaterialfv(GL_FRONT, GL_SPECULAR, &cube.color.r);
			glColor4fv(&cube.color.r);
			for (int i = 0; i < 24; ++i) {
				glVertex3fv(&cube.vertices[cubeVertices[i]].x);
			}
		}
		glEnd();

		//glBegin(GL_LINES);
		//glColor3ub(0x00, 0x44, 0x00);
		//for (auto const &line : landLines) {
		//	glVertex3fv(&line.x);
		//}		
		//glEnd();

		//glBegin(GL_LINES);
		//glColor3ub(0x00, 0x44, 0x00);
		//for (auto const &index : landscapeLines) {
		//	glVertex3fv(&landscapeVertices[index].x);
		//}
		//glEnd();

		//РЕНДЕР ПРИДУРКОВ
			/*glBegin(GL_LINES);
			glColor3ub(0xFF, 0, 0);
			for (auto const &prey : preys) {
				glVertex3fv(&prey.pos.x);
				glm::vec3 const accelerationVector = prey.pos + prey.acc;
				glVertex3fv(&accelerationVector.x);
			}

			glColor3ub(0, 0xFF, 0);
			for (auto const &prey : predators) {
				glVertex3fv(&prey.pos.x);
				glm::vec3 const accelerationVector = prey.pos + prey.acc;
				glVertex3fv(&accelerationVector.x);
			}

			glColor3ub(0, 0xFF, 0xFF);
			for (auto const &prey : blues) {
				glVertex3fv(&prey.pos.x);
				glm::vec3 const accelerationVector = prey.pos + prey.acc;
				glVertex3fv(&accelerationVector.x);
			}
			glEnd();
			*/




		glPointSize(3);
		glBegin(GL_POINTS);
		glColor3ub(0x88, 0xFF, 0);
		const float donutRadius = 200, donutThickness = 90;
		for (auto& [x, line] : LifeCell::cellsMap) {
		//сталбыть x - это вдоль бублика
			float ringRad = 2 * PI / 256 * x;
			//auto vec = glm::vec4(donutThickness, 0, 0, 1);
			//auto transMat = glm::identity<glm::mat4x4>();
			//transMat = glm::rotate(transMat, ringRad, glm::vec3(0, 0, 1));
			//vec = transMat * vec;
			//vec += glm::vec4(donutRadius, 0, 0, 1);
			for (auto& [y, cell] : line) {
				if (cell.getState()) {

					float surfaceRad = 2. * PI / 256. * y;
					//auto transMat = glm::rotate(glm::identity<glm::mat4x4>(), (xTurn / 17 / PI), {1,0,0});
					//transMat = glm::rotate(transMat, (xTurn / 7 / PI), {0,0,1});
					//transMat = glm::rotate(transMat, (xTurn / 47 / PI), {0,1,0});
					auto transMat = glm::rotate(glm::identity<glm::mat4x4>(), surfaceRad, {0,1,0});
					//transMat = glm::scale(transMat, {60, 60, 60});
					transMat = glm::translate(transMat, {donutRadius, 0, 0});
					transMat = glm::rotate(transMat, ringRad, {0,0,1});
					transMat = glm::translate(transMat, {donutThickness, 0, 0});
					auto vec2 = transMat * glm::vec4(0, 0, 0, 1);


					//сталбыть у - это по поверхности бублика 
					//float surfaceRad = 2. * PI / 256. * y;
					//auto ringMat = glm::rotate(glm::mat4x4(1.0f), surfaceRad, glm::vec3(0, 1, 0));
					//auto vec2 = ringMat * vec;

					glVertex3fv(&vec2.x);
				}
			}
		}
		glEnd();




	//glFlush();
		SDL_GL_SwapWindow(gameWindow);
		title = std::to_string((int) (1 / timeElapsed));
		SDL_SetWindowTitle(gameWindow, title.c_str());
		//SDL_Delay(20);
	}

	projPhyz.join();
	entPreyMov.join();
	entPredMov.join();

	//SDL_Quit(); // завершаем работу SDL и выходим
	return 0;
}
