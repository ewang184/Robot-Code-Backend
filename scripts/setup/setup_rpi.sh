# install arduino-cli
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

# add arduino-cli to path
export PATH=$PATH:$HOME/bin 
echo 'export PATH=$PATH:$HOME/bin' | tee -a  $HOME/.bashrc > /dev/null

# arduino-cli setup
arduino-cli core update-index
arduino-cli core install arduino:avr
