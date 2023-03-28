#!/bin/sh

cd $(dirname $0)
loc=$(pwd)
rsync -vrP --delete-after --exclude build/build ${loc} root@eliasnijs.xyz:msgserver/
