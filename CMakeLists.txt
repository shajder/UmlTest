cmake_minimum_required(VERSION 3.10)
project(ConCom)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenCL REQUIRED)

if(MSVC)
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MDd")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MDd")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

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

add_library(ConCom SHARED ${SOURCES} ${HEADERS})


target_link_libraries(ConCom PUBLIC OpenCL::OpenCL)
target_compile_definitions(ConCom PRIVATE BUILDING_CLIENT_DLL)



enable_testing()

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(externals/googletest)

add_executable(test_client src/tests/smoke/ClientCreate.cpp)
target_link_libraries(test_client gtest gtest_main ConCom)
target_include_directories(test_client PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src  PRIVATE ${PROJECT_BINARY_DIR})

add_executable(test_client_transaction src/tests/smoke/ClientCreateTransaction.cpp)
target_link_libraries(test_client_transaction gtest gtest_main ConCom)
target_include_directories(test_client_transaction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src  PRIVATE ${PROJECT_BINARY_DIR})

add_test(NAME test_client COMMAND test_client)
add_test(NAME test_client_transaction COMMAND test_client_transaction)