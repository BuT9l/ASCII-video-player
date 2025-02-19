project('BadAppleTerminal', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

opencv = dependency('opencv4')

executable('videoplayer.bin',
           'code.cpp',
           dependencies : [opencv],
           install : false)
