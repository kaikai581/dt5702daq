#!/bin/bash

# decorate the command line
if [[ $EUID -ne 0 ]]; then
    PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\n\$\[\033[00m\] '
else
    PS1='\[\033[01;31m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\n\$\[\033[00m\] '
fi

# my own frequently used aliases
unalias ll
alias ll='ls -l --color=auto'

# enable conda
conda_script=(/home/hepr2018/sklin/anaconda3/etc/profile.d/conda.sh /home/kaikai/anaconda3/etc/profile.d/conda.sh)
for i in "${conda_script[@]}"
do
    if [[ -f "$i" ]]; then
        . $i
    fi
done

# activate environment
conda activate conda-forge

# quiet down the warning
export XDG_RUNTIME_DIR=/tmp/runtime-root

# avoid generation of .pyc files
export PYTHONDONTWRITEBYTECODE=1

# expose libraries to python
export PYTHONPATH=$PWD/libs:$PWD/FEBDTP:$PYTHONPATH
