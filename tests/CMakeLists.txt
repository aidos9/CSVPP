if(ENABLE_TESTS)
    include_directories(${CMAKE_SOURCE_DIR}/libs/catch2)
    # CSV tests
    add_executable(CSVTest csvTest.cpp)
    target_link_libraries(CSVTest PRIVATE CSV)
    add_test(NAME CSVTest COMMAND CSVTest)
endif(ENABLE_TESTS)
