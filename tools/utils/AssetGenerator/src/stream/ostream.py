import defaults
from plogger import logy
import os


class ostream(object):
    def __init__(
        self,
        base_data: dict = None,
        headers: list = None,
        sections: list = None,
        common_include_headers=None,
        other_include_headers=None,
        component_include_headers=None,
        macros=None,
        exported_vars=None,
        local_vars=None,
        structs=None,
        enums=None,
        unions=None,
        types=None,
        local_functions_declaration=None,
        local_functions_definition=None,
        global_functions_definition=None,
    ):
        self.__logger = logy(module_name="ostream")
        #
        self.__output_dir = defaults.OUTPUT_DIR
        #
        self.__base_data = base_data
        self.__headers = headers
        self.__sections = sections
        self.__common_include_headers = common_include_headers
        self.__other_include_headers = other_include_headers
        self.__component_include_headers = component_include_headers
        self.__macros = macros
        self.__exported_vars = exported_vars
        self.__local_vars = local_vars
        self.__structs = structs
        self.__enums = enums
        self.__unions = unions
        self.__types = types
        self.__local_functions_declaration = local_functions_declaration
        self.__local_functions_definition = local_functions_definition
        self.__global_functions_definition = global_functions_definition
        # Pre
        self.__initiate_file_data()

    def __initiate_file_data(self):
        self.__file_type = self.__base_data.get("name", "null")
        self.__file_name = self.__base_data.get("source_file", "null")
        self.__file_extension = self.__base_data.get("file_extension", "null")
        self.__file_description = self.__base_data.get("description", "null")

    def __stream_out_to_file(self, file_name: str = None, msg: str = None):
        assert file_name is not None
        with open(file_name, "a") as f2w:
            f2w.write(msg)

    def put_file_headers(self, headers: any = None):
        assert headers is not None

        self.__logger.info(f"Putting file headers: {self.__full_fp}")

        try:

            # Hard coded license
            # TODO(Wx): Add license selector / json
            hard_coded_license = """
/********************************************************************************************            
**                                    AUTOSarZs olc
**                              ------------------------
**                              AUTOSAR free for learning
** 
**   Copyright (C) 2019 AUTOSarZs olc
**   All rights reserved.                                                   
**                                                                   
**   This document contains proprietary information belonging to AUTOSarZs olc. 
**   Passing on and copying of this document, and communication       
**   of its contents is not permitted without prior written authorization.  
**                                                       
**   This software is licensed under the Mozilla Public License Version 2.0.
**   For details, see the LICENSE.txt file in the root directory of this project.
********************************************************************************************/
"""
            self.__stream_out_to_file(self.__full_fp, hard_coded_license)

            self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 90 + "\n")

            # max_key_length = max(len(value) for value in headers.values())
            for key, value in headers.items():
                line = f"** {key.ljust(23)} : {value.ljust(60)} **\n"
                self.__stream_out_to_file(self.__full_fp, line)

            self.__stream_out_to_file(self.__full_fp, "*" * 91 + "*/\n\n")

        except Exception as e:
            self.__logger.error(f"Error while putting file headers `{self.__full_fp}`")
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(f"Successfully putted file headers `{self.__full_fp}`")

    def __fill_include_header(self, header):
        if header.conditional_include_macro:
            self.__stream_out_to_file(self.__full_fp, f"#if {header.name.upper()}\n")

        if bool(header.description.strip()):
            self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
            self.__stream_out_to_file(self.__full_fp, "Description: \n")
            self.__stream_out_to_file(
                self.__full_fp, f"{header.description.rjust(5)}\n"
            )
            self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")

        self.__stream_out_to_file(
            self.__full_fp,
            f'#{"  "if header.conditional_include_macro else ""}include "{header.name}" \n',
        )

        if header.conditional_include_macro:
            self.__stream_out_to_file(
                self.__full_fp, f"#endif /* {header.name.upper()} */\n"
            )

    def __fill_common_headers(self):
        self.__logger.info(f"Filling common headers section")

        try:
            for header in self.__common_include_headers:
                self.__fill_include_header(header)
        except Exception as e:
            self.__logger.error(f"Error while filling common headers section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling common headers section")

    def __fill_other_headers(self):
        self.__logger.info(f"Filling other headers section")

        try:
            for header in self.__other_include_headers:
                self.__fill_include_header(header)
        except Exception as e:
            self.__logger.error(f"Error while filling other headers section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling other headers section")

    def __fill_component_headers(self):
        self.__logger.info(f"Filling component headers section")

        try:
            for header in self.__component_include_headers:
                self.__fill_include_header(header)
        except Exception as e:
            self.__logger.error(f"Error while filling component headers section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling component headers section")

    def __fill_macros_definition(self):
        self.__logger.info(f"Filling macros definition section")

        try:
            for macro in self.__macros:
                if macro.conditional_include_macro:
                    self.__stream_out_to_file(
                        self.__full_fp, f"#if {macro.name.upper()}"
                    )

                if bool(macro.description.strip()):
                    self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
                    self.__stream_out_to_file(self.__full_fp, "Description: \n")
                    self.__stream_out_to_file(
                        self.__full_fp, f"{macro.description.rjust(5)}\n"
                    )
                    self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")
                self.__stream_out_to_file(
                    self.__full_fp,
                    f'#{"  " if macro.conditional_include_macro else ""}define {macro.name}\n',
                )
                if macro.conditional_include_macro:
                    self.__stream_out_to_file(
                        self.__full_fp, f"#endif /* {macro.name.upper()} */\n"
                    )

        except Exception as e:
            self.__logger.error(f"Error while filling macros definition section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling macros definition section")

    def __fill_structs_definition(self):
        self.__logger.info(f"Filling structs definition section")

        try:
            for struct in self.__structs:
                if struct.conditional_include_macro:
                    self.__stream_out_to_file(
                        self.__full_fp, f"#if {struct.name.upper()}"
                    )

                if bool(struct.description.strip()):
                    self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
                    self.__stream_out_to_file(self.__full_fp, "Description: \n")
                    self.__stream_out_to_file(
                        self.__full_fp, f"{struct.description.rjust(5)}\n"
                    )
                    self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")

                self.__stream_out_to_file(
                    self.__full_fp,
                    f"struct {struct.name}{';' if not struct.list_of_members else ' {'}\n",
                )
                if struct.list_of_members is not None:
                    for member in struct.list_of_members:
                        self.__stream_out_to_file(
                            self.__full_fp,
                            f"{member.datatype.rjust(5)} {member.name}{';' if not member.bit_field else f':{member.bit_field}'}\n",
                        )
                self.__stream_out_to_file(
                    self.__full_fp, f"{'}' if struct.list_of_members else ''};\n",
                )
                if struct.conditional_include_macro:
                    self.__stream_out_to_file(
                        self.__full_fp, f"#endif /* {struct.name.upper()} */\n"
                    )

        except Exception as e:
            self.__logger.error(f"Error while filling structs definition section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling structs definition section")

    def __fill_enums_definition(self):
        self.__logger.info(f"Filling enums definition section")

        try:
            for enum in self.__enums:
                if bool(enum.description.strip()):
                    self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
                    self.__stream_out_to_file(self.__full_fp, "Description: \n")
                    self.__stream_out_to_file(
                        self.__full_fp, f"{enum.description.rjust(5)}\n"
                    )
                    self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")

                self.__stream_out_to_file(
                    self.__full_fp,
                    f"enum {enum.name}{';' if not enum.dict_of_members else ' {'}\n",
                )

                for key, value in enum.dict_of_members.items():
                    self.__stream_out_to_file(
                        self.__full_fp, f"{key.rjust(8)} = {value.rjust(5)},\n"
                    )

                self.__stream_out_to_file(
                    self.__full_fp, f"{'}' if enum.dict_of_members else ''};\n",
                )

        except Exception as e:
            self.__logger.error(f"Error while filling enums definition section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling enums definition section")

    def __fill_unions_definition(self):
        self.__logger.info(f"Filling unions definition section")

        try:
            for union in self.__unions:
                if bool(union.description.strip()):
                    self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
                    self.__stream_out_to_file(self.__full_fp, "Description: \n")
                    self.__stream_out_to_file(
                        self.__full_fp, f"{union.description.rjust(5)}\n"
                    )
                    self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")

                self.__stream_out_to_file(
                    self.__full_fp,
                    f"union {union.name}{';' if not union.list_of_members else ' {'}\n",
                )
                if union.list_of_members is not None:
                    for member in union.list_of_members:
                        self.__stream_out_to_file(
                            self.__full_fp,
                            f"{member.datatype.rjust(5)} {member.name}{';' if not member.bit_field else f':{member.bit_field}'}\n",
                        )
                self.__stream_out_to_file(
                    self.__full_fp, f"{'}' if union.list_of_members else ''};\n",
                )

        except Exception as e:
            self.__logger.error(f"Error while filling unions definition section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling unions definition section")

    def __fill_types_definition(self):
        self.__logger.info(f"Filling types definition section")

        try:
            for type in self.__types:
                if bool(type.description.strip()):
                    self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
                    self.__stream_out_to_file(self.__full_fp, "Description: \n")
                    self.__stream_out_to_file(
                        self.__full_fp, f"{type.description.rjust(5)}\n"
                    )
                    self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")

                self.__stream_out_to_file(
                    self.__full_fp,
                    f"typedef {type.type} {type.base_name} {type.new_name};\n",
                )

        except Exception as e:
            self.__logger.error(f"Error while filling types definition section")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling types definition section")

    def __fill_exported_variables_definition(self):
        self.__logger.info(f"Filling exported variables definition section")

        try:
            for var in self.__exported_vars:
                if bool(var.description.strip()):
                    self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
                    self.__stream_out_to_file(self.__full_fp, "Description: \n")
                    self.__stream_out_to_file(
                        self.__full_fp, f"{var.description.rjust(5)}\n"
                    )
                    self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")

                self.__stream_out_to_file(
                    self.__full_fp, f"extern {var.datatype} {var.name};\n",
                )

        except Exception as e:
            self.__logger.error(
                f"Error while filling exported variables definition section"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling exported variables definition section")

    def __fill_local_variables_definition(self):
        self.__logger.info(f"Filling local variables definition section")

        try:
            for var in self.__local_vars:
                if bool(var.description.strip()):
                    self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 40 + "\n")
                    self.__stream_out_to_file(self.__full_fp, "Description: \n")
                    self.__stream_out_to_file(
                        self.__full_fp, f"{var.description.rjust(5)}\n"
                    )
                    self.__stream_out_to_file(self.__full_fp, "*" * 41 + "*/\n")

                if bool(var.attributes.strip()):
                    self.__stream_out_to_file(
                        self.__full_fp, f"{var.attributes}\n",
                    )
                self.__stream_out_to_file(
                    self.__full_fp, f"{var.datatype} {var.name};\n",
                )

        except Exception as e:
            self.__logger.error(
                f"Error while filling local variables definition section"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling local variables definition section")

    def __fill_function_doc(self, function):
        _func_doc_lookup = [
            "description",
            "parameters in",
            "parameters in out",
            "parameters out",
            "return value",
            "requirement",
            "notes",
        ]
        _service_doc_lookup = [
            "service name",
            "service id",
            "sync async",
            "reentrancy",
            "parameters in",
            "parameters in out",
            "parameters out",
            "return value",
            "description",
        ]

        function_data = function.data
        self.__stream_out_to_file(self.__full_fp, "/*" + "*" * 70 + "\n")
        # Service
        if "true" == function_data["service_flag"]:
            line = ""
            for k in _service_doc_lookup:
                line += f"** {k.title().ljust(17)} : "

                k = k.replace(" ", "_")
                if k in function_data:
                    line += f"{function_data[k].ljust(46)}\n"

                elif k == "parameters_in":
                    line += "("
                    for arg in function.list_of_args:
                        line += f"{arg.name}, "
                    line = line[:-2]
                    line += ")\n"

                elif k == "parameters_in_out":
                    line += f"None\n"

                elif k == "parameters_sout":
                    line += f"None\n"

                else:
                    line += f"None\n"

            self.__stream_out_to_file(self.__full_fp, line)

        # Normal Function
        else:
            # max_key_length = max(len(value) for value in function_data.values())
            line = ""
            for k in _func_doc_lookup:
                line += f"** {k.title().ljust(17)} : "

                if k in function_data:
                    line += f"{function_data[k].ljust(46)}\n"
                elif k == "parameters in":
                    line += "("
                    for arg in function.list_of_args:
                        line += f"{arg.name}, "
                    line = line[:-2]
                    line += ")\n"

                elif k == "parameters in out":
                    line += f"None\n"

                elif k == "parameters out":
                    line += f"None\n"

                else:
                    line += f"None\n"

            self.__stream_out_to_file(self.__full_fp, line)

        self.__stream_out_to_file(self.__full_fp, "*" * 71 + "*/\n")

    def __fill_local_functions_declaration(self):
        self.__logger.info(f"Filling local functions declaration section")

        try:
            for function in self.__local_functions_declaration:
                self.__fill_function_doc(function)

                if function.compiler is not None:
                    for key, value in function.compiler.items():
                        self.__stream_out_to_file(
                            self.__full_fp, f"{value}\n",
                        )

                if "local" == function.data["local_global"]:
                    self.__stream_out_to_file(self.__full_fp, f"static ")

                self.__stream_out_to_file(
                    self.__full_fp,
                    f"{function.return_type} {function.name}({', '.join(f'{arg.datatype} {arg.name}' for arg in function.list_of_args)});\n\n",
                )

        except Exception as e:
            self.__logger.error(
                f"Error while filling local functions declaration section"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling local functions declaration section")

    def __fill_local_functions_definition(self):
        self.__logger.info(f"Filling local functions defintion section")

        try:
            for function in self.__local_functions_definition:
                self.__fill_function_doc(function)

                if function.compiler is not None:
                    for key, value in function.compiler.items():
                        self.__stream_out_to_file(
                            self.__full_fp, f"{value}\n",
                        )

                if "local" == function.data["local_global"]:
                    self.__stream_out_to_file(self.__full_fp, f"static ")

                self.__stream_out_to_file(
                    self.__full_fp,
                    f"{function.return_type} {function.name}({', '.join(f'{arg.datatype} {arg.name}' for arg in function.list_of_args)})\n",
                )
                self.__stream_out_to_file(self.__full_fp, "{\n")
                for arg in function.list_of_args:
                    self.__stream_out_to_file(
                        self.__full_fp, f"\tUNUSED({arg.name});\n"
                    )
                self.__stream_out_to_file(self.__full_fp, "\n\treturn 0xFFFFU; \n}\n\n")

        except Exception as e:
            self.__logger.error(
                f"Error while filling local functions defintion section"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling local functions defintion section")

    def __fill_global_functions_definition(self):
        self.__logger.info(f"Filling global functions defintion section")

        try:
            for function in self.__global_functions_definition:
                self.__fill_function_doc(function)

                if function.compiler is not None:
                    for key, value in function.compiler.items():
                        self.__stream_out_to_file(
                            self.__full_fp, f"{value}\n",
                        )

                if "local" == function.data["local_global"]:
                    self.__stream_out_to_file(self.__full_fp, f"static ")

                self.__stream_out_to_file(
                    self.__full_fp,
                    f"{function.return_type} {function.name}({', '.join(f'{arg.datatype} {arg.name}' for arg in function.list_of_args)})\n",
                )
                self.__stream_out_to_file(self.__full_fp, "{\n")
                for arg in function.list_of_args:
                    self.__stream_out_to_file(
                        self.__full_fp, f"\tUNUSED({arg.name});\n"
                    )
                self.__stream_out_to_file(self.__full_fp, "\n\treturn 0xFFFFU; \n}\n\n")

        except Exception as e:
            self.__logger.error(
                f"Error while filling global functions declaration section"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling global functions declaration section")

    def __fill_sections(self, section):
        self.__logger.info(f"Filling sections: {section}")

        try:
            pre_defined_sections_funcptr = {
                "include_common_headers": self.__fill_common_headers,
                "include_other_headers": self.__fill_other_headers,
                "include_component_headers": self.__fill_component_headers,
                "local_macros_definition": self.__fill_macros_definition,
                "local_structs_definition": self.__fill_structs_definition,
                "local_enums_definition": self.__fill_enums_definition,
                "local_unions_definition": self.__fill_unions_definition,
                "local_types_definition": self.__fill_types_definition,
                "exported_variables_definition": self.__fill_exported_variables_definition,
                "local_variables_definition": self.__fill_local_variables_definition,
                "local_functions_declaration": self.__fill_local_functions_declaration,
                "local_functions_definition": self.__fill_local_functions_definition,
                "global_functions_definition": self.__fill_global_functions_definition,
            }

            pre_defined_sections_funcptr.get(
                section, lambda: self.__logger.debug("Invalid section")
            )()

        except Exception as e:
            self.__logger.error(f"Error while filling sections: {section}")
            self.__logger.error(f"Error: {e}")
            exit(1)
        self.__logger.info(f"Done filling sections: {section}")

    def put_file_sections(self, sections: any = None):
        assert sections is not None

        self.__logger.info(f"Putting file sections: {self.__full_fp}")

        try:
            for key, value in sections.items():
                self.__stream_out_to_file(self.__full_fp, "\n/*" + "*" * 90 + "\n")
                line = f"**{value.center(88)}**\n"
                self.__stream_out_to_file(self.__full_fp, line)
                self.__stream_out_to_file(self.__full_fp, "*" * 91 + "*/\n\n")

                self.__fill_sections(key)

        except Exception as e:
            self.__logger.error(f"Error while putting file sections `{self.__full_fp}`")
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(f"Successfully putted file sections `{self.__full_fp}`")

    def __create_a_file(self, file_path: str = None):
        if os.path.exists(file_path):
            dir_name = os.path.dirname(file_path)
            file_name = os.path.basename(file_path)
            new_path = f"{dir_name}/backup/{file_name}"
            self.__create_a_dir(f"{dir_name}/backup")
            self.__stream_out_to_file(new_path, "")
            # Copy contents
            import shutil

            shutil.copyfile(file_path, new_path)
            
            os.remove(file_path)
            self.__stream_out_to_file(file_path, "")
        else:
            self.__stream_out_to_file(file_path, "")

    def __create_a_dir(self, dir_path: str = None):
        if os.path.exists(dir_path):
            pass
        else:
            os.makedirs(dir_path, exist_ok=True)

    def put_file(self, file_fp: str = None):
        assert file_fp is not None
        self.__logger.info(f"Putting file: {file_fp}")

        try:
            # TODO(Wx): Design a better way
            if defaults.WHOLE_MODULE_DIR:
                # Create directory
                base_filename = (
                    self.__file_name.lower()
                    if defaults.MODULE_ALL_SMALL_CASE
                    else self.__file_name
                )
                base_dir = os.path.join(
                    self.__output_dir,
                    f"{base_filename}_{defaults.MODULE_DIR_EXTRA_EXT}",
                )

                self.__create_a_dir(base_dir)

                self.__sources_dir = f"{base_dir}/{defaults.MODULE_SOURCES_DIR_NAME}"
                self.__create_a_dir(self.__sources_dir)

                self.__tests_dir = f"{base_dir}/{defaults.MODULE_TESTS_DIR_NAME}"
                self.__create_a_dir(self.__tests_dir)
                self.__create_a_dir(f"{self.__tests_dir}/unit")
                self.__create_a_dir(f"{self.__tests_dir}/integration")

                self.__create_a_dir(f"{self.__tests_dir}/unit/test_runners")
                self.__create_a_file(
                    f"{self.__tests_dir}/unit/test_runners/all_tests.c"
                )
                self.__create_a_file(
                    f"{self.__tests_dir}/unit/test_runners/{base_filename}_Runner.c"
                )

                self.__tools_dir = f"{base_dir}/{defaults.MODULE_TOOLS_DIR_NAME}"
                self.__create_a_dir(self.__tools_dir)

                if defaults.MODULE_CMAKE_INCLUDED:
                    self.__cmake_dir = (
                        f"{self.__tools_dir}/{defaults.MODULE_CMAKE_DIR_NAME}"
                    )
                    self.__create_a_dir(self.__cmake_dir)

                # Create file
                self.__create_a_file(file_fp)

                # Create cmake(s)
                self.__create_a_file(f"{base_dir}/CMakelists.txt")
                self.__create_a_file(
                    f"{self.__cmake_dir}/{base_filename}_swc_compile.cmake"
                )
                self.__create_a_file(
                    f"{self.__cmake_dir}/{base_filename}_swc_tests.cmake"
                )

            else:
                self.__create_a_file(file_fp)

        except Exception as e:
            self.__logger.error(f"Error while putting file `{file_fp}`")
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(f"Successfully putted file `{file_fp}`")

    def run(self):
        self.__logger.info("Running output stream")

        self.__full_fp = (
            f"{self.__output_dir}/{self.__file_name}{self.__file_extension}"
        )

        # 1. Create the file
        ## Setup
        ## Run
        self.put_file(self.__full_fp)

        # 2. Add the file headers
        ## Setup

        ## Run
        self.put_file_headers(headers=self.__headers)

        # 3. Add the file sections
        ## Setup
        ## Run
        self.put_file_sections(sections=self.__sections)

        # 4. Add fill values
        ## Setup
        ## Run

        self.__logger.info("Done running output stream")
