import json
import os
import defaults
from plogger import logy
from tabulate import tabulate


class include_headers(object):
    def __init__(
        self,
        name: str = None,
        conditional_include_macro: bool = False,
        description: str = None,
    ):
        assert name is not None

        self.__name = name
        self.__conditional_include_macro = conditional_include_macro
        self.__description = description

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def conditional_include_macro(self):
        return self.__conditional_include_macro

    @conditional_include_macro.setter
    def conditional_include_macro(self, conditional_include_macro):
        self.__conditional_include_macro = conditional_include_macro

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, description):
        self.__description = description


class macros(object):
    def __init__(
        self, name: str = None, conditional_include_macro=False, description=None
    ):
        assert name is not None

        self.__name = name
        self.__conditional_include_macro = conditional_include_macro
        self.__description = description

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def conditional_include_macro(self):
        return self.__conditional_include_macro

    @conditional_include_macro.setter
    def conditional_include_macro(self, conditional_include_macro):
        self.__conditional_include_macro = conditional_include_macro

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, description):
        self.__description = description


class variable(object):
    def __init__(
        self,
        extra_qualifier: str = None,
        memory_qualifier: str = None,
        size_qualifier: str = None,
        datatype: str = None,
        name: str = None,
        bit_field: int = None,
        compiler: str = None,
        description: str = None,
    ):
        assert datatype is not None
        assert name is not None

        self.__extra_qualifier = extra_qualifier
        self.__memory_qualifier = memory_qualifier
        self.__size_qualifier = size_qualifier
        self.__datatype = datatype
        self.__name = name
        self.__description = description

        self.__bit_field = bit_field
        self.__compiler = compiler

    @property
    def extra_qualifier(self):
        return self.__extra_qualifier

    @extra_qualifier.setter
    def extra_qualifier(self, extra_qualifier):
        self.__extra_qualifier = extra_qualifier

    @property
    def memory_qualifier(self):
        return self.__memory_qualifier

    @memory_qualifier.setter
    def memory_qualifier(self, memory_qualifier):
        self.__memory_qualifier = memory_qualifier

    @property
    def size_qualifier(self):
        return self.__size_qualifier

    @size_qualifier.setter
    def size_qualifier(self, size_qualifier):
        self.__size_qualifier = size_qualifier

    @property
    def bit_field(self):
        return self.__bit_field

    @bit_field.setter
    def bit_field(self, bit_field):
        self.__bit_field = bit_field

    @property
    def attributes(self):
        return self.__compiler

    @attributes.setter
    def attributes(self, compiler):
        self.__compiler = compiler

    @property
    def datatype(self):
        return self.__datatype

    @datatype.setter
    def datatype(self, datatype):
        self.__datatype = datatype

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, description):
        self.__description = description


class structs(object):
    def __init__(
        self,
        name: str = None,
        conditional_include_macro: bool = False,
        compiler: str = None,
        list_of_members: list = None,
        description: str = None,
    ):
        assert name is not None

        self.__name = name
        self.__conditional_include_macro = conditional_include_macro
        self.__description = description

        self.__attributes = compiler

        self.__list_of_members = list_of_members
        self.__num_of_members = len(list_of_members)

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def conditional_include_macro(self):
        return self.__conditional_include_macro

    @conditional_include_macro.setter
    def conditional_include_macro(self, conditional_include_macro):
        self.__conditional_include_macro = conditional_include_macro

    @property
    def list_of_members(self):
        return self.__list_of_members

    @list_of_members.setter
    def list_of_members(self, list_of_members):
        self.__list_of_members = list_of_members

    @property
    def compiler(self):
        return self.__attributes

    @compiler.setter
    def compiler(self):
        return self.__attributes

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, description):
        self.__description = description


class functions(object):
    def __init__(
        self,
        return_type: str = None,
        name: str = None,
        list_of_args: list = None,
        compiler: str = None,
        data: dict = None,
    ):
        assert name is not None
        assert data is not None

        self.__return_type = return_type
        self.__name = name
        self.__data = data
        self.__list_of_args = list_of_args
        self.__attributes = compiler

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def return_type(self):
        return self.__return_type

    @return_type.setter
    def return_type(self, return_type):
        self.__return_type = return_type

    @property
    def data(self):
        return self.__data

    @data.setter
    def data(self, data):
        self.__data = data

    @property
    def compiler(self):
        return self.__attributes

    @compiler.setter
    def compiler(self, compiler):
        self.__attributes = compiler

    @property
    def list_of_args(self):
        return self.__list_of_args

    @list_of_args.setter
    def list_of_args(self, list_of_args):
        self.__list_of_args = list_of_args


class unions(object):
    def __init__(
        self,
        name: str = None,
        description=None,
        compiler: str = None,
        list_of_members: list = None,
    ):
        assert name is not None

        self.__name = name
        self.__attributes = compiler
        self.__list_of_members = list_of_members
        self.__description = description

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def compiler(self):
        return self.__attributes

    @compiler.setter
    def compiler(self, compiler):
        self.__attributes = compiler

    @property
    def list_of_members(self):
        return self.__list_of_members

    @list_of_members.setter
    def list_of_members(self, list_of_members):
        self.__list_of_members = list_of_members

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, description):
        self.__description = description


class enums(object):
    def __init__(
        self, name: str = None, dict_of_members: dict = None, description=None,
    ):
        self.__name = name
        self.__dict_of_members = dict_of_members
        self.__description = description

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, name):
        self.__name = name

    @property
    def dict_of_members(self):
        return self.__dict_of_members

    @dict_of_members.setter
    def dict_of_members(self, dict_of_members):
        self.__dict_of_members = dict_of_members

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, description):
        self.__description = description


class typedef(object):
    def __init__(
        self,
        base_name: str = None,
        new_name: str = None,
        type: str = None,
        compiler: str = None,
        description: str = None,
    ):
        assert base_name is not None
        assert new_name is not None

        self.__base_name = base_name
        self.__new_name = new_name
        self.__type = type
        self.__compiler = compiler
        self.__description = description

    @property
    def base_name(self):
        return self.__base_name

    @base_name.setter
    def base_name(self, base_name):
        self.__base_name = base_name

    @property
    def new_name(self):
        return self.__new_name

    @new_name.setter
    def new_name(self, new_name):
        self.__new_name = new_name

    @property
    def type(self):
        return self.__type

    @type.setter
    def type(self, type):
        self.__type = type

    @property
    def compiler(self):
        return self.__compiler

    @compiler.setter
    def compiler(self, compiler):
        self.__compiler = compiler

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, description):
        self.__description = description


class parse_cfg_json:
    pre_defined_generators = [
        "mowx_xftg_wx10" "mowx_xftg_wx11",
        "mowx_xftg_wx12",
        "mowx_xftg_wx13",
    ]

    available_template_names = ["C Source File", "C Header File"]

    available_template_file_extensions = [".c", ".h", ".cpp", ".hpp"]

    def __init__(self):
        self.__logger = logy(module_name="parse_cfg_json")

        self.__cfg_fp = os.path.join(defaults.JSON_CFG_DIR, defaults.JSON_CFG_NAME)

        self.__number_of_templates_provided = 0
        self.__number_of_c_templates = 0
        self.__number_of_h_templates = 0
        self.__number_of_common_headers = 0
        self.__number_of_other_headers = 0
        self.__number_of_component_headers = 0
        self.__number_of_enums = 0
        self.__number_of_structs = 0
        self.__number_of_unions = 0
        self.__number_of_macros = 0
        self.__number_of_exported_variables = 0
        self.__number_of_local_variables = 0
        self.__number_of_functions = 0
        self.__number_of_services = 0
        #
        self.__metadata = {}
        self.__templates = []

    def __read_json_file(self):
        self.__logger.info(f"Parsing the json configuration file @{self.__cfg_fp}")
        try:
            with open(self.__cfg_fp, "r") as file:
                file_data = file.read()
            self.__json_file_data = json.loads(file_data)

            self.__logger.debug(self.__json_file_data)

        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file @{self.__cfg_fp}"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            f"Successfully parsed the json configuration file @{self.__cfg_fp}"
        )

    def __validate_template_format(self, n_templates: int = 0):
        self.__logger.info(f"Validating the json configuration file template format")
        self.__name = []
        self.__source_file = []
        self.__file_extension = []
        self.__description = []
        self.__file_header = []
        self.__file_sections = []
        self.__file_fill_values = []

        for i in range(0, n_templates):
            self.__name.append(self.__templates[i].get("name", "null"))
            self.__logger.debug(f"[*] name[template:{i}]: {self.__name}")

            self.__description.append(self.__templates[i].get("description", "null"))
            self.__logger.debug(f"[*] description[template:{i}]: {self.__description}")

            self.__file_extension.append(
                self.__templates[i].get("file_extension", "null")
            )
            self.__logger.debug(
                f"[*] file_extension[template:{i}]: {self.__file_extension}"
            )

            self.__source_file.append(self.__templates[i].get("source_file", "null"))
            self.__logger.debug(f"[*] source_file[template:{i}]: {self.__source_file}")

            self.__file_header.append(self.__templates[i].get("file_header", "null"))
            self.__logger.debug(f"[*] file_header[template:{i}]: {self.__file_header}")

            self.__file_sections.append(
                self.__templates[i].get("file_sections", "null")
            )
            self.__logger.debug(
                f"[*] file_sections[template:{i}]: {self.__file_sections}"
            )

            self.__file_fill_values.append(
                self.__templates[i].get("file_fill_values", "null")
            )
            self.__logger.debug(
                f"[*] file_fill_values[template:{i}]: {self.__file_fill_values}"
            )

            if any(
                value == "null"
                for value in [
                    self.__name,
                    self.__description,
                    self.__file_extension,
                    self.__source_file,
                    self.__file_header,
                    self.__file_sections,
                    self.__file_fill_values,
                ]
            ):
                self.__logger.error(
                    f"Invalid template format. Please check for missing attributes/fields"
                )
                exit(1)

    def __parse_metadata(self):
        self.__logger.info(f"Parsing the json configuration file metadata")
        try:
            self.__metadata = self.__json_file_data.get("metadata", "null")

            if "null" == self.__metadata:
                self.__logger.error(
                    "Error while parsing invalid json configuration file metadata"
                )
                exit(1)
            else:
                self.__logger.info(f"Checking the generator name")
                generator_name = self.__metadata.get("generator_name", "null")
                if generator_name not in parse_cfg_json.pre_defined_generators:
                    self.__logger.error(
                        f"Error while parsing metadata invalid generator name {generator_name}"
                    )
                    exit(1)

                self.__logger.info(f"Valid generator name found")

        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file metadata"
            )
            self.__logger.error(f"Error: {e}")

        self.__logger.debug(self.__metadata)
        self.__logger.info(f"Successfully parsed the json configuration file metadata")

    def __parse_template_file_header(self, template_num: int = None):
        self.__logger.info(f"Parsing the json configuration file template file header")

        dict_of_provided_fields = {}
        try:
            num_of_file_headers = len(self.__file_header[template_num])
            self.__logger.debug(
                f"Number of headers in file header {template_num}: {num_of_file_headers}"
            )

            self.__logger.debug(f"Parsing file header {template_num}:")
            self.__logger.debug(self.__file_header[template_num])

            for i in range(num_of_file_headers):
                header_fields = self.__file_header[template_num][i]
                dict_of_provided_fields.update(
                    {header_fields["name"]: header_fields["value"]}
                )

            self.__logger.debug(f"Collected fields: {dict_of_provided_fields}")
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template file header"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info("Successfully parsed the template file headers")
        return dict_of_provided_fields

    def __parse_template_file_section(self, template_num: int = None):
        self.__logger.info(f"Parsing the json configuration file template file section")

        dict_of_provided_fields = {}
        try:
            num_of_file_sections = len(self.__file_sections[template_num])
            self.__logger.debug(
                f"Number of sections in file sections {template_num}: {num_of_file_sections}"
            )

            self.__logger.debug(f"Parsing file section {template_num}:")
            self.__logger.debug(self.__file_sections[template_num])

            for i in range(num_of_file_sections):
                header_fields = self.__file_sections[template_num][i]
                dict_of_provided_fields.update(
                    {header_fields["name"]: header_fields["value"]}
                )

            self.__logger.debug(f"Collected fields: {dict_of_provided_fields}")
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template file section"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info("Successfully parsed the template file sections")
        return dict_of_provided_fields

    def __parse_included_headers(self, headers: any = None):
        fetched_headers = []

        for header in headers:
            new_header = include_headers(
                name=header["name"],
                conditional_include_macro=header.get("conditional_include_macro", None),
                description=header["description"],
            )

            fetched_headers.append(new_header)
            self.__logger.debug(
                f"Fetched Header: {new_header.name}, "
                f"Conditional Include Macro: {new_header.conditional_include_macro}, "
                f"Description: {new_header.description}"
            )
        return fetched_headers

    def __parse_template_fill_values_include_common_headers(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None

        self.__logger.info(
            f"Parsing the json configuration file template fill values (include_common_headers)"
        )

        try:
            full_headers_data = file_fill_values["include_common_headers"]
            fetched_headers = self.__parse_included_headers(full_headers_data)
            self.__number_of_common_headers = len(full_headers_data)

        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (include_common_headers)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (include_common_headers)"
        )
        return fetched_headers

    def __parse_template_fill_values_include_other_headers(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (include_other_headers)"
        )

        try:
            full_headers_data = file_fill_values["include_other_headers"]
            fetched_headers = self.__parse_included_headers(full_headers_data)
            self.__number_of_other_headers = len(full_headers_data)

        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (include_other_headers)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (include_other_headers)"
        )
        return fetched_headers

    def __parse_template_fill_values_include_component_headers(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (component_headers)"
        )

        try:
            full_headers_data = file_fill_values["include_component_headers"]
            fetched_headers = self.__parse_included_headers(full_headers_data)
            self.__number_of_component_headers = len(full_headers_data)

        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (component_headers)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (component_headers)"
        )
        return fetched_headers

    def __parse_template_fill_values_local_macros_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (macros definition)"
        )

        try:
            full_macros_data = file_fill_values.get("local_macros_definition", [])
            fetched_macros = []
            self.__number_of_macros = len(full_macros_data)
            for macro_data in full_macros_data:
                new_macro = macros(
                    name=macro_data["name"],
                    conditional_include_macro=macro_data.get(
                        "conditional_include_macro", None
                    ),
                    description=macro_data["description"],
                )

                fetched_macros.append(new_macro)
                self.__logger.debug(
                    f"Macro: {new_macro.name}, "
                    f"Conditional Include Macro: {new_macro.conditional_include_macro}, "
                    f"Description: {new_macro.description}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (macros definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (macros definition)"
        )
        return fetched_macros

    def __parse_template_fill_values_local_structs_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (structs_definition)"
        )

        try:
            full_structs_data = file_fill_values.get("local_structs_definition", [])
            fetched_structs = []
            self.__number_of_structs = len(full_structs_data)

            for struct_data in full_structs_data:
                list_of_variables = []
                members_data = struct_data.get("members", [])

                for member_data in members_data:
                    list_of_variables.append(
                        variable(
                            name=member_data["name"],
                            datatype=member_data["type"],
                            bit_field=member_data.get("bit_field", None),
                        )
                    )

                new_struct = structs(
                    name=struct_data["name"],
                    conditional_include_macro=struct_data.get(
                        "conditional_include_macro", None
                    ),
                    compiler=struct_data.get("compiler", None),
                    list_of_members=list_of_variables,
                    description=struct_data.get("description", None),
                )

                fetched_structs.append(new_struct)
                self.__logger.debug(
                    f"Struct: {new_struct.name}, "
                    f"Conditional Include Macro: {new_struct.conditional_include_macro}, "
                    f"Compiler: {new_struct.compiler}, "
                    f"Members: {[(arg.name, arg.datatype) for arg in new_struct.list_of_members]}, "
                    f"Description: {new_struct.description}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (structs_definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (structs_definition)"
        )
        return fetched_structs

    def __parse_template_fill_values_local_enums_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (enums_definition)"
        )

        try:
            full_enums_data = file_fill_values.get("local_enums_definition", [])
            fetched_enums = []
            self.__number_of_enums = len(full_enums_data)

            for enum_data in full_enums_data:
                new_enum = enums(
                    name=enum_data["name"],
                    dict_of_members=enum_data["members"],
                    description=enum_data["description"],
                )

                fetched_enums.append(new_enum)

                self.__logger.debug(
                    f"Enum: {new_enum.name}, "
                    f"Members: {new_enum.dict_of_members}, "
                    f"Description: {new_enum.description}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (enums_definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (enums_definition)"
        )
        return fetched_enums

    def __parse_template_fill_values_local_unions_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None

        self.__logger.info(
            f"Parsing the json configuration file template fill values (unions_definition)"
        )

        try:
            full_unions_data = file_fill_values.get("local_unions_definition", [])
            fetched_unions = []
            self.__number_of_unions = len(full_unions_data)

            for union_data in full_unions_data:
                list_of_variables = []
                members_data = union_data.get("members", [])

                for member_data in members_data:
                    list_of_variables.append(
                        variable(
                            name=member_data["name"],
                            datatype=member_data["type"],
                            bit_field=member_data.get("bit_field", None),
                        )
                    )

                new_union = unions(
                    name=union_data["name"],
                    compiler=union_data.get("compiler", None),
                    list_of_members=list_of_variables,
                    description=union_data.get("description", None),
                )

                fetched_unions.append(new_union)
                self.__logger.debug(
                    f"Union: {new_union.name}, "
                    f"Compiler: {new_union.compiler}, "
                    f"Members: {[(arg.name, arg.datatype) for arg in new_union.list_of_members]}, "
                    f"Description: {new_union.description}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (unions_definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (unions_definition)"
        )
        return fetched_unions

    def __parse_template_fill_values_local_types_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (local_types_definition)"
        )

        try:
            full_types_data = file_fill_values.get("local_types_definition", [])
            fetched_types = []
            self.__number_of_types = len(full_types_data)

            for type_data in full_types_data:
                new_type = typedef(
                    base_name=type_data["base_name"],
                    new_name=type_data["new_name"],
                    type=type_data["type"],
                    description=type_data["description"],
                )

                fetched_types.append(new_type)
                self.__logger.debug(
                    f"Type: {new_type.base_name}, "
                    f"New Name: {new_type.new_name}, "
                    f"Type: {new_type.type}, "
                    f"Description: {new_type.description}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (local_types_definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (local_types_definition)"
        )
        return fetched_types

    def __parse_template_fill_values_exported_variables_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (exported_variables_definition)"
        )

        try:
            full_exports_data = file_fill_values.get(
                "exported_variables_definition", []
            )
            fetched_exports = []
            self.__number_of_exported_variables = len(full_exports_data)

            for export_data in full_exports_data:
                new_export = variable(
                    name=export_data["name"],
                    datatype=export_data["type"],
                    description=export_data["description"],
                )

                fetched_exports.append(new_export)
                self.__logger.debug(
                    f"Exported Variable: {new_export.name}, "
                    f"Type: {new_export.datatype}, "
                    f"Description: {new_export.description}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (exported_variables_definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (exported_variables_definition)"
        )
        return fetched_exports

    def __parse_template_fill_values_local_variables_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (local_variables_definition)"
        )

        try:
            full_vars_data = file_fill_values.get("local_variables_definition", [])
            fetched_vars = []
            self.__number_of_local_variables = len(full_vars_data)

            for var_data in full_vars_data:
                new_var = variable(
                    name=var_data["name"],
                    datatype=var_data["type"],
                    compiler=var_data["compiler"],
                    description=var_data["description"],
                )

                fetched_vars.append(new_var)
                self.__logger.debug(
                    f"Variable: {new_var.name}, "
                    f"Type: {new_var.datatype}, "
                    f"Attributes: {new_var.attributes}, "
                    f"Description: {new_var.description}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (local_variables_definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (local_variables_definition)"
        )
        return fetched_vars

    def __parse_template_fill_values_local_functions_declaration(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (local functions declaration)"
        )
        try:
            full_functions_data = file_fill_values["local_functions_declaration"]
            fetched_functions = []

            self.__number_of_functions = len(full_functions_data)

            for function_data in full_functions_data:
                list_of_args = []
                arguments = function_data.get("arguments", [])

                for arg in arguments:
                    new_arg = variable(
                        name=arg["name"],
                        datatype=arg["type"],
                        description=arg["description"],
                    )
                    list_of_args.append(new_arg)

                data = {
                    "local_global": function_data.get("local_global", None),
                    "service_flag": function_data.get("service_flag", None),
                    "description": function_data.get("description", None),
                    "requirement": function_data.get("requirement", None),
                    "notes": function_data.get("notes", None),
                }
                if data.get("service_flag") == "true":
                    data.update(
                        {
                            "service_name": function_data.get("service_name", None),
                            "service_id": function_data.get("service_id", None),
                            "sync_async": function_data.get("sync_async", None),
                            "reentrancy": function_data.get("reentrancy", None),
                        }
                    )
                    self.__number_of_services += 1

                new_function = functions(
                    return_type=function_data.get("return_type", None),
                    name=function_data.get("name", None),
                    list_of_args=list_of_args,
                    data=data,
                    compiler=function_data.get("compiler", None),
                )

                fetched_functions.append(new_function)

                self.__logger.debug(
                    f"Function: {new_function.name}, "
                    f"Return Type: {new_function.return_type}, "
                    f"Arguments: {[(arg.name, arg.datatype) for arg in new_function.list_of_args]}, "
                    f"Data: {new_function.data}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (functions)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (functions)"
        )
        return fetched_functions

    def __parse_template_fill_values_local_functions_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (local functions definition)"
        )
        try:
            full_functions_data = file_fill_values["local_functions_definition"]
            fetched_functions = []

            self.__number_of_functions = len(full_functions_data)

            for function_data in full_functions_data:
                list_of_args = []
                arguments = function_data.get("arguments", [])

                for arg in arguments:
                    new_arg = variable(name=arg["name"], datatype=arg["type"])
                    list_of_args.append(new_arg)

                data = {
                    "local_global": function_data.get("local_global", None),
                    "service_flag": function_data.get("service_flag", None),
                    "description": function_data.get("description", None),
                    "requirement": function_data.get("requirement", None),
                    "notes": function_data.get("notes", None),
                }
                if data.get("service_flag") == "true":
                    data.update(
                        {
                            "service_name": function_data.get("service_name", None),
                            "service_id": function_data.get("service_id", None),
                            "sync_async": function_data.get("sync_async", None),
                            "reentrancy": function_data.get("reentrancy", None),
                        }
                    )
                    self.__number_of_services += 1

                new_function = functions(
                    return_type=function_data.get("return_type", None),
                    name=function_data.get("name", None),
                    list_of_args=list_of_args,
                    data=data,
                )

                fetched_functions.append(new_function)

                self.__logger.debug(
                    f"Function: {new_function.name}, "
                    f"Return Type: {new_function.return_type}, "
                    f"Arguments: {[(arg.name, arg.datatype) for arg in new_function.list_of_args]}, "
                    f"Data: {new_function.data}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (local functions definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (local functions definition)"
        )
        return fetched_functions

    def __parse_template_fill_values_global_functions_definition(
        self, file_fill_values: dict = None
    ):
        assert file_fill_values is not None
        self.__logger.info(
            f"Parsing the json configuration file template fill values (global functions definition)"
        )
        try:
            full_functions_data = file_fill_values["global_functions_definition"]
            fetched_functions = []

            self.__number_of_functions = len(full_functions_data)

            for function_data in full_functions_data:
                list_of_args = []
                arguments = function_data.get("arguments", [])

                for arg in arguments:
                    new_arg = variable(name=arg["name"], datatype=arg["type"])
                    list_of_args.append(new_arg)

                data = {
                    "local_global": function_data.get("local_global", None),
                    "service_flag": function_data.get("service_flag", None),
                    "description": function_data.get("description", None),
                    "requirement": function_data.get("requirement", None),
                    "notes": function_data.get("notes", None),
                }
                if data.get("service_flag") == "true":
                    data.update(
                        {
                            "service_name": function_data.get("service_name", None),
                            "service_id": function_data.get("service_id", None),
                            "sync_async": function_data.get("sync_async", None),
                            "reentrancy": function_data.get("reentrancy", None),
                        }
                    )
                    self.__number_of_services += 1

                new_function = functions(
                    return_type=function_data.get("return_type", None),
                    name=function_data.get("name", None),
                    list_of_args=list_of_args,
                    data=data,
                )

                fetched_functions.append(new_function)

                self.__logger.debug(
                    f"Function: {new_function.name}, "
                    f"Return Type: {new_function.return_type}, "
                    f"Arguments: {[(arg.name, arg.datatype) for arg in new_function.list_of_args]}, "
                    f"Data: {new_function.data}"
                )
        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values (global functions definition)"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info(
            "Successfully parsed the template file fill values (global functions definition)"
        )
        return fetched_functions

    def __parse_file_fill_values(self, template_num: int = None):
        self.__logger.info(f"Parsing the json configuration file template fill values")

        self.__include_common_headers = []
        self.__include_other_headers = []
        self.__include_component_headers = []
        self.__local_macros_definition = []
        self.__local_structs_definition = []
        self.__local_enums_definition = []
        self.__local_unions_definition = []
        self.__local_types_definition = []
        self.__exported_variables_definition = []
        self.__local_variables_definition = []
        self.__local_functions_declaration = []
        self.__local_functions_definition = []
        self.__global_functions_definition = []

        try:
            self.__include_common_headers.append(
                self.__parse_template_fill_values_include_common_headers(
                    self.__file_fill_values[template_num]
                )
            )
            self.__include_other_headers.append(
                self.__parse_template_fill_values_include_other_headers(
                    self.__file_fill_values[template_num]
                )
            )

            self.__include_component_headers.append(
                self.__parse_template_fill_values_include_component_headers(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_macros_definition.append(
                self.__parse_template_fill_values_local_macros_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_structs_definition.append(
                self.__parse_template_fill_values_local_structs_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_enums_definition.append(
                self.__parse_template_fill_values_local_enums_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_unions_definition.append(
                self.__parse_template_fill_values_local_unions_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_types_definition.append(
                self.__parse_template_fill_values_local_types_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__exported_variables_definition.append(
                self.__parse_template_fill_values_exported_variables_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_variables_definition.append(
                self.__parse_template_fill_values_local_variables_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_functions_declaration.append(
                self.__parse_template_fill_values_local_functions_declaration(
                    self.__file_fill_values[template_num]
                )
            )

            self.__local_functions_definition.append(
                self.__parse_template_fill_values_local_functions_definition(
                    self.__file_fill_values[template_num]
                )
            )

            self.__global_functions_definition.append(
                self.__parse_template_fill_values_global_functions_definition(
                    self.__file_fill_values[template_num]
                )
            )

        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file template fill values"
            )
            self.__logger.error(f"Error: {e}")
            exit(1)

        self.__logger.info("Successfully parsed the template fill values")

    def __parse_templates(self):
        self.__logger.info(f"Parsing the json configuration file templates")
        try:
            self.__templates = self.__json_file_data.get("templates", "null")

            if "null" == self.__templates:
                self.__logger.error(
                    "Error while parsing invalid json configuration file templates"
                )
                exit(1)
            else:
                self.__logger.debug(self.__templates)

                self.__number_of_templates_provided = len(self.__templates)
                self.__logger.debug(
                    f"Number of templates provided: {self.__number_of_templates_provided}"
                )

                self.__logger.info(f"Checking the template format")
                self.__validate_template_format(self.__number_of_templates_provided)
                self.__logger.info(f"Valid template format")

                #
                self.__xfile_headers = []
                self.__xfile_sections = []
                self.__xfile_fillvalues = []
                for i in range(0, self.__number_of_templates_provided):
                    self.__xfile_headers.append(self.__parse_template_file_header(i))
                    self.__xfile_sections.append(self.__parse_template_file_section(i))
                    self.__xfile_fillvalues.append(self.__parse_file_fill_values(i))

        except Exception as e:
            self.__logger.error(
                f"Error while reading the json configuration file tempolates"
            )
            self.__logger.error(f"Error: {e}")

    def __analyzer(self):
        self.__logger.info("Running analyzer...")

        for name in self.__name:
            if name == "C Source File":
                self.__number_of_c_templates += 1
            else:
                self.__number_of_h_templates += 1

        attributes_data = [
            ["Number of Templates Provided", self.__number_of_templates_provided],
            ["Number of C Templates", self.__number_of_c_templates],
            ["Number of H Templates", self.__number_of_h_templates],
            ["Number of Common Headers", self.__number_of_common_headers],
            ["Number of Other Headers", self.__number_of_other_headers],
            ["Number of Component Headers", self.__number_of_component_headers],
            ["Number of Enums", self.__number_of_enums],
            ["Number of Structs", self.__number_of_structs],
            ["Number of Unions", self.__number_of_unions],
            ["Number of Macros", self.__number_of_macros],
            ["Number of Exported Variables", self.__number_of_exported_variables],
            ["Number of Local Variables", self.__number_of_local_variables],
            ["Number of Functions", self.__number_of_functions],
            ["Number of Services", self.__number_of_services],
        ]

        self.__logger.info(
            "\n"
            + tabulate(attributes_data, headers=["Attribute", "Value"], tablefmt="grid")
        )

    """
        Public Functions (APIs)
    """

    def get_metadata(self, template_n: int = None):
        return self.__metadata

    def get_template_name(self, template_n: int = None):
        return self.__name[template_n]

    def get_template_source_file(self, template_n: int = None):
        return self.__source_file[template_n]

    def get_template_file_extension(self, template_n: int = None):
        return self.__file_extension[template_n]

    def get_template_description(self, template_n: int = None):
        return self.__description[template_n]

    def get_template_file_headers(self, template_n: int = None):
        return self.__xfile_headers[template_n]

    def get_template_file_sections(self, template_n: int = None):
        return self.__xfile_sections[template_n]

    def get_template_local_functions_declaration(self, template_n: int = None):
        return self.__local_functions_declaration[template_n]

    def get_template_local_functions_definition(self, template_n: int = None):
        return self.__local_functions_declaration[template_n]

    def get_template_global_functions_definition(self, template_n: int = None):
        return self.__global_functions_definition[template_n]

    def get_template_common_include_headers(self, template_n: int = None):
        return self.__include_common_headers[template_n]

    def get_template_other_include_headers(self, template_n: int = None):
        return self.__include_other_headers[template_n]

    def get_template_component_include_headers(self, template_n: int = None):
        return self.__include_component_headers[template_n]

    def get_template_macros(self, template_n: int = None):
        return self.__local_macros_definition[template_n]

    def get_template_exported_vars(self, template_n: int = None):
        return self.__exported_variables_definition[template_n]

    def get_template_local_vars(self, template_n: int = None):
        return self.__local_variables_definition[template_n]

    def get_template_structs(self, template_n: int = None):
        return self.__local_structs_definition[template_n]

    def get_template_enums(self, template_n: int = None):
        return self.__local_enums_definition[template_n]

    def get_template_unions(self, template_n: int = None):
        return self.__local_unions_definition[template_n]

    def get_template_types(self, template_n: int = None):
        return self.__local_types_definition[template_n]

    def get_num_of_templates(self):
        return self.__number_of_templates_provided

    def run(self):
        self.__logger.info("Running json configuration fetcher...")
        self.__read_json_file()
        self.__parse_metadata()
        self.__parse_templates()
        self.__analyzer()
        self.__logger.info("Done running json configuration fetcher")
