

# **Purevision** 

## introduction
Purevision est un projet qui consite à transformer une picar en une voiture autonome qui analyse son environement  

## Materiels nécessaire 
---------------------------------
* kit Picar 4wd
* Raspberry 4 
* camera raspberry ou webcam usb
* Carte SD 64 GB
* Ubuntu Server 20.04.3 LTS 64 bit
-------------------------------------
## logicielles nécessaire  

| paquets   | version |
| ------    | --------|
| gstreamer | 1.18.4  |
| opencv    |  4.5.2  |
| ROS       |  noetic |
| raspidvid | x.x.x   |
| picar_4wd | x.x.x   |

## Préparation de l'image 
---------------------------------------
**Deux possiblités** s'offre à vous :
* Utiliser l'image avec l'ensemble des pre-requis 
* Créer sa propore image
--------------------------------------------------
### 1- Préparation de la carte sd
--------------------------------------------------

### Téléchargement de l'image ubuntu ici: [Lien](https://ubuntu.com/download/raspberry-pi)

## Installation des paquets
### 1. installation de gstreamer 
suivre le lien suivant: https://qengineering.eu/install-gstreamer-1.18-on-raspberry-pi-4.html 

### `2. Installation de opencv`
    
Mise à jour 
```
sudo apt update
sudo apt install libopencv-dev python3-opencv
sudo apt install git 
```
installation des élements de base:
```
# to get your administation in order

$ sudo apt-get update
$ sudo apt-get upgrade

$ sudo apt-get install build-essential cmake gcc g++ git unzip pkg-config
$ sudo apt-get install libjpeg-dev libpng-dev libtiff-dev
$ sudo apt-get install libavcodec-dev libavformat-dev libswscale-dev
$ sudo apt-get install libgtk2.0-dev libcanberra-gtk*
$ sudo apt-get install libxvidcore-dev libx264-dev
$ sudo apt-get install python3-dev python3-numpy python3-pip
$ sudo apt-get install libtbb2 libtbb-dev libdc1394-22-dev
$ sudo apt-get install libv4l-dev v4l-utils
$ sudo apt-get install libopenblas-dev libatlas-base-dev libblas-dev
$ sudo apt-get install liblapack-dev gfortran libhdf5-dev
$ sudo apt-get install libprotobuf-dev libgoogle-glog-dev libgflags-dev
$ sudo apt-get install protobuf-compiler
```

```
sudo apt install build-essential cmake git pkg-config libgtk-3-dev \
    libavcodec-dev libavformat-dev libswscale-dev libv4l-dev \
    libxvidcore-dev libx264-dev libjpeg-dev libpng-dev libtiff-dev \
    gfortran openexr libatlas-base-dev python3-dev python3-numpy \
    libtbb2 libtbb-dev libdc1394-22-dev libopenexr-dev \
    libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
```
Ajout d'une memory swaping pour augementer la rapidité 
```
# install zram
sudo apt-get install zram-config

# install your desktop
sudo apt-get install ubuntu-desktop
startx
```
modifier le fichier init-zram-swapping 
```
sudo nano /usr/bin/init-zram-swapping
# after saving the modifications, restart
reboot
```



Clone d'opencv depuis les repos git :
```
free -m
mkdir ~/opencv_build && cd ~/opencv_build
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
```
 Build opencv avec cmake :
```
cmake -D CMAKE_BUILD_TYPE=RELEASE \
        -D CMAKE_INSTALL_PREFIX=/usr/local \
        -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules \
        -D ENABLE_NEON=ON \
        -D BUILD_TIFF=ON \
        -D WITH_FFMPEG=ON \
        -D WITH_GSTREAMER=ON \
        -D WITH_TBB=ON \
        -D BUILD_TBB=ON \
        -D BUILD_TESTS=OFF \
        -D WITH_EIGEN=OFF \
        -D WITH_V4L=ON \
        -D WITH_LIBV4L=ON \
        -D WITH_VTK=OFF \
        -D OPENCV_ENABLE_NONFREE=ON \
        -D INSTALL_C_EXAMPLES=OFF \
        -D INSTALL_PYTHON_EXAMPLES=OFF \
        -D BUILD_NEW_PYTHON_SUPPORT=ON \
        -D BUILD_opencv_python3=TRUE \
        -D OPENCV_GENERATE_PKGCONFIG=ON \
        -D BUILD_EXAMPLES=OFF ..
```
la fin de la compilation devrait donner un affichage comme ceci
```
Output
-- Configuring done
-- Generating done
-- Build files have been written to: /home/vagrant/opencv_build/opencv/build
```
lancer la compliation 
```
make -j4
```
Faire un make install 
```
sudo make install
```
Verification de l'installation 
```
pkg-config --modversion opencv4
```


### 3. installation de ROS

suivre le tuto suivant:

http://wiki.ros.org/noetic/Installation/Ubuntu

### 4. installation de raspicam 
 * Modifier le config.txt
```
#setting Raspicam 
start_x=1
gpu_men=128
```
 * installation du paquet suivant 
```

```

### 5. installation de raspi-config 

```
wget https://archive.raspberrypi.org/debian/pool/main/r/raspi-config/raspi-config_20200601_all.deb -P /tmp
sudo apt-get install libnewt0.52 whiptail parted triggerhappy lua5.1 alsa-utils -y
# Auto install dependancies on eg. ubuntu server on RPI
sudo apt-get install -fy
sudo dpkg -i /tmp/raspi-config_20200601_all.deb
```


## Installation de picar 4wd


installer les paquets suivant pour les scripts pythons 
```
sudo apt-get install python3-catkin-pkg-modules
sudo apt-get install python3-rospkg-modules
sudo apt-get install python3-rospy

source /opt/ros/noetic/setup.bash
```


## premision 
donner acces au gpio 

```
groupadd gpio
usermod -a -G gpio ubuntu
sudo adduser ubuntu gpio

sudo chown root.gpio /dev/gpiomem
sudo chown root.gpio /dev/mem
sudo chmod g+rw /dev/gpiomem
sudo chmod g+rw /dev/mem
```

Pour éviter d ela refaire à chaque fois, il est possible de l'ecire en dur avec les commandes suivantes:

```
echo "sudo chown root.gpio /dev/gpiomem" >> ~/.bashrc
echo "sudo chmod g+rw /dev/gpiomem" >> ~/.bashrc
echo "sudo chown root.gpio /dev/mem " >> ~/.bashrc
echo "sudo chmod g+rw /dev/mem" >> ~/.bashrc
```

voire également les liens suivants :


https://forums.raspberrypi.com/viewtopic.php?t=58782
----

https://raspberrypi.stackexchange.com/questions/40105/access-gpio-pins-without-root-no-access-to-dev-mem-try-running-as-root
----