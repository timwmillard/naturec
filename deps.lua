return {
    config = { dir = 'deps' },
    {
        'raysan5/raylib',
        tag = '6.0',
        flatten = false,
        dest = 'deps/raylib',
        files = {
            'src/**',
            'cmake/**',
            'CMakeLists.txt',
            'CMakeOptions.txt',
            'README.md',
            'LICENSE',
            'raylib.pc.in',
        },
    },
    {
        'erincatto/box2d',
        tag = 'v3.1.1',
        flatten = false,
        dest = 'deps/box2d',
        files = {
            'src/**',
            'include/**',
            'extern/**',
            'shared/**',
            'CMakeLists.txt',
            'src/CMakeLists.txt',
            'shared/CMakeLists.txt',
        },
    },
}
