'''
@file: main.py
@author: Mohamed Ashraf Wx
@brief: This is the main entry point for the generator
'''

import subprocess
import argparse

def get_python_command():
    import os
    if os.name == 'posix':  # Unix-like systems
        try:
            subprocess.run(['which', 'python3'], check=True)
            return 'python3'
        except subprocess.CalledProcessError:
            return 'python'
    elif os.name == 'nt':  # Windows
        python_exe = os.environ.get('PYTHON3_EXE', 'python')
        try:
            # Check if python3 is available
            subprocess.run([python_exe, '--version'], check=True)
            return python_exe
        except subprocess.CalledProcessError:
            return 'python'
    else:
        return 'python'

GENERATOR_ENTRY_POINT_PATH = "src/generator.py"
VERBOSE_MODE = False

if __name__ == '__main__':
    '''
    This is the main entry point for the generator.

    @author: Mohamed Ashraf Wx
    '''
    parser = argparse.ArgumentParser(
        prog='generator',
        description='This program generates a template for [Autosarzs olc]',
        epilog=
'''
This is the main entry point for the generator.

@author: Mohamed Ashraf Wx

This program is created to support template generation for the autosarzs olc developing.

Copyright (C) 2024, Mohamed Ashraf Wx.
LICENSE:
    This Source Code Form is subject to the terms of the Mozilla Public
    License, v. 2.0. If a copy of the MPL was not distributed with this
    file, You can obtain one at http://mozilla.org/MPL/2.0/.
'''
    )
    #
    exclusive_group = parser.add_mutually_exclusive_group()
    parser.add_argument('-u', '--usage', action='store_true', help='Prints the usage for this program.')
    parser.add_argument('-v', '--verbose', action='store_true', help='Toggles the verbose mode for the generator.')
    parser.add_argument('-cc', '--clear-cache', action='store_true', help='Clear the generator cache')
    parser.add_argument('-pc', '--pass-config', help='Adds a new config file to run with the generator.')
    exclusive_group.add_argument('-rd', '--run-default', action='store_true', help='Runs the generator with default configuration.')
    exclusive_group.add_argument('-r', '--run', action='store_true', help='Runs the generator with passed configuration.')
    
    args = parser.parse_args()
    
    if args.usage:
        print('''
                                             AUTOSarZs olc
                                       ------------------------
                                       AUTOSAR free for learning
                                       
            This program is used to generate a template for autosarzs olc developing.
            To use this program proberly you need to run with the command " main.py -rd " or " main.py -r "
              ''')
    #
    try:
        if args.verbose:
            VERBOSE_MODE = True
        else:
            VERBOSE_MODE = False
            
        if args.pass_config:
            print(" Not implemented ")
        
        if args.run_default:
            cmd = f"{get_python_command()} {GENERATOR_ENTRY_POINT_PATH}"
            subprocess.run(cmd, shell=False)
        
        if args.run:
            cmd = f"{get_python_command()} {GENERATOR_ENTRY_POINT_PATH}"
            subprocess.run(cmd, shell=False)
        
        if args.clear_cache:
            cmd = "rm .cache/*"
            subprocess.run(cmd, shell=False)
            
    except Exception as e:
        print("Unexpected error occured.")
        print(f"Error: {e}")
        exit(1)