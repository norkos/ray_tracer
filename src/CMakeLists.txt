add_executable (ray_tracer main.cpp )

add_library(primitives SHARED
    AABB.cpp
    OctTreeNode.cpp
    Triangle.cpp
    Color.cpp
)

add_library(parser SHARED
    Parser.cpp
)

add_library(logic SHARED
    Scene.cpp
    OctTree.cpp
)

add_library(media SHARED
    Image.cpp
)

target_link_libraries(ray_tracer media logic primitives parser)