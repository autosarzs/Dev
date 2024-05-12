from plogger import logy
from fetch_cfg import jscfgparser
from stream import ostra
from utils import xgformatter
import defaults

def run():
    gen_log = logy("generator")

    # Run the yaml fetcher

    gen_log.info("Running the json configuration parser")
    # Run the json fetcher
    js_cfg_parser = jscfgparser()
    js_cfg_parser.run()
    gen_log.info("Done running the json configuration parser")
    
    # Run Ostra
    ## Initiate data for Ostra
    n_temp = js_cfg_parser.get_num_of_templates()

    gen_log.info("Running Ostream for the templates")
    for i in range(0, n_temp):
        base_data = {
            "name": js_cfg_parser.get_template_name(i),
            "source_file": js_cfg_parser.get_template_source_file(i),
            "file_extension": js_cfg_parser.get_template_file_extension(i),
            "description": js_cfg_parser.get_template_description(i),
        }

        ouput_stream = ostra(
            base_data=base_data,
            headers=js_cfg_parser.get_template_file_headers(i),
            sections=js_cfg_parser.get_template_file_sections(i),
            common_include_headers=js_cfg_parser.get_template_common_include_headers(i),
            other_include_headers=js_cfg_parser.get_template_other_include_headers(i),
            component_include_headers=js_cfg_parser.get_template_component_include_headers(
                i
            ),
            macros=js_cfg_parser.get_template_macros(i),
            exported_vars=js_cfg_parser.get_template_exported_vars(i),
            local_vars=js_cfg_parser.get_template_local_vars(i),
            structs=js_cfg_parser.get_template_structs(i),
            enums=js_cfg_parser.get_template_enums(i),
            unions=js_cfg_parser.get_template_unions(i),
            types=js_cfg_parser.get_template_types(i),
            local_functions_declaration=js_cfg_parser.get_template_local_functions_declaration(
                i
            ),
            local_functions_definition=js_cfg_parser.get_template_local_functions_definition(
                i
            ),
            global_functions_definition=js_cfg_parser.get_template_global_functions_definition(
                i
            ),
        )
        ## Run for the provided template
        ouput_stream.run()
        gen_log.info("Done running Ostream for the templates")
        
    # Format the output files
    if defaults.RUN_FORMATTER:
        gen_log.info("Running formatter")
        xgformatter(defaults.OUTPUT_DIR)
        gen_log.info("Done running formatter")
        
        
# TODO(Wx): Optimize the call   
run()