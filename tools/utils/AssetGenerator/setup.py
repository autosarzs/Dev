from setuptools import setup, find_packages

setup(
    name='asset_generator',
    version='2.0.0',
    description='A project made for file template generator',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    author='MoWx',
    author_email='mohamedashrafwx@gmail.com',
    url='https://github.com/mohamedashraf-eng',
    # 
    packages=find_packages(),
    #
    install_requires=[
        'wheel',
        'tabulate',
        'argparse'
    ],
    #
    entry_points={
        'console_scripts': [
        ],
    },
    #
    python_requires=">=3.8",
    #
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
)
