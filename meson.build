project('printer-gui', 'c')
cc = meson.get_compiler('c')

subdir('include')
subdir('src')

deps = []
deps += cc.find_library('m', required : true)
deps += dependency('freetype2')

add_global_arguments('-DWall', language : 'c')
add_global_arguments('-DWerror', language : 'c')


executable('printer-gui', sources, dependencies: deps, include_directories: inc_dir)
