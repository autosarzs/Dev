import os
import subprocess
import defaults
from plogger import logy

logger = logy(module_name='formatter')

def format_c_file(directory):
    logger.info("Running formatter {0}".format(defaults.FORMATTER_SCRIPT_PATH))

    logger.info("Collecting output c file @{0}".format(directory))
    try:
        # Get a list of C files in the directory
        c_files = [file for file in os.listdir(directory) if file.endswith('.c')]

        # cmd = f"clang-format -style=llvm -dump-config > {defaults.FORMATTER_SCRIPT_PATH}"
        # subprocess.run(cmd, shell=True)
            
        logger.info("formatting files")
        # Loop through each C file and format it
        for file in c_files:
            logger.info("Formatting [{0}]".format(file))
            file_path = os.path.join(directory, file)
            
            cmd = f"clang-format -style=llvm -i {file_path}"
            subprocess.run(cmd, shell=True)
            logger.info("Done formatting [{0}]".format(file))
            
    except Exception as e:
        logger.error("Error formatting files")
        logger.error(e)
        exit(1)
    logger.info("Done formatting files")
