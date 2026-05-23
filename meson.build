project('opengl', ['cpp', 'c'])

glfw_dep = dependency('glfw3')
gl_dep = dependency('opengl')

executable(
    'opengl',
    'src/main.cpp', 'vendor/glad/src/glad.c',
    cpp_args: '-O1',
    include_directories: include_directories('vendor/glad/include'),
    dependencies: [glfw_dep, gl_dep]
)
