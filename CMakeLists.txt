cmake_minimum_required(VERSION 3.30)
project(PacMan_Game)

set(CMAKE_CXX_STANDARD 20)

add_executable(PacMan_Game private/main.cpp
        public/PM_Map.h
        private/PM_PacMan.cpp
        public/PM_PacMan.h
        private/PM_Map.cpp
        private/Ghost.cpp
        public/Ghost.h
        private/RedGhost.cpp
        public/RedGhost.h
        private/PM_PinkGhost.cpp
        public/PM_PinkGhost.h
)
