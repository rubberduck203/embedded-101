#! /bin/bash -ex

docker-machine create -d virtualbox default
docker-machine stop
vboxmanage modifyvm default --usbehci on
docker-machine start
vboxmanage usbfilter add 0 --target default --name ftdi --vendorid 0x0403 --productid 0x6015
vboxmanage usbfilter add 0 --target default --name arduino-org --vendorid 0x2A03
vboxmanage usbfilter add 0 --target default --name arduino-cc --vendorid 0x2341