#!/bin/bash

# Update system packages
if [[ $(command -v apt-get) ]]; then
  apt-get update
  apt-get -y upgrade
  apt-get install -y gcc cmake git valgrind build-essential
elif [[ $(command -v yum) ]]; then
  yum update
  yum upgrade -y
  yum install -y gcc cmake git valgrind
else
  echo "This script only supports Ubuntu and CentOS"
  exit 1
fi

# Check if packages were successfully installed
if [[ $(command -v gcc) && $(command -v cmake) && $(command -v git) && $(command -v valgrind) ]]; then
  echo "Installation and system update complete!"
else
  echo "There was an error installing one or more packages"
  exit 1
fi
