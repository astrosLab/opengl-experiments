project('opengl', ['cpp', 'c'])

glfw_dep = dependency('glfw3')
gl_dep = dependency('opengl')

shader_dir = meson.source_root() / 'shaders'

run_command('cp', '-r', 'shaders', meson.current_build_dir(), check: true)

sources = files(
  'src/main.cpp',
  'src/shader.cpp',
)

includes = include_directories(['include', 'vendor/glad/include'])

executable(
    'opengl',
    sources, 'vendor/glad/src/glad.c',
    cpp_args: ['-O1', '-DSHADER_DIR="' + shader_dir + '"'],
    include_directories: includes,
    dependencies: [glfw_dep, gl_dep]
)
