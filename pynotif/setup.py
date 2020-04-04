#!/usr/bin/python3

from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize


notifExtension = Extension(
    name="pynotif",
    sources=["pynotif.pyx"],
    libraries=["vlc", "notify", "notification"],
    library_dirs=["/usr/lib64/", "../libnotification/"],
    include_dirs=["/usr/include/glib-2.0/", "/usr/include/gdk-pixbuf-2.0/",
                  "/usr/lib64/glib-2.0/include/", "../libnotification/"]
)

setup(
    name="pynotif",
    version="0.1.0",
    description="Another Python API for GNU/Linux desktop notification service with in-built notification sound support",
    long_description=open("../README.md").read(),
    url="https://itzmeanjan.github.io/pynotif/",
    author="Anjan Roy",
    author_email="anjanroy@yandex.com",
    license="MIT",
    classifiers=[
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.7",
    ],
    ext_modules=[
        cythonize(notifExtension, compiler_directives={
                          'language_level': '3'})
    ]
)
