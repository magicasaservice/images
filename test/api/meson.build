fs = import('fs')

catch2_dep = dependency('catch2',
    version: '>=3.0.0',
    fallback: ['catch2', 'catch2_dep'],
    default_options: ['tests=false', 'install=false'],
)

test_main = static_library('test-main',
    'base.cpp',
    'max_color_distance.h',
    'max_color_distance.cpp',
    'similar_image.h',
    'similar_image.cpp',
    'test_environment.h',
    dependencies: [catch2_dep, weserv_dep],
)

test_files = files(
    'exceptions/unit-invalid.cpp',
    'exceptions/unit-large.cpp',
    'exceptions/unit-other.cpp',
    'exceptions/unit-timeout.cpp',
    'exceptions/unit-unreadable.cpp',
    'exceptions/unit-unsupported.cpp',
    'parsers/unit-color.cpp',
    'parsers/unit-query.cpp',
    'processors/unit-alignment.cpp',
    'processors/unit-background.cpp',
    'processors/unit-blur.cpp',
    'processors/unit-contrast.cpp',
    'processors/unit-crop.cpp',
    'processors/unit-embed.cpp',
    'processors/unit-filter.cpp',
    'processors/unit-gamma.cpp',
    'processors/unit-mask.cpp',
    'processors/unit-modulate.cpp',
    'processors/unit-orientation.cpp',
    'processors/unit-rotation.cpp',
    'processors/unit-sharpen.cpp',
    'processors/unit-stream.cpp',
    'processors/unit-thumbnail.cpp',
    'processors/unit-tint.cpp',
    'processors/unit-trim.cpp',
    'utils/unit-status.cpp',
)

foreach test_src : test_files
    exe_name = fs.stem(test_src)

    test_exe = executable(exe_name,
        test_src,
        link_with: test_main,
        dependencies: [catch2_dep, weserv_dep],
    )

    test(exe_name,
        test_exe,
        args: ['-F', meson.current_source_dir() / 'fixtures'],
        # Increase the timeout as running the tests with sanitizers
        # enabled could be slower than the default 30 seconds.
        timeout: 120,
    )
endforeach
