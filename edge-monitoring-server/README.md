# VentQ
Ventilation quality monitoring system

The monitoring server is based in a docker image for deploying MySQL as NodeMCU database (together with the DB), PHP for REST API deployment and RStudio for spatial statistics computation in the Cloud.

In order to deploy this server, we use docker-compose (command: docker-compose up -d) in the same folder as the docker image (zip file) for the deployment of all the folder structure and applications.
