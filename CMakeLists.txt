cmake_minimum_required(VERSION 3.10)
project(ConCom)

# Wymagana wersja C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Zależności do OpenCL
find_package(OpenCL REQUIRED)

# Źródła
set(SOURCES
    src/Client.cpp
    src/Transaction.cpp
    src/Solver.cpp
    src/ComputeRes.cpp
    src/SolverFactory.cpp
    src/SolverImpl.cpp
)

set(HEADERS
    src/Client.h
    src/Transaction.h
    src/Solver.h
    src/ComputeRes.h
    src/SolverFactory.h
    src/OpType.h
    src/TransactionState.h
    src/SolverImpl.h
)

# Utworzenie biblioteki
add_library(ConCom ${SOURCES} ${HEADERS})

# Ustawienia include
target_include_directories(ConCom
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_BINARY_DIR}
)

# Linkowanie do OpenCL
target_link_libraries(ConCom PUBLIC OpenCL::OpenCL)