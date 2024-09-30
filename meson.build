project('printer-gui', 'c')
cc = meson.get_compiler('c')

subdir('include')
subdir('src')

deps = []
deps += cc.find_library('m', required : true)

executable('printer-gui', sources, dependencies: deps, include_directories: inc_dir)
