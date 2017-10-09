cmake_minimum_required(VERSION 3.6)
project(ia)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/Board.cpp include/Board.h include/Pawn.h src/Pawn.cpp src/PawnMove.cpp include/PawnMove.h include/Pawn.h src/Pawn.cpp src/Move.cpp include/Move.h include/Direction.h src/Turn.cpp include/Turn.h src/MoveNode.cpp include/MoveNode.h src/MoveTree.cpp include/MoveTree.h src/MoveStack.cpp include/MoveStack.h src/NegMaxNode.cpp include/NegMaxNode.h include/RandomCarlo.h src/RandomCarlo.cpp include/MonteCarloNode.h src/MonteCarloNode.cpp include/SSS.h include/SSSNode.h src/SSS.cpp src/SSSNode.cpp include/NegMax.h src/NegMax.cpp include/AI.h src/AI.cpp)
add_executable(ia ${SOURCE_FILES})