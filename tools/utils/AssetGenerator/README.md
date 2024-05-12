<div align="center">  
<a href="https://ibb.co/y48Nh9g"><img src="https://i.ibb.co/jJL8VN3/logo.png" alt="logo" border="0" /> </a>  

  <a href="https://www.python.org"><img src="https://img.shields.io/badge/Python-FFD43B?style=for-the-badge&logo=python&logoColor=blue" alt="Python"></a>  
</div>  
<div align="center">  

# Autosarzs Asset Generator 2.0  
</div>  

## Brief  
This code is made to generate file templates for C development. The tool is mainly built with python modules.
It is still under development and needs to be more user friendly by adding good user interface to interact with the template configuration json file. 

## Key Features  
* Configurable
* Portable
* Easy to migrate with user interface 
* Easy to add file template
* Easy to use

## Usage
For now this tool is running on python and it has two main files the `main.py` and `generator.py`.  
To run the generator properly:  

- First run `python setup.py install` to install all the dependices.  

- Then you need to adjust the configurations for the project  
    1. First you need to adjust your templates inside `config.json` located in project root directory.  
        <div align="center">  
        <a href="https://imgbb.com/"><img src="https://i.ibb.co/6vcGy3p/config-json-location.png" alt="config-json-location" border="0" /></a>
        </div>  

    2. After cofiguring the templates to generate in the json config file,  
        you need to run the `main.py` by writing the cmd `python3 main.py -h` to see all the options.  
    3. To run the generator you simply  need to write the cmd `python3 main.py -rd` to run the defaults.

    4. To see the output head to the `tools/utils/AssetGenerator/out`

## Configurations  
For now the only configuration is the template json configuration and it is manually.
- How to interact with the `config.json`  
    - First section is the `metadata`. You don't need to modify this as it is needed for the generator to run proberly.
    <div align="center">  

    <a href="https://imgbb.com/"><img src="https://i.ibb.co/qDRv0pm/metadata.png" alt="metadata" border="0" /></a>
    </div>  

    - Second section is the templates defined within this json config, This templates are the processed by file; Each file to be generated requires a template.
        -   The template basic data is the main file data to be processed.
        <div align="center">  
        <a href="https://imgbb.com/"><img src="https://i.ibb.co/qdYFsjH/template-base-data.png" alt="template-base-data" border="0" /></a>
        </div>

        - The file templates is devided into three main sections:  
            1. The headers: It is the introduction to the file itself it containes the main data to be included within the file at its start.
        <div align="center">  
        <a href="https://ibb.co/1ZCSBbS"><img src="https://i.ibb.co/gy0nQ6n/file-header.png" alt="file-header" border="0" /></a>
        </div>
            2. The sections: This is the section organization to include in this file  
        <div align="center">  
        <a href="https://ibb.co/xXw2g9C"><img src="https://i.ibb.co/jbq8w06/file-sections.png" alt="file-sections" border="0" /></a>
        </div> 
            3. The fill values: The startup skeletion for the file such as:  
                1. Common Headers
                2. Component Headers
                3. Other Headers
                4. Local Data
                5. Functions / Services
            and it is generated with its documntation and defaults.  
            ex:
        <div align="center">  
        <a href="https://ibb.co/d208jBn"><img src="https://i.ibb.co/mqCfbJQ/generated-sample.png" alt="generated-sample" border="0" /></a>
        </div> 

## Next Features  

For now the generator is still being developed to be more flexible and easier and the next main thing to develop is integrate a user interface with it to make the template generation and the config json adjustments easier and user friendly. 