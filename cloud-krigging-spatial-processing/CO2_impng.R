#install.packages("Hmisc")
library("Hmisc")
library(sp)
library(ggplot2)
library(maptools)
library(lattice)
library(spatial)
library(geoR)
library(gstat)
library(scatterplot3d)
library(RColorBrewer)
#if(!requireNamespace("devtools")) install.packages("devtools")
# devtools::install_github("fresques/ggmap")
# devtools::install_github("dkahle/ggmap", ref = "tidyup")
# if(!require(devtools)) install.packages("devtools")
# devtools::install_github("kassambara/ggpubr")
# if(!require(devtools)) install.packages("devtools")
# devtools::install_github("tidyverse/tibble") 
library(ggmap)
library(imager)
library(magick)
library(dplyr)
library(ggpubr)
#####
setwd("D:/papers/mdpi/electronics/co2/")

fpath <- system.file("extdata/mes41nodes.png", package="imager")
pla <- load.image("mes41node.png")
pla1 <- image_read("mes41node.png")

df <- as.data.frame(pla)
plot(pla)

image_scale(pla1,"600")
df <- pla %>% as.data.frame

# Read data file (dataframe)
dataset1 = read.csv('evolCO2.csv',header = T, sep = ';')

#summary(dataset1)

dat<-dataset1

dat <- na.omit(dat) 


x<-rbind(650, 650, 570, 450, 450, 300, 190, 190)
y<-rbind(900, 220, 500, 900, 220, 550, 850, 190)
#x1<-rbind(650, 650, 570, 450, 450, 250, 190, 190)
#y1<-rbind(190, 850, 600, 190, 850, 500, 220, 900)
co2<-rbind(438.81, 489.69, 472.26, 473.18, 520.71, 439.27, 492.24, 533.14)


dat <- as.data.frame(cbind(x,y,co2))
colnames(dat) <- c('x', 'y', 'co2')
coordinates(dat) <- ~x+y


# Spatial statistics & Kriging
x.range <- as.double(range(dat@coords[,1]))
y.range <- as.double(range(dat@coords[,2]))

# Define the grid (and its resolution) and predict variogram alues in the grid
grd <- expand.grid(x=seq(from=x.range[1], to=x.range[2], by=10), y=seq(from=y.range[1], to=y.range[2], by=10))
coordinates(grd) <- ~ x+y 
gridded(grd) <- TRUE
# Compute variogram and establish relationship (linear: ldbn~1)
g0 <- gstat(id="co2", formula= co2 ~ 1, data=dat)
v0<-variogram(g0, width=1, cutoff=1000)
v0.fit <- fit.variogram(v0, model=vgm(1, "Mat", 100, 3000),fit.kappa = TRUE)
plot(v0,v0.fit)
p0 <- predict(g0, model=v0.fit, newdata=grd)


# Representation linear kriging 
W0<-as.data.frame(cbind(p0@coords[,1], p0@coords[,2], p0@data$co2.pred))
colnames(W0)<-c('lon','lat','co2')
coordinates(W0) <- ~ lon+lat

#install.packages("patchwork")       # Install patchwork package
library("patchwork")     

fig <- image_graph(res = 96)
ggplot() + geom_tile(data = as.data.frame(W0), aes(x = W0@coords[,1], y = W0@coords[,2], fill = W0@data$co2), alpha=0.6) + scale_fill_gradient(low = "green", high = "red") + geom_point(aes(x = dat@coords[,1], y = dat@coords[,2]), data = as.data.frame(coordinates(dat)), alpha = .6, color="black", size = 1)

#IDW
z<-predict(g0,grd)
par(mar=c(2,2,2,2))
points(dat@coords, pch=4, cex=0.5)
pts <- list("sp.points", dat, pch = 4, col = "black", cex=0.5)
spplot(z["co2.pred"],col.regions=terrain.colors(140), cuts=140, sp.layout=list(pts), contour=FALSE, labels=FALSE, pretty=TRUE, col='brown', main='IDW')

##########

library(spatstat)  # Used for the dirichlet tessellation function
library(maptools)  # Used for conversion from SPDF to ppp
library(raster)    # Used to clip out thiessen polygons
# For automatic Krige fitting 
library(sp)
library(gstat)
library(automap)
# In case the projection of the grid grd is not the same as the one of the dataset dat
grd@proj4string@projargs=dat@proj4string@projargs

Var <- variogram(dat$co2 ~ 1, dat, width=1, cutoff=1000)
Krig <- autoKrige(dat$co2 ~ 1, dat, grd, model = "Mat", kappa=4.4, fix.values = c(10, 100, 2000), miscFitOptions = list())

plot(Krig)

############
library(gapminder)
library(ggplot2)
#img <- image_graph(600, 340, res = 96)
#datalist <- split(dat)
#out <- lapply(datalist, function(dat){
#  p <- ggplot(dat) + 
#      geom_tile(data = as.data.frame(W0), aes(x = W0@coords[,1], y = W0@coords[,2], fill = W0@data$co2), alpha=0.6) +
#      scale_fill_gradient(low = "green", high = "red") +
#      geom_point(aes(x = dat@coords[,1], y = dat@coords[,2]), data = as.data.frame(coordinates(dat)), alpha = .6, color="black", size = 1) + 
#      theme_classic()
#  print(p)
#})p
#dev.off()
#animation <- image_animate(img, fps = 2, optimize = TRUE)
#print(animation)


fig <- image_scale(pla1, "600x547")
img <- image_graph(width = 470, height = 447, res = 96)
ggplot()+ 
geom_tile(data = as.data.frame(W0), aes(x = W0@coords[,1], y = W0@coords[,2], fill = W0@data$co2), alpha=0.6) +
scale_fill_gradient(low = "green", high = "red") + 
geom_point(aes(x = dat@coords[,1], y = dat@coords[,2]), data = as.data.frame(coordinates(dat)), alpha = .6, color="black", size = 1) 
dev.off() 
#img <- img %>% image_rotate(180)
img <-  image_fx(img, expression = "0.5*a", channel = "alpha")#img1 %>% image_rotate(180)
out <- image_composite(fig, img, offset = "+5+45")
print(out)


img1 <- image_graph(width = 400, height = 347, res = 96, alpha=0.5)
points(dat@coords, pch=4, cex=0.5)
pts <- list("sp.points", dat, pch = 4, col = "black", cex=0.5)
spplot(z["co2.pred"],col.regions=terrain.colors(140), cuts=140, sp.layout=list(pts), contour=FALSE, labels=FALSE, pretty=TRUE, col='brown', main='IDW')
dev.off() 
img1 <-  image_fx(img1, expression = "0.5*a", channel = "alpha")#img1 %>% image_rotate(180)
out1 <- image_composite(fig, img1, offset = "+70+30")
print(out1)

###############################
# IMAGES FOR CO2 MOVIE
###############################

#dataset1 = read.csv('evolCO2.csv',header = T, sep = ';')

#dat1 <- na.omit(dataset1) 

library("stringr")
library("tidyverse")


for (i in 1:200) {

co2b<-rbind(dat1$Node.1[i],dat1$Node.2[i],dat1$Node.3[i],dat1$Node.4[i],dat1$Node.5[i],dat1$Node.6[i],dat1$Node.7[i],dat1$Node.8[i])
dat2 <- as.data.frame(cbind(x,y,co2b))
colnames(dat2) <- c('x', 'y', 'co2')
# Añado coordenadas GPS al data.frame
coordinates(dat2) <- ~x+y
print(t(dat2$co2))
# Spatial statistics & Kriging
x2.range <- as.double(range(dat2@coords[,1]))
y2.range <- as.double(range(dat2@coords[,2]))

# Establish grid (and resolution) and predict variogram values in the grid
grd2 <- expand.grid(x=seq(from=x2.range[1], to=x2.range[2], by=10), y=seq(from=y2.range[1], to=y2.range[2], by=10))
coordinates(grd2) <- ~ x+y 
gridded(grd2) <- TRUE
# Compute the variogram and establish a relationship (linear: ldbn~1)
g <- gstat(id="co2", formula= co2 ~ 1, data=dat2)
#v <- variogram(g,cloud=TRUE)
v<-gstat::variogram(g, 500, cutoff = 3000,width = 100)
v.fit <- fit.variogram(v, model=vgm(1, "Mat", 500, 5000))
#plot(v,v.fit)
p <- predict(g, model=v.fit, newdata=grd2)

# Lriging linear representation
W<-as.data.frame(cbind(p@coords[,1], p@coords[,2], p@data$co2.pred))
colnames(W)<-c('lon','lat','co2')
coordinates(W) <- ~ lon+lat
titl<-str_c("Spatial statistics in room 4.1 (N=",i,")")
ggplot(as.data.frame(W$co2),aes(W@coords[,1],W@coords[,2])) + geom_tile(data = as.data.frame(W), aes(x = W@coords[,1], y = W@coords[,2], fill = W@data$co2), alpha=0.7) +  scale_fill_gradient(low="green", high = "red", limits=c(0,700)) +  geom_contour(aes(z = W$co2), colour="black", bins = 12, alpha=0.7) + geom_text_contour(aes(z = W$co2), rotate = FALSE, alpha=0.7) + geom_point(aes(x = dat2@coords[,1], y = dat2@coords[,2]), data = as.data.frame(coordinates(dat2)), alpha = .8, color="black", size = 1) + labs(fill = "CO2 conc. (ppm)") + ggtitle(titl) + xlab("x pos.") + ylab("y pos.")
#ggplot() + geom_tile(data = as.data.frame(W), aes(x = W@coords[,1], y = W@coords[,2], fill = W@data$co2), alpha=0.9) + scale_fill_gradient(low = "green", high = "red", limits=c(390, 700)) + geom_point(aes(x = dat@coords[,1], y = dat@coords[,2]), data = as.data.frame(coordinates(dat2)), alpha = .6, color="black", size = 1) + stat_density_2d(geom = "raster",  aes(fill = after_stat(density)), contour = TRUE) + scale_fill_viridis_c() + labs(fill = "CO2 conc. (ppm)") + ggtitle(titl) + xlab("x pos.") + ylab("y pos.")

nom<-"sp_co2room41_"
ggsave(str_c(nom,i,".png"))
}

#IDW
z1<-predict(g,grd2)
par(mar=c(2,2,2,2))
points(dat2@coords, pch=4, cex=0.5)
pts2 <- list("sp.points", dat, pch = 4, col = "black", cex=0.5)
spplot(z1["co2.pred"],col.regions=terrain.colors(140), cuts=140, sp.layout=list(pts2), contour=FALSE, labels=FALSE, pretty=TRUE, col='brown', main='IDW')

