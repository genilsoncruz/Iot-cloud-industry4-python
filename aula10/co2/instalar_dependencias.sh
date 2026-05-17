#!/bin/bash

echo "Instalando dependências..."

sudo apt update

sudo apt install -y python3-pip build-essential minicom

pip3 install pyserial

echo "Dependências instaladas."
