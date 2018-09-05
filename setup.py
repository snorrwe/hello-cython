from setuptools import setup
from distutils.sysconfig import get_python_lib
import glob
from distutils.extension import Extension

SETUP_REQUIRES = ["Cython==0.28.5"]

try:
    from Cython.Distutils import build_ext
    from Cython.Build import cythonize
except ImportError:
    import subprocess
    import sys
    subprocess.check_call([
        sys.executable,
        '-m',
        'pip',
        'install',
        *SETUP_REQUIRES,
    ])
    from Cython.Distutils import build_ext
    from Cython.Build import cythonize

TEST_DEPENDENCIES = ["pytest"]

setup(
    name="simple_greeting",
    version="0.0.1",
    ext_modules=cythonize([
        Extension(
            "greeting", ["src/greeting.pyx"],
            language="c++",
            extra_compile_args=["-O2", "-std=c++14"])
    ]),
    cmdclass={"build_ext": build_ext},
    data_files=[(get_python_lib(), glob.glob('src/*.so'))],
    author='Daniel Kiss',
    license='MIT',
    zip_safe=False,
    tests_require=TEST_DEPENDENCIES,
    extras_require={'ci': TEST_DEPENDENCIES},
)
