#/usr/bin/bash


if [ -d $1 ]
  then echo "directory"
elif [ -f $1 ]
then echo "file"

fi
exit 0
