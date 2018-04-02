add_executable(unit_tests main.cpp VectorUT.cpp ColorUT.cpp ParserUT.cpp TriangleUT.cpp AABBUT.cpp OctTreeNodeUT.cpp)

target_link_libraries(unit_tests
    libgmock
    libgtest
    primitives
    parser
    logic
)

install(TARGETS unit_tests DESTINATION bin)