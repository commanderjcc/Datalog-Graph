cmake_minimum_required(VERSION 3.16)
project(dl_graph)

set(CMAKE_CXX_STANDARD 17)

add_executable(dl_graph main.cpp Database.cpp Database.h DatalogProgram.cpp DatalogProgram.h Interpreter.cpp Interpreter.h Parameter.cpp Parameter.h Parser.cpp Parser.h Predicate.cpp Predicate.h Relation.cpp Relation.h Rule.cpp Rule.h Scanner.cpp Scanner.h Scheme.cpp Scheme.h Token.cpp Token.h Tuple.cpp Tuple.h Node.cpp Node.h Graph.cpp Graph.h)
