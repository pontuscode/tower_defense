FLAGS := -std=c++17 -Wall
LIBS := -L${SFML_ROOT}/lib -I${SFML_ROOT}/include -lsfml-window -lsfml-graphics -lsfml-system
all: assetManager.o buildState.o castle.o creditState.o enemy.o enemyManager.o fastEnemy.o fastTower.o gameLoop.o gameOverState.o gameState.o iceTower.o inputManager.o main.o menuState.o minotaur.o pauseState.o powerEnemy.o powerTower.o projectile.o stateMachine.o Tile.o Timer.o Tower.o waterTower.o zombie.o
	g++ $(FLAGS) assetManager.o buildState.o castle.o creditState.o enemy.o enemyManager.o fastEnemy.o fastTower.o gameLoop.o gameOverState.o gameState.o iceTower.o inputManager.o main.o menuState.o minotaur.o pauseState.o powerEnemy.o powerTower.o projectile.o stateMachine.o Tile.o Timer.o Tower.o waterTower.o zombie.o -o program $(LIBS)
assetManager.o: assetManager.cc assetManager.h
	g++ $(FLAGS) assetManager.cc -c -o assetManager.o  

buildState.o: buildState.cc buildState.h state.h
	g++ $(FLAGS) buildState.cc -c -o buildState.o  

castle.o: castle.cc castle.h
	g++ $(FLAGS) castle.cc -c -o castle.o  		

creditState.o: creditState.cc creditState.h state.h definitions.h
	g++ $(FLAGS) creditState.cc -c -o creditState.o  

enemy.o: enemy.cc enemy.h
	g++ $(FLAGS) enemy.cc -c -o enemy.o  

enemyManager.o: enemyManager.cc enemyManager.h
	g++ $(FLAGS) enemyManager.cc -c -o enemyManager.o  

fastEnemy.o: fastEnemy.cc fastEnemy.h
	g++ $(FLAGS) fastEnemy.cc -c -o fastEnemy.o  

fastTower.o: fastTower.cc fastTower.h
	g++ $(FLAGS) fastTower.cc -c -o fastTower.o  

gameLoop.o: gameLoop.cc gameLoop.h definitions.h
	g++ $(FLAGS) gameLoop.cc -c -o gameLoop.o  

gameOverState.o: gameOverState.cc gameOverState.h state.h definitions.h
	g++ $(FLAGS) gameOverState.cc -c -o gameOverState.o  

gameState.o: gameState.cc gameState.h definitions.h state.h
	g++ $(FLAGS) gameState.cc -c -o gameState.o  

iceTower.o: iceTower.cc iceTower.h
	g++ $(FLAGS) iceTower.cc -c -o iceTower.o  

inputManager.o: inputManager.cc inputManager.h
	g++ $(FLAGS) inputManager.cc -c -o inputManager.o  

main.o: main.cc
	g++ $(FLAGS) main.cc -c -o main.o  

menuState.o: menuState.cc menuState.h definitions.h
	g++ $(FLAGS) menuState.cc -c -o menuState.o  

minotaur.o: minotaur.cc minotaur.h
	g++ $(FLAGS) minotaur.cc -c -o minotaur.o  

pauseState.o: pauseState.cc pauseState.h definitions.h state.h
	g++ $(FLAGS) pauseState.cc -c -o pauseState.o  

powerEnemy.o: powerEnemy.cc powerEnemy.h
	g++ $(FLAGS) powerEnemy.cc -c -o powerEnemy.o  

powerTower.o: powerTower.cc powerTower.h
	g++ $(FLAGS) powerTower.cc -c -o powerTower.o  

projectile.o: projectile.cc projectile.h
	g++ $(FLAGS) projectile.cc -c -o projectile.o  

stateMachine.o: stateMachine.cc stateMachine.h state.h
	g++ $(FLAGS) stateMachine.cc -c -o stateMachine.o  

Tile.o: Tile.cc Tile.h
	g++ $(FLAGS) Tile.cc -c -o Tile.o  

Timer.o: Timer.cc Timer.h
	g++ $(FLAGS) Timer.cc -c -o Timer.o  

Tower.o: Tower.cc Tower.h
	g++ $(FLAGS) Tower.cc -c -o Tower.o  

waterTower.o: waterTower.cc waterTower.h
	g++ $(FLAGS) waterTower.cc -c -o waterTower.o  

zombie.o: zombie.cc zombie.h
	g++ $(FLAGS) zombie.cc -c -o zombie.o  




.PHONY: clean
clean:
	rm *.o

