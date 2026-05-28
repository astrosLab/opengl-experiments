project(
  'opengl', ['cpp', 'c'],
  version: 'experiment',
  default_options: ['cpp_std=c++17']
)

# Dependencies
glfw_dep = dependency('glfw3', version : '>=3.3')
gl_dep = dependency('opengl')
glm_dep = dependency('glm')

# Source Files
sources = files(
  'src/main.cpp',
  'src/shader.cpp',
)

# Includes
includes = include_directories(
  ['include', 'vendor/glad/include', 'vendor/stb_image/include']
)

# Folders Included
shader_dir = meson.project_source_root() / 'shaders'
texture_dir = meson.project_source_root() / 'textures'

# Executable File
executable(
    'opengl',
    sources, 'vendor/glad/src/glad.c',
    cpp_args: [
      '-O1', 
      '-DSHADER_DIR="' + shader_dir + '"',
      '-DTEXTURE_DIR="' + texture_dir + '"'
    ],
    include_directories: includes,
    dependencies: [glfw_dep, gl_dep]
)
