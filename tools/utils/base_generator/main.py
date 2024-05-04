'''
@file: main.py
@author: MoWx 
@brief:
@copyright: 

@attention:
'''
import os

import os

def get_license_header(license=None, max_line_length=80):
    if license is None:
        return None

    license_header = []
    
    # Get the directory path where license files are stored
    license_dir = os.path.join(os.getcwd(), 'licenses')
    
    # Check if the license file exists
    if license not in os.listdir(license_dir):
        raise ValueError('License file "{}" does not exist'.format(license))
    
    # Read the content of the license file and format each line
    with open(os.path.join(license_dir, license), mode='r', encoding='utf-8') as fp:
        for line in fp:
            stripped_line = line.strip()
            
            # Skip empty lines and comments (lines starting with '#')
            if len(stripped_line) > 0 and not stripped_line.startswith('#'):
                # Limit the line length
                segments = [stripped_line[i:i+max_line_length] for i in range(0, len(stripped_line), max_line_length)]
                formatted_segments = []
                for segment in segments:
                    num_spaces = max_line_length - len(segment) + 3
                    formatted_segment = '** {}{} **'.format(segment.strip(), ' ' * num_spaces)
                    formatted_segments.append(formatted_segment)
                formatted_line = '\n'.join(formatted_segments)
                license_header.append(formatted_line)
                
    return '\n'.join(license_header) + '\n'
            
c_file_license = None
if c_file_license is not None:
    c_file_license_header = get_license_header(c_file_license, 71)

    c_file_license_headerx = '''
/*******************************************************************************
**  LICENSE:                                                                  **
{}
/*******************************************************************************
    '''.format(c_file_license_header)
else:
    c_file_license_headerx = '''
/*******************************************************************************
**                                                                            **
**  Copyright (C) AUTOSarZs olc (2019)		                                  **
**                                                                            **
**  All rights reserved.                                                      **
**                                                                            **
**  This document contains proprietary information belonging to AUTOSarZs     **
**  olc . Passing on and copying of this document, and communication          **
**  of its contents is not permitted without prior written authorization.     **
**                                                                            **
********************************************************************************
    '''
c_file_header = ''' 
/*******************************************************************************
**                                                                            **
**  FILENAME     :                  		                                  **
**                                                                            **
**  VERSION      :                                                            **
**                                                                            **
**  DATE         :                                                            **
**                                                                            **
**  VARIANT      :                                                            **
**                                                                            **
**  PLATFORM     :                                                            **
**                                                                            **
**  AUTHOR       :                  	                                      **
**                                                                            **
**  VENDOR       :                                                            **
**                                                                            **
**                                                                            **
**  DESCRIPTION  :                                                            **
**                                                                            **
**  SPECIFICATION(S) :                                                        **
**                                                                            **
**  MAY BE CHANGED BY USER :                                                  **
**                                                                            **
*******************************************************************************/
'''

c_file_headers = '''
/*****************************************************************************************/
/*                                   Include Common headres                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Include Other  headres                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Include Component headres                           */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Macro Definition                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Definition                                    */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local types Definition                              */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                Exported Variables Definition                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                Local Variables Definition                             */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Function Declaration                          */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Local Function Definition                           */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                   Global Function Definition                          */
/*****************************************************************************************/
'''

c_file_service_header = ''' 
/************************************************************************************
* Service Name: 
* Service ID[hex]: 
* Sync/Async: 
* Reentrancy: 
* Parameters (in):
*     [type][name] : [decsription]
*     [type][name] : [decsription]
* Parameters (inout): 
*     [type][name] : [decsription]
*     [type][name] : [decsription]
* Parameters (out): 
*     [type][name] : [decsription]
*     [type][name] : [decsription]
* Return value: Std_ReturnType
* Description: 
************************************************************************************/
'''

c_file_function_header = '''
/****************************************************************************************/
/*    Function Description :                                                            */
/*                                                                                      */
/*    Parameter in         :                                                            */
/*    Parameter inout      :                                                            */
/*    Parameter out        :                                                            */
/*    Return value         :                                                            */
/*    Requirment           :                                                            */
/*    Notes                :                                                            */
/*****************************************************************************************/
'''

h_file_license_headerx = c_file_license_headerx
h_file_header = c_file_header

h_file_headers = '''
/*****************************************************************************************/
/*                                   Include headres                                     */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                    Macros Definition                                  */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                    Structs Definition                                 */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                    Enums Definition                                   */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                    Unions Definition                                  */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                    User Type Definition                               */
/*****************************************************************************************/

/*****************************************************************************************/
/*                                    Global Functions Prototype                         */
/*****************************************************************************************/
'''

# C File org
GENERATED_FILES_DIR = 'generated_files'

def write_to_files(files_names=None):
    if files_names is None:
        return -1
    
    if not os.path.exists(f'{os.getcwd()}/{GENERATED_FILES_DIR}'):
        os.mkdir(f'{os.getcwd()}/{GENERATED_FILES_DIR}')
        
    for file in files_names:
        with open(f'{GENERATED_FILES_DIR}/{file}' + '.c', 'w') as f:
            f.write(c_file_license_headerx)
            f.write(c_file_header)
            f.write(c_file_headers)
            f.write(c_file_service_header)
            f.write(c_file_function_header)
            
    for file in files_names:
        with open(f'{GENERATED_FILES_DIR}/{file}' + '.h', 'w') as f:
            f.write(h_file_license_headerx)
            f.write(h_file_header)
            f.write(f"\n#if !defined( __{file.upper()}_H__ )\n#define ( __{file.upper()}_H__ ) \n")
            f.write("\n#if defined(cplusplus) || defined(c_plus_plus)\nextern \"c\" {\n")
            f.write("#endif /* defined(cplusplus) || defined(c_plus_plus) */ \n\n")
            f.write(h_file_headers)
            f.write("\n#if defined(cplusplus) || defined(c_plus_plus)\n}\n")
            f.write("#endif /* defined(cplusplus) || defined(c_plus_plus) */")
            f.write(f"\n\n#endif /* ( __{file.upper()}_H__ ) */")
            
if __name__ == '__main__':
    file_names = []
        
    with open('gen_files.txt', 'r') as file:
        for g_files in file:
            file_names.append(g_files.strip())
        
    write_to_files(file_names)