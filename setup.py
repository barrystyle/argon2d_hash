from distutils.core import setup, Extension

argon2d_hash_module = Extension('argon2d_hash',
                               sources = ['argon2d_module.c',
                                          'argon2d.c',
                                          'argon2d/argon2.c',
                                          'argon2d/core.c',
                                          'argon2d/encoding.c',
                                          'argon2d/opt.c',
                                          'argon2d/thread.c',
                                          'blake2/blake2b.c'],
                            include_dirs=['.', './argon2d', './blake2'])

setup (name = 'argon2d_hash',
       version = '1.0',
       ext_modules = [argon2d_hash_module])
