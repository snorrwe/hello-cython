from setuptools import setup
from Cython.Build import cythonize
from distutils.sysconfig import get_python_lib
import glob

setup(
    name="simple_greeting",
    version="0.0.1",
    package_dir={'': ''},
    ext_modules=cythonize("src/greeting.pyx"),
    data_files=[(get_python_lib(), glob.glob('src/*.so'))],
    author='Daniel Kiss',
    license='MIT',
    zip_safe=False,
)
