# VentQ
This is an Open-source and Open-hardware ventilation quality monitoring system

This IoT-based system is oriented for CO2 and Temp/Hum monitoring. 

The structure of this project is summarized in 3 folders:
- The sensing hardware is described in "open-hardware-node" folder. It also provides the software to configure the sensing nodes.
- The collecting information system is based on a REST API that stores the indoor environmental information into a MySQL database. This system is dockerized and the image has been uploaded to this github in "edge-monitoring-server" folder. 
- The processing of the information is made in the Cloud and is based on a RStudio script querying the database, in specific periods, and applying spatial statistics (kriging) for the mean values of the data collected in each period. This script is collected in "cloud-krigging-spatial-processing" folder.
- The calibration of the nodes is done by means of an APP built with MIT App Inventor 2 (http://appinventor.mit.edu/). This App allows to calibrate to zero, to enable/disable autocalibration mode and obtain information from the node.

