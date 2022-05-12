#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "BIOMPlugin.h"

void BIOMPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string key, value;
   ifile >> key;
   ifile >> value;
   parameters[key] = value;
 }
}

void BIOMPlugin::run() {
   
}

void BIOMPlugin::output(std::string file) { 
   std::string command = "export OLDPATH=${PATH}; ";
   command += "export PATH=${CONDA_HOME}/bin/:${PATH}; ";
   command += "eval \"$(conda shell.bash hook)\"; ";
   command += "conda activate qiime2-2021.4; ";
   command += "biom "+parameters["op"]+" -i "+std::string(PluginManager::prefix())+"/"+parameters["inputfile"]+" ";
   if (parameters.count("observationmetadataFP") != 0)
	   command += "--observation-metadata-fp "+std::string(PluginManager::prefix())+"/"+parameters["observationmetadataFP"]+" ";
   if (parameters.count("scSeparated") != 0)
	   command += "--sc-separated "+parameters["scSeparated"]+" ";
   command += "-o "+file+"; ";

//qiime tools import \
  --type 'SampleData[PairedEndSequencesWithQuality]' \
  --input-path AlphaFinal1.manifest \
  --output-path AlphaFinal1-paired-end-demux.qza \
  --input-format PairedEndFastqManifestPhred33V2
 //std::cout << command << std::endl;
   command += "conda deactivate; ";
   command += "conda deactivate; ";
   command += "export PATH=${OLDPATH}";
 std::cout << command << std::endl;


 system(command.c_str());
}

PluginProxy<BIOMPlugin> BIOMPluginProxy = PluginProxy<BIOMPlugin>("BIOM", PluginManager::getInstance());
