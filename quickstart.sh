#!
# sudo -S
# git clone git@alpine:slan/HelloArty hartysoc

sudo apt-get install -y python3-pip python3-venv
python3 -m venv ~/virtualenvs/hartysoc
. ~/virtualenvs/hartysoc/bin/activate

pip install wheel
pip install nmigen nmigen-boards
