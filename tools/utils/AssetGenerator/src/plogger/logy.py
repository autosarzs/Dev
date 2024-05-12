import logging.config
import logging.handlers
import defaults
import os
import json

# import pathlib

# def setup_logging():
#     config_file = pathlib.Path(
#         "G:\WX_CAREER\COTS\AssetGenerator\src\plogger\config.json"
#     )
#     with open(config_file) as f_in:
#         config = json.load(f_in)

#     logging.config.dictConfig(config)


# TODO(Wx): Integrate with online logging service
# TODO(Wx): Integrate json config
class logy(object):
    """
    Creates a logger handle for the current module.
    
    Args:
        module_name (str): Name of the module.
    """

    def __init__(self, module_name: str = None):
        # Create logger
        if module_name is None:
            self.__logger_name = "default"
        else:
            self.__logger_name = module_name

        # setup_logging()

        self.__logger = logging.getLogger(self.__logger_name)

        self.__logger.setLevel(logging.DEBUG)

        # Create formatter
        fmt = logging.Formatter(
            "[%(levelname)s|%(module)s|L%(lineno)d] %(asctime)s: %(calling_module)s: %(message)s",
            "%Y-%m-%dT%H:%M:%S%z",
        )

        console_handler = logging.StreamHandler()
        console_handler.setFormatter(fmt)

        self.__logger.addHandler(console_handler)

        log_file = os.path.join(
            defaults.PROJECT_LOGGING_DIR, f"{self.__logger_name}.log"
        )
        file_handler = logging.FileHandler(log_file)

        file_handler.setFormatter(fmt)
        self.__logger.addHandler(file_handler)

    def debug(self, msg):
        self.__logger.debug(msg, extra={"calling_module": f"{self.__logger_name}"})

    def info(self, msg):
        self.__logger.info(msg, extra={"calling_module": f"{self.__logger_name}"})

    def warning(self, msg):
        self.__logger.warning(msg, extra={"calling_module": f"{self.__logger_name}"})

    def error(self, msg):
        self.__logger.error(msg, extra={"calling_module": f"{self.__logger_name}"})

    def critical(self, msg):
        self.__logger.critical(msg, extra={"calling_module": f"{self.__logger_name}"})
