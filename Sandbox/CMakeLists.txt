add_executable(Sandbox
    Game.cpp
)


target_include_directories(Sandbox PRIVATE
    ${CMAKE_SOURCE_DIR}/GameEngine
)

target_link_libraries(Sandbox PRIVATE GameEngine glad)
